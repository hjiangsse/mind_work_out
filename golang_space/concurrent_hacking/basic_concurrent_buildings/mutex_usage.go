package main

import (
	"fmt"
	"sync"
)

type Counter struct {
	count int
	mutex sync.Mutex
}

func (cnt *Counter) Increment() {
	cnt.mutex.Lock()
	defer cnt.mutex.Unlock()
	cnt.count++
}

func (cnt *Counter) Decrement() {
	cnt.mutex.Lock()
	defer cnt.mutex.Unlock()
	cnt.count--
}

func (cnt *Counter) GetValue() int {
	cnt.mutex.Lock()
	defer cnt.mutex.Unlock()
	return cnt.count
}

func main() {
	var counter Counter
	var wg sync.WaitGroup
	wg.Add(5)
	for i := 0; i < 5; i++ {
		go func() {
			defer wg.Done()
			counter.Increment()
		}()
	}

	wg.Add(4)
	for i := 0; i < 4; i++ {
		go func() {
			defer wg.Done()
			counter.Decrement()
		}()
	}

	wg.Wait()
	fmt.Println("Now the value of the counter is: ", counter.GetValue())
}
