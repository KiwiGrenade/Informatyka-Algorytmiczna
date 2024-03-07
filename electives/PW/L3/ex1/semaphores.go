package main

import (
	"fmt"
	"math/rand"
	"strconv"
	"time"
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

var (
	output = []string{}
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

type philosopher struct {
	id int
}

func newPhilosopher(pid int) *philosopher {
	return &philosopher{
		id: pid,
	}
}

func left(id int) int {
	return id
}

func right(id int, max int) int {
	return (id + 1) % max
}

func takeForks(fork []*semaphore, id int, max int) {
	if id == max {
		fork[right(id, max)].Acquire()
		fork[left(id)].Acquire()
	} else {
		fork[left(id)].Acquire()
		fork[right(id, max)].Acquire()
	}
	output = append(output, "W"+strconv.Itoa(left(id))+" F"+strconv.Itoa(id)+" W"+strconv.Itoa(right(id, max)))
	fmt.Println(output)

}

func dropForks(fork []*semaphore, id int, max int) {
	fork[left(id)].Release()
	fork[right(id, max)].Release()
	output = removeElement(output, "W"+strconv.Itoa(left(id))+" F"+strconv.Itoa(id)+" W"+strconv.Itoa(right(id, max)))
	fmt.Println(output)
}

func philosopherLife(philosopher *philosopher, fork []*semaphore, max int) {
	for {
		//println("Philosopher " + strconv.Itoa(philosopher.id) + " is thinking")
		// GRAB FORKS
		rand.Seed(time.Now().UnixNano())
		r := rand.Intn(10000)
		time.Sleep(time.Duration(r) * time.Millisecond)
		takeForks(fork, philosopher.id, max)
		//println("Philosopher " + strconv.Itoa(philosopher.id) + " is eating")
		// EAT
		rand.Seed(time.Now().UnixNano())
		r = rand.Intn(10000)
		time.Sleep(time.Duration(r) * time.Millisecond)
		dropForks(fork, philosopher.id, max)
		//println("Philosopher " + strconv.Itoa(philosopher.id) + " finished eating")
	}

}

func main() {
	var k = 5
	var s []*semaphore
	var philosophers []*philosopher

	for i := 0; i < k; i++ {
		sem := newSemaphore(1)
		s = append(s, sem)
	}

	for i := 0; i < k; i++ {
		phil := newPhilosopher(i)
		philosophers = append(philosophers, phil)
	}

	for _, phil := range philosophers {
		go philosopherLife(phil, s, k)
	}

	select {}
}
