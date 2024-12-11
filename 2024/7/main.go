package main

import (
	"fmt"
	"math"
	"strconv"
	"strings"

	helper "github.com/tinmarr/aoc/2024"
)

func part1(file string) {
	lines := strings.Split(file, "\n")
	res := 0
	for _, line := range lines {
		parts := strings.Split(line, ":")
		testVal, err := strconv.Atoi(parts[0])
		if err != nil {
			fmt.Println("err in atoi")
		}

		parts = strings.Split(strings.Trim(parts[1], " "), " ")
		vals := make([]int, len(parts))
		for i, part := range parts {
			val, err := strconv.Atoi(part)
			if err != nil {
				fmt.Println("err in atoi")
			}
			vals[i] = val
		}

		// bit 0 means a "+" bit 1 means a "*"
		for counter := 0; counter < int(math.Pow(2, float64(len(vals)-1))); counter++ {
			testTotal := vals[0]
			for i := 1; i < len(vals); i++ {
				op := (counter >> (i - 1)) & 1
				switch op {
				case 1:
					testTotal *= vals[i]
				case 0:
					testTotal += vals[i]
				}
			}
			if testTotal == testVal {
				res += testVal
				break
			}
		}
	}
	fmt.Println(res)
}

func part2(file string) {
	lines := strings.Split(file, "\n")
	res := 0
	for _, line := range lines {
		parts := strings.Split(line, ":")
		testVal, err := strconv.Atoi(parts[0])
		if err != nil {
			fmt.Println("err in atoi")
		}

		parts = strings.Split(strings.Trim(parts[1], " "), " ")
		vals := make([]int, len(parts))
		for i, part := range parts {
			val, err := strconv.Atoi(part)
			if err != nil {
				fmt.Println("err in atoi")
			}
			vals[i] = val
		}

		// 0 means a "+"
		// 1 means a "*"
		// 2 means a "||"
		for counter := 0; counter < int(math.Pow(3, float64(len(vals)-1))); counter++ {
			ops := strconv.FormatInt(int64(counter), 3)
			for len(ops) < len(vals)-1 {
				ops = "0" + ops
			}
			testTotal := vals[0]
			for i := 1; i < len(vals); i++ {
				op := ops[i-1]
				switch op {
				case '2':
					r, err := strconv.Atoi(strconv.Itoa(testTotal) + strconv.Itoa(vals[i]))
					if err != nil {
						fmt.Println("err in atoi (concat)")
					}
					testTotal = r
				case '1':
					testTotal *= vals[i]
				case '0':
					testTotal += vals[i]
				default:
					fmt.Println("err in base 3 conv:", ops)
				}
			}
			if testTotal == testVal {
				res += testVal
				break
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
