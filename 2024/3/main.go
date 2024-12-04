package main

import (
	"fmt"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func part1(file string) {
	re := regexp.MustCompile(`mul\(\d{1,3},\d{1,3}\)`)
	muls := re.FindAllString(file, -1)
	sum := 0

	for _, mul := range muls {
		numString := strings.Trim(mul[4:], "()")
		nums := strings.Split(numString, ",")

		num1, err1 := strconv.Atoi(nums[0])
		num2, err2 := strconv.Atoi(nums[1])
		if err1 != nil || err2 != nil {
			fmt.Println("err during atoi")
		}
		sum += num1 * num2
	}
	fmt.Println(sum)
}

func part2(file string) {
	re := regexp.MustCompile(`mul\(\d{1,3},\d{1,3}\)|don't\(\)|do\(\)`)
	instr := re.FindAllString(file, -1)
	sum := 0
	doing := true
	for _, instruction := range instr {
		if instruction == "do()" {
			doing = true
		} else if instruction == "don't()" {
			doing = false
		} else if doing {
			numString := strings.Trim(instruction[4:], "()")
			nums := strings.Split(numString, ",")

			num1, err1 := strconv.Atoi(nums[0])
			num2, err2 := strconv.Atoi(nums[1])
			if err1 != nil || err2 != nil {
				fmt.Println("err during atoi")
			}
			sum += num1 * num2
		}
	}
	fmt.Println(sum)
}

func main() {
	dat, err := os.ReadFile(os.Args[1])
	if err != nil {
		fmt.Println("read file error")
		return
	}
	file := strings.TrimRight(string(dat), "\n")

	// part1(file)
	part2(file)
}
