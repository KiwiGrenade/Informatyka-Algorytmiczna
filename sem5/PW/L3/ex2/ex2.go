package main

import (
	"fmt"
	"math/rand"
	"strconv"
	"time"
)

type semaphore struct {
	semC chan struct{}
}

func newSemaphore(maxConcurrency int) *semaphore {
	return &semaphore{
		semC: make(chan struct{}, maxConcurrency),
	}
}

func (s *semaphore) Acquire() {
	s.semC <- struct{}{}
}

func (s *semaphore) Release() {
	<-s.semC
}

var (
	readerCount = 0
	rsem        = newSemaphore(1)
	wsem        = newSemaphore(1)
	visitors    = []string{}
)

func removeElement(slice []string, value string) []string {
	for i := 0; i < len(slice); i++ {
		if slice[i] == value {
			slice = append(slice[:i], slice[i+1:]...)
			i--
		}
	}
	return slice
}

func reader(id int) {
	for {
		rand.Seed(time.Now().UnixNano())
		r := rand.Intn(10000)
		time.Sleep(time.Duration(r) * time.Millisecond)

		rsem.Acquire()
		readerCount++
		if readerCount == 1 {
			wsem.Acquire()
		}
		rsem.Release()
		visitors = append(visitors, "R"+strconv.Itoa(id))
		fmt.Println(visitors)

		rand.Seed(time.Now().UnixNano())
		r = rand.Intn(10000)
		time.Sleep(time.Duration(r) * time.Millisecond)

		rsem.Acquire()
		readerCount--
		if readerCount == 0 {
			wsem.Release()
		}
		visitors = removeElement(visitors, "R"+strconv.Itoa(id))
		rsem.Release()
		fmt.Println(visitors)
	}
}

func writer(id int) {
	for {
		rand.Seed(time.Now().UnixNano())
		r := rand.Intn(10000)
		time.Sleep(time.Duration(r) * time.Millisecond)

		//println("writer " + strconv.Itoa(id) + " is writing")
		wsem.Acquire()
		visitors = append(visitors, "W"+strconv.Itoa(id))
		fmt.Println(visitors)

		rand.Seed(time.Now().UnixNano())
		r = rand.Intn(10000)
		time.Sleep(time.Duration(r) * time.Millisecond)

		visitors = removeElement(visitors, "W"+strconv.Itoa(id))
		wsem.Release()
		fmt.Println(visitors)
	}

}

func main() {
	m := 4 // readers
	n := 2 // writers

	for i := 0; i < m; i++ {
		go reader(i)
	}

	for i := 0; i < n; i++ {
		go writer(i)
	}

	select {}
}
