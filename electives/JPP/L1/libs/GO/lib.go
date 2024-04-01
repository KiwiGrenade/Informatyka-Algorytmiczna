package go_lib

import "fmt"

// int64Pair represents a pair of int64 values
type int64Pair struct {
	x int64
	y int64
}

func IFactor(n uint64) uint64 {
	var r uint64 = 1
	var i uint64 = 2
	if n < 2 {
		return 1
	}
	for i <= n {
		r *= i
		i++
	}
	return r
}

func RFactor(n uint64) uint64 {
	if n < 2 {
		return 1
	} else {
		return n * RFactor(n-1)
	}
}

func IGCD(a uint64, b uint64) uint64 {
	var t uint64
	for b != 0 {
		t = b
		b = a % b
		a = t
	}
	return a
}

func RGCD(a uint64, b uint64) uint64 {
	if b == 0 {
		return a
	} else {
		return RGCD(b, a % b)
	}
}

// ERGCD finds the extended greatest common divisor
func ERGCD(a, b uint64, x, y *int64) int64 {
	if b == 0 {
		*x = 1
		*y = 0
		return int64(a)
	}
	var g int64
	var x1, y1 int64
	g = ERGCD(b, a%b, &x1, &y1)
	*x = y1
	*y = x1 - int64(a/b)*y1
	return g
}

// RLDES finds the solution for a recursive linear Diophantine equation
func RLDES(a, b, c uint64) int64Pair {
	var result int64Pair
	var x, y int64
	if a == 0 && b == 0 {
		if c == 0 {
			fmt.Println("Infinite Solutions Exist")
		} else {
			fmt.Println("No Solution Exists")
		}
	} else {
		gcd := ERGCD(a, b, &x, &y)
		if c%uint64(gcd) != 0 {
			fmt.Println("No Solution Exists")
		}
		result.x = x
		result.y = y
	}
	return result
}

// IEGCD finds the iterative extended greatest common divisor
func IEGCD(a, b uint64, x, y *int64) int64 {
	var X0, Y0, X1, Y1, Temp, Quotient, Remainder, TA, TB int64 = 1, 0, 0, 1, 0, 0, 0, int64(a), int64(b)

	*x = X0
	*y = Y0

	for TB != 0 {
		Quotient = TA / TB
		Remainder = TA % TB
		TA = TB
		TB = Remainder
		Temp = X1
		X1 = X0 - Quotient*X1
		X0 = Temp
		Temp = Y1
		Y1 = Y0 - Quotient*Y1
		Y0 = Temp

		*x = X0
		*y = Y0
	}

	return TA
}

// ILDES finds the solution for an iterative linear Diophantine equation
func ILDES(a, b, c uint64) int64Pair {
	var result int64Pair
	var x, y int64
	if a == 0 && b == 0 {
		if c == 0 {
			fmt.Println("Infinite Solutions Exist")
		} else {
			fmt.Println("No Solution Exists")
		}
	} else {
		gcd := IEGCD(a, b, &x, &y)
		if c%uint64(gcd) != 0 {
			fmt.Println("No Solution Exists")
		}
		result.x = x
		result.y = y
	}
	return result
}
