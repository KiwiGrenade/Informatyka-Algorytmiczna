package go_wrapper

import (
	"testing"
)

func Test_IFactor(t *testing.T) {
	const expected uint64 = 120
	var got uint64 = IFactor(5)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}

func Test_RFactor(t *testing.T) {
	const expected uint64 = 120
	var got uint64 = RFactor(5)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}

func Test_IGCD_1(t *testing.T) {
	const expected uint64 = 1
	var got uint64 = IGCD(1, 1)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}

func Test_IGCD_2(t *testing.T) {
	const expected uint64 = 10
	var got uint64 = IGCD(10, 100)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}

func Test_RGCD_1(t *testing.T) {
	const expected uint64 = 1
	var got uint64 = RGCD(1, 1)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}

func Test_RGCD_2(t *testing.T) {
	const expected uint64 = 10
	var got uint64 = RGCD(10, 100)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}

func Test_RLDE_1(t *testing.T) {
	var expected int64Pair
	expected.x = -1
	expected.y = 1
	var got int64Pair = RLDE(24, 36, 12)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}

func Test_RLDE_2(t *testing.T) {
	var expected int64Pair
	expected.x = 2
	expected.y = -5
	var got int64Pair = RLDE(91, 35, 7)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}

func Test_ILDE_1(t *testing.T) {
	var expected int64Pair
	expected.x = -1
	expected.y = 1
	var got int64Pair = ILDE(24, 36, 12)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}

func Test_ILDE_2(t *testing.T) {
	var expected int64Pair
	expected.x = 2
	expected.y = -5
	var got int64Pair = ILDE(91, 35, 7)
	if got != expected {
		t.Errorf("expected: %d, got: %d", expected, got)
	}
}
