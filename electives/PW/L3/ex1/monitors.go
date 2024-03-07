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

type Cond struct {
	me      semaphore
	waiters int
	ch      chan struct{}
}

func NewCond() *Cond {
	return &Cond{
		ch: make(chan struct{}),
		me: *newSemaphore(1),
	}
}

func (c *Cond) Wait() {
	c.me.Acquire()
	c.waiters++
	localCh := c.ch
	c.me.Release()

	// Wait for the signal
	<-localCh

	c.me.Acquire()
	c.waiters--
	if c.waiters == 0 {
		c.ch = make(chan struct{})
	}
	c.me.Release()
}

func (c *Cond) Signal() {
	c.me.Acquire()
	defer c.me.Release()

	if c.waiters > 0 {
		close(c.ch)
	}
}

type DiningPhilosophers struct {
	state    []int
	cond     []*Cond
	numPhils int
}

func NewDiningPhilosophers(numPhils int) *DiningPhilosophers {
	dp := &DiningPhilosophers{
		state:    make([]int, numPhils),
		cond:     make([]*Cond, numPhils),
		numPhils: numPhils,
	}

	for i := 0; i < numPhils; i++ {
		dp.cond[i] = NewCond()
	}

	return dp
}

func left(id int) int {
	return id
}

func right(id int, max int) int {
	return (id + 1) % max
}

func (dp *DiningPhilosophers) takeForks(id int) {
	dp.state[id] = Hungry
	dp.checkFork(id)

	if dp.state[id] != Eating {
		dp.cond[id].Wait()
	}
	output = append(output, "W"+strconv.Itoa(left(id))+" F"+strconv.Itoa(id)+" W"+strconv.Itoa(right(id, dp.numPhils)))
	fmt.Println(output)
}

func (dp *DiningPhilosophers) dropForks(id int) {
	dp.state[id] = Thinking
	output = removeElement(output, "W"+strconv.Itoa(left(id))+" F"+strconv.Itoa(id)+" W"+strconv.Itoa(right(id, dp.numPhils)))
	fmt.Println(output)
	dp.checkFork((id + 1) % dp.numPhils)
	dp.checkFork((id + dp.numPhils - 1) % dp.numPhils)
}

func (dp *DiningPhilosophers) checkFork(id int) {
	if dp.state[(id+1)%dp.numPhils] != Eating &&
		dp.state[(id+dp.numPhils-1)%dp.numPhils] != Eating &&
		dp.state[id] == Hungry {
		dp.state[id] = Eating
		dp.cond[id].Signal()
	}
}

func (dp *DiningPhilosophers) philosopherLife(id int) {
	for {
		rand.Seed(time.Now().UnixNano())
		r := rand.Intn(1000)
		time.Sleep(time.Duration(r) * time.Millisecond)

		dp.takeForks(id)

		rand.Seed(time.Now().UnixNano())
		r = rand.Intn(1000)
		time.Sleep(time.Duration(r) * time.Millisecond)

		dp.dropForks(id)
	}
}

const (
	Thinking = iota
	Hungry
	Eating
)

func main() {
	numPhilosophers := 5

	diningPhilosophers := NewDiningPhilosophers(numPhilosophers)

	for i := 0; i < numPhilosophers; i++ {
		go diningPhilosophers.philosopherLife(i)
	}

	select {}
}
