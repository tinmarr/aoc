package main

import (
	"fmt"
	"strings"

	helper "github.com/tinmarr/aoc/2024"
)

const (
	UP    = iota
	RIGHT = iota
	DOWN  = iota
	LEFT  = iota
)

func processMap(file string) (int, int, [][]int) {
	lines := strings.Split(file, "\n")
	grid := make([][]int, len(lines))

	var startRow, startCol int
	for row, line := range lines {
		gridRow := make([]int, len(line))
		for col := 0; col < len(line); col++ {
			if line[col] == '^' {
				startRow = row
				startCol = col
			} else if line[col] == '#' {
				gridRow[col] = 1
			}
		}
		grid[row] = gridRow
	}
	return startRow, startCol, grid
}

func part1(file string) {
	row, col, grid := processMap(file)
	direction := UP
	visited := 0

	for {
		if grid[row][col] != 2 {
			visited++
			grid[row][col] = 2
		}
		nextRow, nextCol := row, col
		switch direction {
		case UP:
			nextRow--
		case DOWN:
			nextRow++
		case LEFT:
			nextCol--
		case RIGHT:
			nextCol++
		}
		inBounds := 0 <= nextRow && nextRow < len(grid) && 0 <= nextCol && nextCol < len(grid[0])
		if !inBounds {
			break
		} else if grid[nextRow][nextCol] == 1 {
			if direction == LEFT {
				direction = UP
			} else {
				direction++
			}
		} else {
			row = nextRow
			col = nextCol
		}
	}

	fmt.Println(visited)
}

func part2(file string) {
}

func main() {
	file := helper.LoadFile()
	part1(file)
	// part2(file)
}
