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
	//for i := 0; i < 2; i++ {
	//	drifter := newDrifter()
	//	travelers = append(travelers, drifter.traveler)
	//	go drifterLife(drifter, vMatrix, m, n)
	//}

	//nDangers := 3
	//for i := 0; i < nDangers; i++ {
	//	danger := newDanger()
	//	travelers = append(travelers, danger.drifter.traveler)
	//	go dangerLife(danger, vMatrix, m, n)
	//}

	cameraFreezerChannel := make(chan bool)
	freezerCameraChannel := make(chan bool)
	go freezer(travelers, &cameraFreezerChannel, &freezerCameraChannel)
	go camera(vMatrix, &cameraFreezerChannel, &freezerCameraChannel, m, n)

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
			// time run out, you're invisible
		default:
			select {
			case <-danger.drifter.traveler.deathChan:
				danger.drifter.traveler.currVertex.currTraveler = nil
				danger.drifter.traveler.isAlive = false
				println("danger is dead!")
				return
				// DANGER DIES FOR REAL
			default:
				select {
				case <-danger.drifter.traveler.timerChan:
					// move out
					danger.drifter.traveler.isVisible = false
					danger.drifter.traveler.currVertex.currTraveler = nil
					danger.drifter.traveler.currVertex = nil
				default:
					if !danger.drifter.traveler.isVisible {
						// come to life
						if rand.Intn(5) == 0 {

							randX := rand.Intn(m - 1)
							randY := rand.Intn(n - 1)
							for !travHandshake(danger.drifter.traveler, vMatrix[randX][randY]) {
								randX = rand.Intn(m - 1)
								randY = rand.Intn(n - 1)
							}

							danger.drifter.traveler.isVisible = true
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
				drifter.traveler.isVisible = false
				// move out
				drifter.traveler.currVertex.currTraveler = nil
				drifter.traveler.currVertex = nil
				//println("drifter is dead!")
				// find other place and move
			case <-drifter.traveler.receiveChan:
				X := drifter.traveler.currVertex.cord.x
				Y := drifter.traveler.currVertex.cord.y
				oldChannel := drifter.traveler.currVertex.drifterChan
				if ((X+1 < n) && travHandshake(drifter.traveler, vMatrix[X+1][Y])) ||
					((X-1 >= 0) && travHandshake(drifter.traveler, vMatrix[X-1][Y])) ||
					((Y+1 < m) && travHandshake(drifter.traveler, vMatrix[X][Y+1])) ||
					((Y-1 >= 0) && travHandshake(drifter.traveler, vMatrix[X][Y-1])) {
					//println("drifter found a spot!")
					oldChannel <- true
				} else {
					println("drifter did not find a spot!")
					oldChannel <- false
				}
			default:
				if !drifter.traveler.isVisible {
					// come to life
					if rand.Intn(5) == 0 {
						drifter.traveler.isVisible = true

						randX := rand.Intn(m - 1)
						randY := rand.Intn(n - 1)
						for !travHandshake(drifter.traveler, vMatrix[randX][randY]) {
							randX = rand.Intn(m - 1)
							randY = rand.Intn(n - 1)
						}

						go timer(drifter.lifeTime, &drifter.traveler.timerChan)
						// stay dead
					} else {
						//time.Sleep(time.Duration(rand.Intn(500)) * time.Millisecond)
						time.Sleep(time.Duration(2000) * time.Millisecond)
					}
				}
			}
		}
	}
}

func timer(T int, wakeChan *chan bool) {
	time.Sleep(time.Duration(T) * time.Millisecond)
	*wakeChan <- true
}

func freezer(travList []*traveler, cameraFreezerChannel *chan bool, freezerCameraChannel *chan bool) {
	for {
		select {
		case stopStart := <-*cameraFreezerChannel:
			for _, trav := range travList {
				if trav.isAlive {
					trav.freezeChan <- stopStart
				}
			}
			*freezerCameraChannel <- stopStart
		default:
		}
	}
}

func camera(vMatrix [][]*vertex, cameraFreezerChannel *chan bool, freezerCameraChannel *chan bool, m int, n int) {
	for {
		*cameraFreezerChannel <- true
		<-*freezerCameraChannel

		var board [][]*boardField
		for i := 0; i < 2*n-1; i++ {
			var boardRow []*boardField
			for j := 0; j < 2*m-1; j++ {
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

		for i := 0; i < n; i++ {
			for j := 0; j < m; j++ {
				currVert := vMatrix[i][j]
				if currVert.currTraveler != nil {
					// emplace traveler
					board[i*2][j*2].val = currVert.currTraveler.id
					board[i*2][j*2].isVisible = true
					for k := 1; k < len(currVert.currTraveler.moveHistory); k++ {
						startX := currVert.currTraveler.moveHistory[k-1].x * 2
						startY := currVert.currTraveler.moveHistory[k-1].y * 2
						endX := currVert.currTraveler.moveHistory[k].x * 2
						endY := currVert.currTraveler.moveHistory[k].y * 2
						if endY > startY {
							board[startX][startY+1].isVisible = true
						} else if endY < startY {
							board[startX][startY-1].isVisible = true
						}
						if endX > startX {
							board[startX+1][startY].isVisible = true
						} else if endX < startX {
							board[startX-1][startY].isVisible = true
						}
					}
					currVert.currTraveler.moveHistory = make([]coordinates, 0)
					currVert.currTraveler.moveHistory = append(currVert.currTraveler.moveHistory, vMatrix[i][j].cord)
				}
			}
		}

		//for i := 0; i < n; i++ {
		//	for j := 0; j < m; j++ {
		//		if vMatrix[i][j].currTraveler != nil {
		//			print(vMatrix[i][j].currTraveler.id)
		//		} else {
		//			print("..")
		//		}
		//
		//		// end the row
		//		if j < m-1 {
		//			print("---")
		//		} else {
		//			println()
		//		}
		//	}
		//
		//	// end the column
		//	if i < n-1 {
		//		for c := 0; c < m; c++ {
		//			print("|")
		//			if c < m-1 {
		//				print("    ")
		//			} else {
		//				println()
		//			}
		//		}
		//	}
		//}

		for i := 0; i < 2*n-1; i++ {
			for j := 0; j < 2*m-1; j++ {
				if board[i][j].isVisible {
					print(board[i][j].val)
				} else {
					spaces := strings.Repeat(" ", utf8.RuneCountInString(board[i][j].val))
					print(spaces)
				}
			}
			println()
		}
		println()
		println()

		*cameraFreezerChannel <- false
		<-*freezerCameraChannel
		time.Sleep(time.Duration(1000) * time.Millisecond)
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
				// move out
				if traveler.currVertex != nil {
					traveler.currVertex.currTraveler = nil
				}
				// suicide
				traveler.isAlive = false
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
						if traveler.currVertex != nil {
							traveler.isVisible = true
						}
					}
					//go timer(rand.Intn(750), &traveler.timerChan)
					go timer(2000, &traveler.timerChan)
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
			//println(traveler.id, " wants to move in!")
			vert.currTraveler.receiveChan <- false
			response = <-vert.drifterChan
			// traveler wants to move in a vertex occupied by a danger
		} else if vert.currTraveler.id == " #" && traveler.id != " *" && traveler.id != " #" {
			//println(traveler.id, " moves into danger!")
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
	return response
}

type drifter struct {
	traveler *traveler
	lifeTime int
}

type danger struct {
	drifter
}

type boardField struct {
	val       string
	isVisible bool
}

type traveler struct {
	id        string
	isVisible bool
	isAlive   bool

	receiveChan chan bool
	deathChan   chan bool
	freezeChan  chan bool
	timerChan   chan bool

	currVertex  *vertex
	moveHistory []coordinates
}

type vertex struct {
	drifterChan chan bool
	receive     chan *traveler

	cord         coordinates
	currTraveler *traveler
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
		isAlive:     true,
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
