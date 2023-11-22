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

	// create 2d table with vertices and fire vertexListener go.subroutines
	var vMatrix [][]*vertex
	for i := 0; i < n; i++ {
		var vertexRow []*vertex
		for j := 0; j < m; j++ {
			ver := newVertex(coordinates{i, j})

			vertexRow = append(vertexRow, ver)
			go vertexListener(ver)
		}
		vMatrix = append(vMatrix, vertexRow)
	}

	// create a list of travelers and fire travSender go.subroutines
	travelers := make([]*traveler, 0, n*m)
	for i := 0; i < k; i++ {
		id := ""
		if i < 10 {
			id += "0"
		}
		id += strconv.Itoa(i)
		trav := newTraveler(id)
		travelers = append(travelers, trav)
		go travSender(trav, vMatrix, m, n)
	}

	//nDrifters := rand.Intn((n*m - k) / 2)
	//for i := 0; i < nDrifters; i++ {
	//	drifter := newDrifter()
	//	travelers = append(travelers, drifter.traveler)
	//	go drifterLife(drifter, vMatrix, m, n)
	//}
	//
	////nDrifters := rand.Intn((n*m - k) / 2)
	//for i := 0; i < 1; i++ {
	//	danger := newDanger()
	//	travelers = append(travelers, danger.drifter.traveler)
	//	go dangerLife(danger, vMatrix, m, n)
	//}

	go camera(vMatrix, travelers, m, n)

	select {}
}

func dangerLife(danger *danger, vMatrix [][]*vertex, m int, n int) {
	for {
		select {
		// stop for the camera
		case stop := <-danger.drifter.traveler.freezeChan:
			for stop {
				stop = <-danger.drifter.traveler.freezeChan
			}
			// time run out, you're dead
		default:
			select {
			case <-danger.drifter.traveler.deathChan:
				danger.drifter.traveler.currVertex.currTraveler = nil
				return
				// DANGER DIES FOR REAL
			case <-danger.drifter.traveler.freezeChan:
				danger.drifter.traveler.isAlive = false
				// move out
				danger.drifter.traveler.currVertex.currTraveler = nil
				danger.drifter.traveler.currVertex = nil
				println("drifter is dead!")
				// find other palce and move
			default:
				if !danger.drifter.traveler.isAlive {
					// come to life
					if rand.Intn(5) == 0 {
						danger.drifter.traveler.isAlive = true

						randX := rand.Intn(m - 1)
						randY := rand.Intn(n - 1)
						for !travHandshake(danger.drifter.traveler, vMatrix[randX][randY]) {
							randX = rand.Intn(m - 1)
							randY = rand.Intn(n - 1)
						}

						go timer(danger.drifter.lifeTime, &danger.drifter.traveler.timerChan)
						// stay dead
					} else {
						time.Sleep(time.Duration(rand.Intn(500)) * time.Millisecond)
					}
				}
			}
		}
	}
}

func drifterLife(drifter *drifter, vMatrix [][]*vertex, m int, n int) {
	for {
		select {
		// stop for the camera
		case stop := <-drifter.traveler.freezeChan:
			for stop {
				stop = <-drifter.traveler.freezeChan
			}
			// time run out, you're dead
			//TODO: drifter lives after death -> * is still on the board
		default:
			select {
			case <-drifter.traveler.timerChan:
				drifter.traveler.isAlive = false
				// move out
				drifter.traveler.currVertex.currTraveler = nil
				drifter.traveler.currVertex = nil
				println("drifter is dead!")
				// find other place and move
			case <-drifter.traveler.receiveChan:
				X := drifter.traveler.currVertex.cord.x
				Y := drifter.traveler.currVertex.cord.y
				oldChannel := drifter.traveler.currVertex.drifterChan
				if ((X+1 < n) && travHandshake(drifter.traveler, vMatrix[X+1][Y])) ||
					((X-1 >= 0) && travHandshake(drifter.traveler, vMatrix[X-1][Y])) ||
					((Y+1 < m) && travHandshake(drifter.traveler, vMatrix[X][Y+1])) ||
					((Y-1 >= 0) && travHandshake(drifter.traveler, vMatrix[X][Y-1])) {
					println("drifter found a spot!")
					oldChannel <- true
				} else {
					println("drifter did not find a spot!")
					oldChannel <- false
				}
			default:
				if !drifter.traveler.isAlive {
					// come to life
					if rand.Intn(5) == 0 {
						drifter.traveler.isAlive = true

						randX := rand.Intn(m - 1)
						randY := rand.Intn(n - 1)
						for !travHandshake(drifter.traveler, vMatrix[randX][randY]) {
							randX = rand.Intn(m - 1)
							randY = rand.Intn(n - 1)
						}

						go timer(drifter.lifeTime, &drifter.traveler.timerChan)
						// stay dead
					} else {
						time.Sleep(time.Duration(rand.Intn(500)) * time.Millisecond)
					}
				}
			}
		}
	}
}

func timer(T int, wake *chan bool) {
	time.Sleep(time.Duration(T) * time.Millisecond)
	*wake <- true
}

func camera(vMatrix [][]*vertex, travelers []*traveler, m int, n int) {
	for {
		sendToTravelers(travelers, true)
		for i := 0; i < n; i++ {
			for j := 0; j < m; j++ {
				if vMatrix[i][j].currTraveler != nil {
					print(vMatrix[i][j].currTraveler.id)
				} else {
					print(freeVert)
				}

				// end the row
				if j < m-1 {
					print(horizontalPass)
				} else {
					println()
				}
			}

			// end the column
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
		sendToTravelers(travelers, false)
		time.Sleep(time.Millisecond * 750)
	}
}

func travSender(traveler *traveler, vMatrix [][]*vertex, m int, n int) {
	go timer(rand.Intn(5000), &traveler.timerChan)
	for {
		select {
		// stop for the camera
		case stop := <-traveler.freezeChan:
			for stop {
				stop = <-traveler.freezeChan
			}
		default:
			select {
			// death
			case <-traveler.deathChan:
				if traveler.currVertex != nil {
					traveler.currVertex.currTraveler = nil
				}
				return
			default:
				select {
				// timer says you good
				case <-traveler.timerChan:
					if traveler.currVertex != nil {
						X := traveler.currVertex.cord.x
						Y := traveler.currVertex.cord.y
						switch direction := rand.Intn(4); direction {
						case 0:
							// right
							if (X + 1) < n {
								travHandshake(traveler, vMatrix[X+1][Y])
							}
						case 1:
							// left
							if (X - 1) >= 0 {
								travHandshake(traveler, vMatrix[X-1][Y])
							}
						case 2:
							// down
							if (Y + 1) < m {
								travHandshake(traveler, vMatrix[X][Y+1])
							}
						case 3:
							// up
							if (Y - 1) >= 0 {
								travHandshake(traveler, vMatrix[X][Y-1])
							}
						}
					} else {
						randX := rand.Intn(m - 1)
						randY := rand.Intn(n - 1)
						travHandshake(traveler, vMatrix[randX][randY])
					}
					if traveler.currVertex != nil {
						traveler.isAlive = true
					}
					go timer(rand.Intn(500), &traveler.timerChan)
				default:
				}
			}
		}
	}
}

func vertexListener(vert *vertex) {
	for {
		traveler := <-vert.receive
		var response bool
		// vertex is empty
		if vert.currTraveler == nil {
			vert.currTraveler = traveler
			response = true
			// traveler wants to move in a vertex occupied by a drifter
		} else if vert.currTraveler.id == " *" && traveler.id != " *" {
			println(traveler.id, " wants to move in!")
			vert.currTraveler.receiveChan <- false
			response = <-vert.drifterChan
			// traveler wants to move in a vertex occupied by a danger
		} else if vert.currTraveler.id == " #" && traveler.id != " *" {
			println(traveler.id, " moves into danger!")
			vert.currTraveler.deathChan <- true
			traveler.deathChan <- true

		} else {
			response = false
		}
		// respond
		traveler.receiveChan <- response

		// receive move in request
	}
}

func travHandshake(traveler *traveler, toBeVertex *vertex) bool {
	// request
	toBeVertex.receive <- traveler
	// response
	response := <-traveler.receiveChan
	if response {
		//addToHistory(traveler, toBeVertex.cord)
		// move out
		if traveler.currVertex != nil {
			traveler.currVertex.currTraveler = nil
		}
		//move in
		traveler.currVertex = toBeVertex
		toBeVertex.currTraveler = traveler
	}
	return response
}

func sendToTravelers(travList []*traveler, stop bool) {
	for _, traveler := range travList {
		//println("sending to: ", index)
		traveler.freezeChan <- stop
		//println("sending done")
	}
}

func addToHistory(traveler *traveler, newCords coordinates) {
	traveler.moveHistory = append(traveler.moveHistory, newCords)
}

type drifter struct {
	traveler *traveler
	lifeTime int
}

type danger struct {
	drifter
}

type traveler struct {
	currVertex  *vertex
	moveHistory []coordinates
	id          string
	receiveChan chan bool
	deathChan   chan bool
	freezeChan  chan bool
	timerChan   chan bool
	isAlive     bool
}

type vertex struct {
	id           int
	cord         coordinates
	currTraveler *traveler
	drifterChan  chan bool
	receive      chan *traveler
}

func newDrifter() *drifter {
	drifter := drifter{traveler: newTraveler(" *"), lifeTime: 10000}
	return &drifter
}

func newDanger() *danger {
	drifter := drifter{traveler: newTraveler(" #"), lifeTime: 10000}
	danger := danger{drifter: drifter}
	return &danger
}

func newTraveler(id string) *traveler {
	traveler := traveler{
		id:          id,
		moveHistory: make([]coordinates, 0),
		receiveChan: make(chan bool, 2),
		freezeChan:  make(chan bool), // HOTFIX -> to be removed
		deathChan:   make(chan bool, 1),
		timerChan:   make(chan bool)}
	return &traveler
}

func newVertex(coordinates coordinates) *vertex {
	ver := vertex{
		receive:     make(chan *traveler),
		drifterChan: make(chan bool),
		cord:        coordinates}
	return &ver
}

type coordinates struct {
	x int
	y int
}
