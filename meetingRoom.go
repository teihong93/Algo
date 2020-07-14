package main
import "fmt"
import "sort"
import "bufio"
import "os"

type doubleAry [][]int

func (da doubleAry) Len() int           { return len(da) }
func (da doubleAry) Swap(i, j int)      { da[i], da[j] = da[j], da[i] }
func (da doubleAry) Less(i, j int) bool {
	if list[i][1] == list[j][1] {
		return list[i][0] < list[j][0]
	} else {
		return list[i][1] < list[j][1]
	}
}

func (da doubleAry) OverLay(endTime,i int) bool {return da[i][0] < endTime }

func main(){

	scanner := bufio.NewReader(os.Stdin)

	var N int
	fmt.Fscan(scanner, &N)

	var list = make(doubleAry,0,100001)

	for i:=0; i<N; i++ {
		var start,end int
		fmt.Fscan(scanner, &start,&end)
		list = append(list,[]int{start,end})
	}

	sort.Sort(list)
	count := 0
	init_end := 0

	for i := 0; i< len(list); i++ {
		if !list.OverLay(init_end,i) {
			count++
			init_end = list[i][1]
		}
	}
	fmt.Println(count)
}