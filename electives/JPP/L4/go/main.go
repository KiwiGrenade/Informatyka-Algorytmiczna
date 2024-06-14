package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"sync"
	"time"
)

var meals int

func philosopher(philosopher int, A, B *sync.Mutex, C *sync.Mutex, WG *sync.WaitGroup) {
	defer WG.Done()
	for i := 0; i < meals; i++ {
		duration := rand.Intn(800 - 200 + 1) + 200 
		C.Lock()
		fmt.Printf("%d is thinking %dms\n", philosopher, duration)
		C.Unlock()
		time.Sleep(time.Duration(duration) * time.Millisecond)

		C.Lock()
		fmt.Printf("\t\t%d is hungry\n", philosopher)
		C.Unlock()

		A.Lock()
		B.Lock()
		duration = rand.Intn(800 - 200 + 1) + 200
		C.Lock()
		fmt.Printf("\t\t\t\t%d eats his %d meal %dms\n", philosopher, i+1, duration)
		C.Unlock()
		time.Sleep(time.Duration(duration) * time.Millisecond)
		B.Unlock()
		A.Unlock()
	}
}

func main() {
	if len(os.Args) <= 2 {
		fmt.Println("Usage: go run main.go [nPhilosophers] [nMeals]")
		return
	}

	philNum, err := strconv.Atoi(os.Args[1])
	if err != nil || philNum <= 1 {
		fmt.Println("!!! nPhilosophers > 1 !!!")
		return
	}

	meals, err = strconv.Atoi(os.Args[2])
	if err != nil || meals <= 0 {
		fmt.Println("!!! nMeals > 0 !!!")
		return
	}

	var wg sync.WaitGroup
	mutexes := make([]*sync.Mutex, philNum)
	for i := range mutexes {
		mutexes[i] = &sync.Mutex{}
	}
	C := &sync.Mutex{}

	for i := 0; i < philNum; i++ {
		wg.Add(1)
		go func(i int) {
			philosopher(i+1, mutexes[i], mutexes[(i + 1) % philNum], C, &wg)
		}(i)
	}

	wg.Wait()
}
