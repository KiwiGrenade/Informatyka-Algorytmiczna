package main

import (
	"math/rand"
	"os"
	"strconv"
	"time"
)

var horizontalPass = "---"
var spacing = "    "
var freeVert = ".."

func main() {

	args := os.Args[1:]

	// Check arguments
	if len(args) != 3 {
		println("Wrong argument number!")
		return
	}

	var m, errM = strconv.Atoi(args[0]) // columns
	var n, errN = strconv.Atoi(args[1]) // rows
	var k, errK = strconv.Atoi(args[2]) // number of travellers

	if (errM != nil) || (errN != nil) || (errK != nil) {
		println("All arguments must be integers!")
		return
	}

	if (m > 10) || (n > 10) || (m*n <= k) {
		println("Error: m * n MUST BE > k!")
		return
	}

	var vMatrix [][]*vertex
	travelers := make([]*traveler, 0, n*m)

	// create 2d table with vertices and fire vertexListener go.subroutines
	for i := 0; i < n; i++ {
		var vertexRow []*vertex
		for j := 0; j < m; j++ {
			ver := newVertex(
				freeVert,
				make(chan *traveler),
				coordinates{i, j})

			vertexRow = append(vertexRow, ver)
			go vertexListener(ver)
		}
		vMatrix = append(vMatrix, vertexRow)
	}

	// create a list of travelers and fire travSender go.subroutines
	for i := 0; i < k; i++ {
		trav := newTraveler(i)
		travelers = append(travelers, trav)
		go travSender(trav, vMatrix, m, n)
	}

	go camera(vMatrix, m, n)

	select {}
}

func camera(vMatrix [][]*vertex, m int, n int) {
	for {
		// TODO: send freeze signal to all threads
		for i := 0; i < n; i++ {
			for j := 0; j < m; j++ {
				// add 0 if the locator ID has 1 digit only
				str := ""
				if vMatrix[i][j].currTraveler != nil {
					if vMatrix[i][j].currTraveler.id < 10 {
						str += "0"
					}
					str += strconv.Itoa(vMatrix[i][j].currTraveler.id)
				} else {
					str += freeVert
				}
				print(str)
				if j < m-1 {
					print(horizontalPass)
				} else {
					println()
				}
			}
			if i < n-1 {
				for c := 0; c < m; c++ {
					print("|")
					if c < m-1 {
						print(spacing)
					} else {
						println()
					}
				}
			}
		}
		println()
		// TODO: send resume signal to all threads
		time.Sleep(time.Millisecond * 750)
	}
}

func travSender(traveler *traveler, vMatrix [][]*vertex, m int, n int) {
	// sleep for starters
	r := rand.Intn(10000)
	time.Sleep(time.Duration(r) * time.Millisecond)
	randX := rand.Intn(m - 1)
	randY := rand.Intn(n - 1)
	transmission(traveler, vMatrix[randX][randY])
	for {
		// currTraveler has a vertex
		X := traveler.currVertex.cord.x
		Y := traveler.currVertex.cord.y
		switch direction := rand.Intn(4); direction {
		case 0:
			// right
			if (X + 1) < n {
				transmission(traveler, vMatrix[X+1][Y])
			}
		case 1:
			// left
			if (X - 1) >= 0 {
				transmission(traveler, vMatrix[X-1][Y])
			}
		case 2:
			// down
			if (Y + 1) < m {
				transmission(traveler, vMatrix[X][Y+1])
			}
		case 3:
			// up
			if (Y - 1) >= 0 {
				transmission(traveler, vMatrix[X][Y-1])
			}
		}
		// sleep
		r := rand.Intn(500)
		time.Sleep(time.Duration(r) * time.Millisecond)
	}
}

func transmission(traveler *traveler, toBeVertex *vertex) {
	toBeVertex.receive <- traveler
	response := <-traveler.receiveChan
	if response {
		addToHistory(traveler, toBeVertex.cord)
		move(traveler, toBeVertex)
	}
}

func move(traveler *traveler, vertex *vertex) {
	// move out
	if traveler.currVertex != nil {
		traveler.currVertex.locator = freeVert
		traveler.currVertex.currTraveler = nil
	}
	//move in
	traveler.currVertex = vertex
	vertex.currTraveler = traveler
}

func vertexListener(vert *vertex) {
	for {
		// receive move in request
		traveler := <-vert.receive

		var response bool
		if vert.currTraveler == nil {
			vert.currTraveler = traveler
			response = true
		} else {
			response = false
		}
		// respond
		traveler.receiveChan <- response
	}
}

type traveler struct {
	currVertex  *vertex
	moveHistory []coordinates
	id          int
	receiveChan chan bool
	freezeChan  chan bool
}
type vertex struct {
	id           int
	cord         coordinates
	locator      string
	currTraveler *traveler
	receive      chan *traveler
	freezeChan   chan bool
}

func addToHistory(traveler *traveler, newCords coordinates) {
	traveler.moveHistory = append(traveler.moveHistory, newCords)
}

func newVertex(locatorSymbol string, channel chan *traveler, coordinates coordinates) *vertex {
	ver := vertex{locator: locatorSymbol, receive: channel, cord: coordinates}
	return &ver
}

type coordinates struct {
	x int
	y int
}

func newTraveler(id int) *traveler {
	traveler := traveler{id: id, moveHistory: make([]coordinates, 0), receiveChan: make(chan bool)}
	return &traveler
}
