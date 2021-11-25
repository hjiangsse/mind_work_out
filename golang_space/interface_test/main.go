package main

import "fmt"

type Actions interface {
	eating()
	drinking()
}

type Mankind struct {
	Name string
	Age  int
}

type Color struct {
	R int
	G int
	B int
}

type Animal struct {
	Name  string
	Age   int
	Color Color
}

func (m *Mankind) eating() {
	fmt.Printf("the man[%v] is eating something!\n", m)
}

func (m *Mankind) drinking() {
	fmt.Printf("the man[%v] is drinking some water!\n", m)
}

func (a *Animal) eating() {
	fmt.Printf("the animal[%v] is eating something!\n", a)
}

func (a *Animal) drinking() {
	fmt.Printf("the animal[%v] is drinking some water!\n", a)
}

func main() {
	unimap := make(map[string]Actions)
	man1 := Mankind{
		Name: "hjiang",
		Age:  30,
	}
	unimap["first"] = &man1

	ani1 := Animal{
		Name: "panda",
		Age:  12,
		Color: Color{
			R: 0,
			G: 0,
			B: 0,
		},
	}
	unimap["second"] = &ani1

	unimap["second"].drinking()
	unimap["second"].eating()

	fmt.Printf("%v", unimap["second"].(*Animal))
}
