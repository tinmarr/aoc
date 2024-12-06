package main

import (
	"fmt"
	"strconv"
	"strings"

	helper "github.com/tinmarr/aoc/2024"
)

func part1(file string) {
	rules := make(map[string][]string)
	lines := strings.Split(file, "\n")
	i := 0
	for lines[i] != "" {
		nums := strings.Split(lines[i], "|")
		beforeList, ok := rules[nums[0]]
		if !ok {
			rules[nums[0]] = []string{nums[1]}
		} else {
			rules[nums[0]] = append(beforeList, nums[1])
		}
		i++
	}
	i++
	res := 0
	for i < len(lines) {
		nums := strings.Split(lines[i], ",")
		seenSoFar := make(map[string]bool)
		good := true
		for _, num := range nums {
			seenSoFar[num] = true
			rule, exists := rules[num]
			if !exists {
				continue
			}
			meetsRules := true
			for _, r := range rule {
				_, seen := seenSoFar[r]
				if seen {
					meetsRules = false
					break
				}
			}
			if !meetsRules {
				good = false
				break
			}
		}
		if good {
			val, err := strconv.Atoi(nums[len(nums)/2])
			if err != nil {
				fmt.Println("err in atoi")
			}
			res += val
		}
		i++
	}
	fmt.Println(res)
}

func part2(file string) {
}

func main() {
	file := helper.LoadFile()
	part1(file)
	// part2(file)
}
