package main

import (
	"math/rand"
	"os"
	"strconv"
	"time"
)

var verPass = "---"
var spacing = "    "

func main() {

	args := os.Args[1:]

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

	moves := ""
	var vMatrix [][]*vertex
	travelers := make([]*traveler, 0, n*m)

	// create 2d table with vertices and fire listener go.subroutines
	for i := 0; i < n; i++ {
		var vertexRow []*vertex
		for j := 0; j < m; j++ {
			ver := newVertex("  ", make(chan *traveler), i, j)
			vertexRow = append(vertexRow, ver)
			go listener(&moves, ver)
		}
		vMatrix = append(vMatrix, vertexRow)
	}

	// create a list of travelers and fire sender go.subroutines
	for i := 0; i < k; i++ {
		trav := newTraveler(i)
		travelers = append(travelers, trav)
		go sender(trav, vMatrix, m, n)
	}

	go camera(&moves, vMatrix, m, n)

	select {}
}

func camera(routes *string, vMatrix [][]*vertex, m int, n int) {
	for {
		for i := 0; i < n; i++ {
			for j := 0; j < m; j++ {
				// add 0 if the locator ID has 1 digit only
				str := ""
				locID, errLoc := strconv.Atoi(vMatrix[i][j].locator)
				if errLoc == nil {
					if locID < 10 {
						str += "0"
					}
					str += vMatrix[i][j].locator
					print(str)
				} else {
					print(vMatrix[i][j].locator)
				}
				if j < m-1 {
					print(verPass)
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
		println(*routes)
		*routes = ""
		println()
		time.Sleep(time.Millisecond * 750)
	}
}

func sender(trav *traveler, vMatrix [][]*vertex, m int, n int) {
	for {
		// traveler does not have a vertex
		V := trav.currVertex
		if V != nil {
			X := trav.currVertex.x
			Y := trav.currVertex.y
			switch direction := rand.Intn(4); direction {
			case 0:
				// right
				if ((X + 1) < n) && (vMatrix[X+1][Y].traveler == nil) {
					vMatrix[X+1][Y].channel <- trav
				}
			case 1:
				// left
				if ((X - 1) >= 0) && (vMatrix[X-1][Y].traveler == nil) {
					vMatrix[X-1][Y].channel <- trav
				}
			case 2:
				// down
				if ((Y + 1) < m) && (vMatrix[X][Y+1].traveler == nil) {
					vMatrix[X][Y+1].channel <- trav
				}
			case 3:
				// up
				if ((Y - 1) > 0) && (vMatrix[X][Y-1].traveler == nil) {
					vMatrix[X][Y-1].channel <- trav
				}
			}
			// traveler has a vertex
		} else {
			randX := rand.Intn(m - 1)
			randY := rand.Intn(n - 1)
			// no traveler in place
			if vMatrix[randY][randX].traveler == nil {
				r := rand.Intn(10000)
				time.Sleep(time.Duration(r) * time.Millisecond)
				vMatrix[randY][randX].channel <- trav
			}
		}

		r := rand.Intn(500)
		time.Sleep(time.Duration(r) * time.Millisecond)
	}

}

func listener(routes *string, vert *vertex) {
	for {
		k := <-vert.channel
		vert.traveler = k
		vert.locator = strconv.Itoa(k.id)
		if k.currVertex != nil {
			id := ""
			if vert.traveler.id < 10 {
				id = "0"
			}
			id += strconv.Itoa(vert.traveler.id)
			x1 := strconv.Itoa(k.currVertex.x)
			y1 := strconv.Itoa(k.currVertex.y)
			x2 := strconv.Itoa(vert.x)
			y2 := strconv.Itoa(vert.y)
			*routes += id + ":[" + x1 + "," + y1 + "]=>[" + x2 + "," + y2 + "]; "

			k.currVertex.locator = "  "
			k.currVertex.traveler = nil
		}
		k.currVertex = vert
	}
}

type traveler struct {
	currVertex *vertex
	xCord      int
	yCord      int
	id         int
}
type vertex struct {
	id       int
	x        int
	y        int
	locator  string
	traveler *traveler
	channel  chan *traveler
}

func newVertex(locatorSymbol string, channel chan *traveler, x int, y int) *vertex {
	ver := vertex{locator: locatorSymbol, channel: channel, x: x, y: y}
	return &ver
}

func newTraveler(id int) *traveler {
	traveler := traveler{id: id}
	return &traveler
}
