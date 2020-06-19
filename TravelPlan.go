package main

import "fmt"

type unionGraph struct {
	graph []int
}

func (ug *unionGraph) init(size int) {
	ug.graph = make([]int,size+1)
	for i := 0 ; i<= size ; i++{
		ug.graph[i] = i
	}
}

func (ug unionGraph) getParent(node int) int{
	if  ug.graph[node] == node {
		return node
	} else {
		new_root := ug.getParent(ug.graph[node])
		return new_root
	}
}

func (ug *unionGraph) connect(from int, to []int) {
	for i, v := range to {
		if v == 1 {
			f:= ug.getParent(from)
			t:= ug.getParent(i+1)
			
			if(f<t) { // 자식 트리로 병합
				ug.graph[t] = f
			} else {
				ug.graph[f] = t
			}
		}
	}
}

func Run() {
	 N := 0
	 M := 0
	_, _ = fmt.Scan(&N, &M)

	var graph = make([][]int,N)
	for i :=0 ; i<N; i++ {
		graph[i] = make([]int,N)
		for j:=0 ; j<N; j++{
			_, _ = fmt.Scan(&graph[i][j])
		}
	}

	var path = make([]int,M)
	for i:=0 ; i<M; i++ {
		_, _ = fmt.Scan(&path[i])
	}

	travelGraph := &unionGraph{}
	travelGraph.init(N)

	for i:=0 ; i<N; i++ {
		travelGraph.connect(i+1,graph[i])
	}

	prev_value := travelGraph.getParent(path[0])
	for p:=1; p<len(path) - 1; p++ {
		if prev_value != travelGraph.getParent(path[p]) {
			fmt.Println("NO")
			return
		}
		prev_value = travelGraph.getParent(path[p])
	}
	fmt.Println("YES")
}

