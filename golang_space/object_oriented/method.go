package main

import (
	"fmt"
	"image/color"
	"math"
	"sync"
)

type Point struct {
	X, Y float64
}

type ColoredPoint struct {
	Point
	Color color.RGBA
}

type Path []Point

//Distance() return the distance traval along the path
func (p Path) Distance() float64 {
	res := 0.0
	for i := range p {
		if i > 0 {
			res += p[i-1].Distance(p[i])
		}
	}
	return res
}

func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X-p.X, q.Y-p.Y)
}

func (p *ColoredPoint) Distance(q ColoredPoint) float64 {
	return p.Point.Distance(q.Point)
}

func (p *Point) ScaleBy(factor float64) {
	p.X *= factor
	p.Y *= factor
}

type MapCache struct {
	sync.Mutex
	mapping map[string]string
}

func (c *MapCache) LookUp(s string) string {
	c.Lock()
	v := c.mapping[s]
	c.Unlock()
	return v
}

func (c *MapCache) Add(key, val string) {
	c.Lock()
	c.mapping[key] = val
	c.Unlock()
}

func main() {
	a := Point{
		X: 10,
		Y: 20,
	}

	b := Point{
		X: 20,
		Y: 30,
	}

	fmt.Println(a.Distance(b))
	fmt.Println(a.X)
	fmt.Println(a.Y)

	c := Point{
		X: 40,
		Y: 90,
	}

	path := Path{a, b, c}
	fmt.Println("The distance of the path: ", path.Distance())

	c.ScaleBy(10)
	newPath := Path{a, b, c}
	fmt.Println("The distance of the path: ", newPath.Distance())

	var cp ColoredPoint
	cp.X = 1
	fmt.Println(cp.Point.X)
	cp.Point.Y = 2
	fmt.Println(cp.Y)

	red := color.RGBA{255, 0, 0, 255}
	cq := ColoredPoint{Point{1, 3}, red}
	fmt.Println(cp.Distance(cq))
	cq.ScaleBy(10)
	fmt.Println(cp.Distance(cq))

	cache := MapCache{
		mapping: make(map[string]string),
	}

	cache.Add("one", "1")
	cache.Add("two", "2")
	cache.Add("three", "3")
	fmt.Println(cache.LookUp("two"))
}
