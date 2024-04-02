package main_c
/* 
#include <stdint.h>
struct int64Pair 
{
	int64_t x;
	int64_t y;
};
*/
import "C"
import "fmt"

//export IFactor
func IFactor(n uint16) uint64 {
	var r uint64 = 1
	var i uint16 = 2
	if n < 2 {
		return 1
	}
	for i <= n {
		r *= uint64(i)
		i++
	}
	return r
}

//export RFactor
func RFactor(n uint16) uint64 {
	if n < 2 {
		return 1
	} else {
		return uint64(n) * RFactor(n-1)
	}
}

//export IGCD
func IGCD(a uint64, b uint64) uint64 {
	var t uint64
	for b != 0 {
		t = b
		b = a % b
		a = t
	}
	return a
}

//export RGCD
func RGCD(a uint64, b uint64) uint64 {
	if b == 0 {
		return a
	} else {
		return RGCD(b, a % b)
	}
}

// EIGCD finds the iterative extended greatest common divisor
func EIGCD(a, b int64, x, y *int64) int64 {
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

// ERGCD finds the recursive extended greatest common divisor
func ERGCD(a, b int64, x, y *int64) int64 {
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

// ILDES finds the solution for an iterative linear Diophantine equation
// export ILDES
func ILDES(a, b, c int64) C.struct_int64Pair {
	var result C.struct_int64Pair
	var x, y int64
	if a == 0 && b == 0 {
		if c == 0 {
			fmt.Println("Infinite Solutions Exist")
		} else {
			fmt.Println("No Solution Exists")
		}
	} else {
		gcd := EIGCD(a, b, &x, &y)
		if c%gcd != 0 {
			fmt.Println("No Solution Exists")
		}
		result.x = x
		result.y = y
	}
	return result
}

// RLDES finds the solution for a recursive linear Diophantine equation
//export RLDES
func RLDES(a, b, c int64) C.struct_int64Pair {
	var result C.struct_int64Pair
	var x, y int64
	if a == 0 && b == 0 {
		if c == 0 {
			fmt.Println("Infinite Solutions Exist")
		} else {
			fmt.Println("No Solution Exists")
		}
	} else {
		gcd := ERGCD(a, b, &x, &y)
		if c%gcd != 0 {
			fmt.Println("No Solution Exists")
		}
		result.x = x
		result.y = y
	}
	return result
}
func main(){}