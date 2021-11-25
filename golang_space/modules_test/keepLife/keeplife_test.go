package main

import "testing"

func Test_tell_some_thing(t *testing.T) {
	want := "Life is short, do not waste your time!"
	if get := tell_some_thing(); want != get {
		t.Fatalf("test fail! want: %s, get: %s\n", want, get)
	}
}
