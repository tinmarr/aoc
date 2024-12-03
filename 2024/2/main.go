package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func part1(reports []string) int {
	safe := 0
	for _, report := range reports {
		direction := 0
		levels := strings.Split(report, " ")
		for i := 1; i < len(levels); i++ {
			first, err1 := strconv.Atoi(levels[i-1])
			second, err2 := strconv.Atoi(levels[i])

			if err1 != nil || err2 != nil {
				fmt.Println("err converting strings to int")
			}

			difference := first - second

			if difference == 0 || difference > 3 || difference < -3 {
				safe--
				break
			}
			if direction == 0 {
				if difference < 0 {
					direction = -1
				} else {
					direction = 1
				}
			} else {
				if difference < 0 && direction == 1 {
					safe--
					break
				} else if difference > 0 && direction == -1 {
					safe--
					break
				}
			}
		}
		safe++
	}
	return safe
}

func checkSafe(levels []string) bool {
	direction := 0
	for i := 1; i < len(levels); i++ {
		first, err1 := strconv.Atoi(levels[i-1])
		second, err2 := strconv.Atoi(levels[i])

		if err1 != nil || err2 != nil {
			fmt.Println("err converting strings to int")
		}

		difference := first - second

		if difference == 0 || difference > 3 || difference < -3 {
			return false
		}
		if direction == 0 {
			if difference < 0 {
				direction = -1
			} else {
				direction = 1
			}
		} else {
			notFollowingDown := difference < 0 && direction == 1
			notFollowingUp := difference > 0 && direction == -1
			if notFollowingDown || notFollowingUp {
				return false
			}
		}
	}
	return true
}

func part2(reports []string) int {
	safe := 0
	for _, report := range reports {
		levels := strings.Split(report, " ")
		if checkSafe(levels) {
			safe++
			continue
		}
		for i := 0; i < len(levels); i++ {
			newLevels := make([]string, 0)
			newLevels = append(newLevels, levels[:i]...)
			newLevels = append(newLevels, levels[i+1:]...)
			if checkSafe(newLevels) {
				safe++
				break
			}
		}
	}
	return safe
}

func main() {
	dat, err := os.ReadFile(os.Args[1])
	if err != nil {
		fmt.Println("read file error")
		return
	}
	file := strings.TrimRight(string(dat), "\n")
	reports := strings.Split(file, "\n")

	// res := part1(reports)
	res := part2(reports)

	fmt.Println(res)
}
