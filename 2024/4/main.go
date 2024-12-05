package main

import (
	"fmt"
	"strings"

	helper "github.com/tinmarr/aoc/2024"
)

// Returns the delta to all adjacent or diagonal Ms (values
// are either -1, 0, or 1). Returns an empty list if none
// are found
//
// Values are [rowDelta, colDelta]
func searchAround(grid [][]string, xRow, xCol int) [][2]int {
	res := make([][2]int, 0)
	options := [...][2]int{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}

	for _, option := range options {
		testRow := xRow + option[0]
		testCol := xCol + option[1]
		rowOOB := testRow < 0 || len(grid) <= testRow
		colOOB := testCol < 0 || len(grid[0]) <= testCol
		if rowOOB || colOOB {
			continue
		}
		if grid[testRow][testCol] == "M" {
			res = append(res, option)
		}
	}

	return res
}

func part1(file string) {
	// Prep file into a grid
	lines := strings.Split(file, "\n")
	grid := make([][]string, len(lines))
	for i, line := range lines {
		grid[i] = strings.Split(line, "")
	}
	res := 0
	// For each X, search adjacent or diagonals for an M
	for row := 0; row < len(grid); row++ {
		for col := 0; col < len(grid[0]); col++ {
			if grid[row][col] != "X" {
				continue
			}
			potentialDirections := searchAround(grid, row, col)
			// Then in the same direction keep looking for the next letters (until the word is found)
			for _, direction := range potentialDirections {
				// We know there is an M in the direction, so now we need to see if there is an A and an S
				aRow := row + (2 * direction[0])
				aCol := col + (2 * direction[1])
				rowOOB := aRow < 0 || len(grid) <= aRow
				colOOB := aCol < 0 || len(grid[0]) <= aCol
				if rowOOB || colOOB {
					continue
				}
				if grid[aRow][aCol] != "A" {
					continue
				}
				sRow := row + (3 * direction[0])
				sCol := col + (3 * direction[1])
				rowOOB = sRow < 0 || len(grid) <= sRow
				colOOB = sCol < 0 || len(grid[0]) <= sCol
				if rowOOB || colOOB {
					continue
				}
				if grid[sRow][sCol] != "S" {
					continue
				}
				res++
			}
		}
	}

	fmt.Println(res)
}

func part2(file string) {
	// Prep file into a grid
	lines := strings.Split(file, "\n")
	grid := make([][]string, len(lines))
	for i, line := range lines {
		grid[i] = strings.Split(line, "")
	}
	res := 0
	for row := 1; row < len(grid)-1; row++ {
		for col := 1; col < len(grid[0])-1; col++ {
			if grid[row][col] != "A" {
				continue
			}
			var tl_br, bl_tr bool
			// top left - bottom right diagonal
			tl_br = tl_br || grid[row-1][col-1] == "M" && grid[row+1][col+1] == "S"
			tl_br = tl_br || grid[row-1][col-1] == "S" && grid[row+1][col+1] == "M"
			// bottom left - top right diagonal
			bl_tr = bl_tr || grid[row+1][col-1] == "M" && grid[row-1][col+1] == "S"
			bl_tr = bl_tr || grid[row+1][col-1] == "S" && grid[row-1][col+1] == "M"

			if tl_br && bl_tr {
				res++
			}
		}
	}
	fmt.Println(res)
}

func main() {
	file := helper.LoadFile()

	// part1(file)
	part2(file)
}
