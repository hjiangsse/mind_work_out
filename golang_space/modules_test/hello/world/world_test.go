package hello

import "testing"

func TestWorld(t *testing.T) {
	want := "China World"
	if got := World(); got != want {
		t.Errorf("Hello() = %q, want %q", got, want)
	}
}
