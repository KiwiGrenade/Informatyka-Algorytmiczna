package go_wrapper

// #cgo CFLAGS: -g -Wall
// #include "../../libs/C/src/lib.c"
import "C"
import "unsafe"

type int64Pair struct {
	x int64
	y int64
}

func IFactor(n uint16) uint64 {
	var result C.uint64_t
	result = C.IFactor(C.uint16_t(n))
	return uint64(result)
}

func RFactor(n uint16) uint64 {
	var result C.uint64_t
	result = C.RFactor(C.uint16_t(n))
	return uint64(result)
}

func IGCD(a uint64, b uint64) uint64 {
	var result C.uint64_t
	result = C.IGCD(C.uint64_t(a), C.uint64_t(b))
	return uint64(result)
}

func RGCD(a uint64, b uint64) uint64 {
	var result C.uint64_t
	result = C.RGCD(C.uint64_t(a), C.uint64_t(b))
	return uint64(result)
}

// RLDE finds the solution for a recursive linear Diophantine equation
func RLDE(a, b, c uint64) int64Pair {
	var tempResult C.struct_int64_pair
	tempResult = C.RLDE(C.uint64_t(a), C.uint64_t(b), C.uint64_t(c))
	var result int64Pair

	//TODO: How to convert C_int64_pair to int64Pair?
	result

	return 
}

// ILDE finds the solution for an iterative linear Diophantine equation
func ILDE(a, b, c uint64) int64Pair {
}
