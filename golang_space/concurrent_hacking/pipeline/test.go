package main

import "fmt"

func main() {
	multiply := func(values []int, multiplier int) []int {
		multipliedValues := make([]int, len(values))
		for i, v := range values {
			multipliedValues[i] = v * multiplier
		}
		return multipliedValues
	}

	add := func(values []int, adder int) []int {
		addedValues := make([]int, len(values))
		for i, v := range values {
			addedValues[i] = v + adder
		}
		return addedValues
	}

	multiply_streamed := func(value, multiplier int) int {
		return value * multiplier
	}

	add_streamed := func(value, adder int) int {
		return value + adder
	}

	ints := []int{1, 2, 3, 4}
	for _, v := range multiply(add(multiply(ints, 2), 1), 2) {
		fmt.Println(v)
	}

	for _, v := range ints {
		fmt.Println(multiply_streamed(add_streamed(v, 2), 1))
	}
}
