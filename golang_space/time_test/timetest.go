package main

import (
	"fmt"
	"time"
)

func main() {
	stamp := time.Now().UnixNano()
	fmt.Println(stamp)
	fmt.Println(time.Unix(0, stamp).Format("2006-01-02 15:04:05"))
}
