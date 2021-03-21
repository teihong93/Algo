/*

golang 을 연습할 겸 유명한 부분합 문제를 한번 풀어보았습니다.
golang 은 왜 이렇게 입출력이 느린지... 입출력 할때마다 귀찮아 죽겠습니다.
배열 초기화하는것도 묘하게 귀찮아서 문제풀기가 아주 번거롭네요.

*/

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

type doubleAry [][]int

func (da doubleAry) calculatePsum() doubleAry {

	aLen := len(da)
	tempDa := make(doubleAry, aLen)
	for i := 0; i < aLen; i++ {
		tempDa[i] = make([]int, aLen)
	}

	for i := 1; i < aLen; i++ {
		for j := 1; j < aLen; j++ {
			tempDa[i][j] = da[i][j] + tempDa[i-1][j] + tempDa[i][j-1] - tempDa[i-1][j-1]
		}
	}
	return tempDa
}

func (da doubleAry) calculatePsumValue(y1 int, x1 int, y2 int, x2 int) int {
	return da[y2][x2] - da[y1-1][x2] - da[y2][x1-1] + da[y1-1][x1-1]
}

func main() {

	scanner := bufio.NewReader(os.Stdin)
	stdout := bufio.NewWriter(os.Stdout)

	var N, M int
	fmt.Fscan(scanner, &N, &M)

	da := make(doubleAry, N+1)
	for i := 0; i <= N; i++ {
		da[i] = make([]int, N+1)
	}

	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			fmt.Fscan(scanner, &da[i+1][j+1])
		}
	}

	memoArray := da.calculatePsum()

	for i := 0; i < M; i++ {
		ip := make([]int, 4)
		for j, _ := range ip {
			fmt.Fscan(scanner, &ip[j])
		}
		stdout.WriteString(strconv.Itoa(memoArray.calculatePsumValue(ip[0], ip[1], ip[2], ip[3])) + "\n")
	}
	stdout.Flush()
}
