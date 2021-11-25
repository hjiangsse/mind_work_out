package main

import (
	"fmt"
	"sync"
)

func main() {
	var wg sync.WaitGroup
	//wg.Add(1)

	for _, cty := range []string{"china", "japan", "america"} {
		wg.Add(1)
		go func() {
			defer wg.Done()
			fmt.Println(cty)
		}()
	}

	wg.Wait()
}
