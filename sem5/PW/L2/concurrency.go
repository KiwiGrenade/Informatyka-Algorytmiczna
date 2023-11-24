package main

import (
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"
	"unicode/utf8"
)

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

	// create 2d table with vertices and fire vertexServerListener go.subroutines
	var vMatrix [][]*vertex
	for i := 0; i < n; i++ {
		var vertexRow []*vertex
		for j := 0; j < m; j++ {
			ver := newVertex(coordinates{i, j})

			vertexRow = append(vertexRow, ver)
			go vertexServerListener(ver)
		}
		vMatrix = append(vMatrix, vertexRow)
	}

	// create a list of travelers and fire travelerLife go.subroutines
	travelers := make([]*traveler, 0, n*m)
	for i := 0; i < k; i++ {
		id := ""
		if i < 10 {
			id += "0"
		}
		id += strconv.Itoa(i)
		trav := newTraveler(id)
		travelers = append(travelers, trav)
		go travelerLife(trav, vMatrix, m, n)
	}

	// TODO: programme blocks when spawning drifters/dangers with travelers
	drifters := make([]*drifter, 0, n*m)
	//nDrifters := rand.Intn(n*m - k)
	nDrifters := n*m - k
	for i := 0; i < nDrifters; i++ {
		var id string
		//if rand.Intn(4) == 0 {
		id = " #"
		//} else {
		//id = " *"
		//}
		drifter := newDrifter(id)
		drifters = append(drifters, drifter)
		travelers = append(travelers, drifter.traveler)
	}

	cameraFreezerChannel := make(chan bool)
	freezerCameraChannel := make(chan bool)
	freezerDrifterSpawnerChannel := make(chan bool)
	go drifterSpawnerLife(drifters, vMatrix, freezerDrifterSpawnerChannel, m, n)
	go freezerLife(travelers, cameraFreezerChannel, freezerCameraChannel, freezerDrifterSpawnerChannel)
	go cameraLife(vMatrix, travelers, cameraFreezerChannel, freezerCameraChannel)

	select {}
}

func timerLife(T int, wakeChan *chan bool) {
	time.Sleep(time.Duration(T) * time.Millisecond)
	*wakeChan <- true
	return
}

func freezerLife(travelers []*traveler, cameraFreezerChannel chan bool, freezerCameraChannel chan bool, freezerDrifterSpawnerChannel chan bool) {
	for {
		select {
		// receive signal from cameraLife
		case stopStart := <-cameraFreezerChannel:
			// notify spawner
			freezerDrifterSpawnerChannel <- stopStart
			// notify all live travelers
			for _, traveler := range travelers {
				if traveler.isAlive {
					//println("sending to", traveler.id)
					traveler.freezeChan <- stopStart
					//println("sent to", traveler.id)
				}
			}
			// notify cameraLife that all travellers stopped
			freezerCameraChannel <- stopStart
		default:
		}
	}
}

func cameraLife(vMatrix [][]*vertex, travelers []*traveler, cameraFreezerChannel chan bool, freezerCameraChannel chan bool) {
	for {
		// notify freezerLife to stop travelers
		cameraFreezerChannel <- true
		// wait for freezers response
		<-freezerCameraChannel
		//println("Taking picture")

		boardWidth := 2*len(vMatrix) - 1
		boardHeight := 2*len(vMatrix[0]) - 1

		// make board and set all the fields
		var board [][]*boardField
		for i := 0; i < boardWidth; i++ {
			var boardRow []*boardField
			for j := 0; j < boardHeight; j++ {
				var val string
				isVisible := false
				if i%2 != 0 {
					// vertical pass
					if j%2 == 0 {
						val = "|"
					} else {
						val = "    "
					}
				} else {
					if j%2 == 0 {
						val = ".."
						isVisible = true
					} else {
						val = "---"
					}
				}
				field := &boardField{val: val, isVisible: isVisible}
				boardRow = append(boardRow, field)
			}
			board = append(board, boardRow)
		}

		// track back the move history and show the edges
		for _, trav := range travelers {
			if trav.currVertex != nil {
				X := trav.currVertex.cord.x
				Y := trav.currVertex.cord.y

				// set traveler id on board and make it visible
				board[X*2][Y*2].val = trav.id
				board[X*2][Y*2].isVisible = true

				for k := 1; k < len(trav.moveHistory); k++ {
					startX := trav.moveHistory[k-1].x * 2
					startY := trav.moveHistory[k-1].y * 2
					endX := trav.moveHistory[k].x * 2
					endY := trav.moveHistory[k].y * 2

					// down
					if endY > startY {
						board[startX][startY+1].isVisible = true
						// up
					} else if endY < startY {
						board[startX][startY-1].isVisible = true
					}
					// right
					if endX > startX {
						board[startX+1][startY].isVisible = true
						// left
					} else if endX < startX {
						board[startX-1][startY].isVisible = true
					}
				}
				// remove coords
				trav.moveHistory = make([]coordinates, 0)
				// because we removed all coordinates, we also removed current position. Add it back
				trav.moveHistory = append(trav.moveHistory, trav.currVertex.cord)
			}
		}

		// print the whole board
		for _, boardRow := range board {
			for _, vertex := range boardRow {
				if vertex.isVisible {
					print(vertex.val)
				} else {
					spaces := strings.Repeat(" ", utf8.RuneCountInString(vertex.val))
					print(spaces)
				}
			}
			println()
		}
		println()
		println()

		// tell freezerLife to unfreeze all travelers
		cameraFreezerChannel <- false
		// wait for response
		<-freezerCameraChannel
		//println("End of picture")
		time.Sleep(time.Duration(2000) * time.Millisecond)
	}
}

func suicide(traveler *traveler) {
	traveler.isAlive = false
	if traveler.currVertex != nil {
		traveler.currVertex.currTraveler = nil
	}
	traveler.currVertex = nil
	traveler.moveHistory = make([]coordinates, 0)
	return
}

func drifterSpawnerLife(drifters []*drifter, vMatrix [][]*vertex, freezerChannel chan bool, m int, n int) {
	timerChannel := make(chan bool)
	go timerLife(1000, &timerChannel)
	for {
		select {
		case stop := <-freezerChannel:
			for stop {
				stop = <-freezerChannel
			}
		default:
			select {
			case <-timerChannel:
				//println("Spawning new recruits?")
				for _, drifter := range drifters {
					if drifter.traveler.currVertex == nil && !drifter.traveler.isAlive {
						if rand.Intn(10) == 0 {
							drifter.traveler.isAlive = true
							if drifter.traveler.id == " *" {
								go drifterLife(drifter, vMatrix, m, n)
							} else {
								go dangerLife(drifter, vMatrix, m, n)
							}
						}
					}
				}
				go timerLife(1000, &timerChannel)
			default:
			}
		}
	}
}

func dangerLife(danger *drifter, vMatrix [][]*vertex, m int, n int) {
	pickFreeVertex(danger.traveler, vMatrix, m, n)
	go timerLife(danger.lifeTime, &danger.traveler.timerChan)
	for {
		select {
		// stop for the cameraLife
		case stop := <-danger.traveler.freezeChan:
			for stop {
				stop = <-danger.traveler.freezeChan
			}
		default:
			select {
			case <-danger.traveler.deathChan:
				suicide(danger.traveler)
			// DANGER DIES FOR REAL
			case <-danger.traveler.timerChan:
				suicide(danger.traveler)
			default:
			}
		}
	}
}

func drifterLife(drifter *drifter, vMatrix [][]*vertex, m int, n int) {
	pickFreeVertex(drifter.traveler, vMatrix, m, n)
	go timerLife(drifter.lifeTime, &drifter.traveler.timerChan)
	for {
		select {
		// stop for the cameraLife
		case stop := <-drifter.traveler.freezeChan:
			for stop {
				stop = <-drifter.traveler.freezeChan
			}
		default:
			select {
			case <-drifter.traveler.timerChan:
				suicide(drifter.traveler)
			default:
				select {
				// find other place and move
				case <-drifter.traveler.moveChan:
					X := drifter.traveler.currVertex.cord.x
					Y := drifter.traveler.currVertex.cord.y
					oldChannel := drifter.traveler.currVertex.vertDriftChan
					// try to move
					canMove := false
					if ((X+1 < m) && travHandshake(drifter.traveler, vMatrix[X+1][Y])) ||
						((X-1 >= 0) && travHandshake(drifter.traveler, vMatrix[X-1][Y])) ||
						((Y+1 < n) && travHandshake(drifter.traveler, vMatrix[X][Y+1])) ||
						((Y-1 >= 0) && travHandshake(drifter.traveler, vMatrix[X][Y-1])) {
						canMove = true
					} else {
						println("drifter did not find a spot!")
						canMove = false
					}
					// respond
					oldChannel <- canMove
				default:
				}
			}
		}
	}
}

func travelerLife(traveler *traveler, vMatrix [][]*vertex, m int, n int) {
	// create initial timerLife
	pickFreeVertex(traveler, vMatrix, m, n)
	go timerLife(rand.Intn(5000), &traveler.timerChan)
	traveler.isAlive = true
	for {
		// cascading select - makes creating channel priority hierarchy possible
		select {
		// stop for the cameraLife
		case stop := <-traveler.freezeChan:
			for stop {
				stop = <-traveler.freezeChan
			}
		default:
			select {
			// death
			case <-traveler.deathChan:
				// move out
				suicide(traveler)
			default:
				select {
				// timerLife says to make a move
				case <-traveler.timerChan:
					// not first move (traveler already spawned)
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
					}
					//go timerLife(rand.Intn(1000), &traveler.timerChan)
					go timerLife(1000, &traveler.timerChan)
				default:
				}
			}
		}
	}
}

func vertexServerListener(vert *vertex) {
	for {
		select {
		case traveler := <-vert.receive:
			var response bool
			// vertex is empty
			if vert.currTraveler == nil {
				vert.currTraveler = traveler
				response = true

				// traveler wants to move in a vertex occupied by a drifter
			} else if vert.currTraveler.id == " *" && traveler.id != " *" {
				vert.currTraveler.receiveChan <- false
				response = <-vert.vertDriftChan

				// traveler wants to move in a vertex occupied by a danger
			} else if vert.currTraveler.id == " #" && traveler.id != " *" && traveler.id != " #" {
				vert.currTraveler.deathChan <- true
				traveler.deathChan <- true
				println(traveler.id, " must die!")
			} else {
				response = false
			}
			// respond
			traveler.receiveChan <- response
		default:
		}
	}
}

func travHandshake(traveler *traveler, toBeVertex *vertex) bool {
	// request
	toBeVertex.receive <- traveler
	// response
	response := <-traveler.receiveChan
	//println("received response")
	if response {
		// add to history
		traveler.moveHistory = append(traveler.moveHistory, toBeVertex.cord)

		// move out
		if traveler.currVertex != nil {
			traveler.currVertex.currTraveler = nil
		}

		// move in
		traveler.currVertex = toBeVertex
		toBeVertex.currTraveler = traveler
	}
	//println("received response")
	return response
}

func pickFreeVertex(traveler *traveler, vMatrix [][]*vertex, m int, n int) {
	randX := rand.Intn(m)
	randY := rand.Intn(n)
	// pick drifters vertex
	for !travHandshake(traveler, vMatrix[randX][randY]) {
		randX = rand.Intn(m)
		randY = rand.Intn(n)
	}
	println(traveler.id, " chose [", randX, ",", randY, "]")
}

type drifter struct {
	traveler *traveler
	//isVisible bool
	lifeTime int
}

type boardField struct {
	val       string
	isVisible bool
}

type traveler struct {
	id      string
	isAlive bool

	receiveChan chan bool
	moveChan    chan bool
	deathChan   chan bool
	freezeChan  chan bool
	timerChan   chan bool

	currVertex  *vertex
	moveHistory []coordinates
}

type vertex struct {
	vertDriftChan chan bool
	receive       chan *traveler

	cord         coordinates
	currTraveler *traveler
}

func newDrifter(id string) *drifter {
	drifter := drifter{traveler: newTraveler(id), lifeTime: 10000}
	return &drifter
}

func newTraveler(id string) *traveler {
	traveler := traveler{
		id:          id,
		isAlive:     false,
		moveHistory: make([]coordinates, 0),
		receiveChan: make(chan bool),
		freezeChan:  make(chan bool),
		moveChan:    make(chan bool),
		deathChan:   make(chan bool),
		timerChan:   make(chan bool)}
	return &traveler
}

func newVertex(coordinates coordinates) *vertex {
	ver := vertex{
		receive:       make(chan *traveler),
		vertDriftChan: make(chan bool),
		cord:          coordinates}
	return &ver
}

type coordinates struct {
	x int
	y int
}
