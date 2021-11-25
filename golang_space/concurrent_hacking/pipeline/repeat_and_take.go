package main

import "fmt"

func main() {

	repeat := func(done <-chan interface{}, values ...interface{}) <-chan interface{} {
		valueStream := make(chan interface{})
		go func() {
			defer close(valueStream)
			for {
				for _, v := range values {
					select {
					case <-done:
						return
					case valueStream <- v:
					}
				}
			}
		}()
		return valueStream
	}

	/*
		repeatFn := func(done <-chan interface{}, fn func() interface{}) <-chan interface{} {
			valueStream := make(chan interface{})
			go func() {
				defer close(valueStream)
				for {
					select {
					case <-done:
						return
					case valueStream <- fn():
					}
				}
			}()
			return valueStream
		}
	*/

	take := func(done <-chan interface{}, valueStream <-chan interface{}, num int) <-chan interface{} {
		takeStream := make(chan interface{})
		go func() {
			defer close(takeStream)
			for i := 0; i < num; i++ {
				select {
				case <-done:
					return
				case takeStream <- <-valueStream:
				}
			}
		}()
		return takeStream
	}

	toString := func(done <-chan interface{}, valueStream <-chan interface{}) <-chan string {
		stringStream := make(chan string)
		go func() {
			defer close(stringStream)
			for v := range valueStream {
				select {
				case <-done:
					return
				case stringStream <- v.(string):
				}
			}
		}()
		return stringStream
	}

	done := make(chan interface{})
	defer close(done)

	/*
			for num := range take(done, repeat(done, 1), 10) {
				fmt.Println(num)
			}

		randf := func() interface{} { return rand.Int() }
		for num := range take(done, repeatFn(done, randf), 10) {
			fmt.Println(num)
		}
	*/
	for str := range toString(done, take(done, repeat(done, "10"), 10)) {
		fmt.Println(str)
	}
}
