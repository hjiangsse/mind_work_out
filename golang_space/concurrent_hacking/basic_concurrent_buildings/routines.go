package main

import (
	"fmt"
	"runtime"
	"sync"
)

var sayHello = func(wg *sync.WaitGroup) {
	defer wg.Done()
	fmt.Println("This is a test function!")
}

var memConsumed = func() uint64 {
	runtime.GC()
	var s runtime.MemStats
	runtime.ReadMemStats(&s)
	return s.Sys
}

func main() {
	var c <-chan interface{}
	var wg sync.WaitGroup
	noop := func() {
		wg.Done()
		<-c
	}

	const numGoroutines = 1e6
	wg.Add(numGoroutines)
	before := memConsumed()
	for i := numGoroutines; i > 0; i-- {
		go noop()
	}
	wg.Wait()
	after := memConsumed()
	fmt.Printf("%.3fkb", float64(after-before)/numGoroutines/1000)
	/*
		var wg sync.WaitGroup
		name := "John"
		wg.Add(2)
		go sayHello(&wg)
		go func() {
			defer wg.Done()
			name = "Jane"
		}()

		for _, name := range []string{"hjiang", "zhangheng", "liming"} {
			wg.Add(1)
			go func(name string) {
				defer wg.Done()
				fmt.Println(name)
			}(name)
		}

		wg.Wait()
		fmt.Println("After goroutines running, the name is: ", name)
	*/
}
