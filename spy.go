/*
Go 문법 연습겸 풀어본 문제.
DFS 로 모든 Case 를 찾아서 해결하는 문제인 줄 알고 열심히 DFS 로 풀었더니 시간초과...
어디서 가지치기를 해야하나 한시간을 고민했지만 생각해보니 그냥 카테고리마다 경우의수를 찾아
전부 곱해주고, 하나도 안입은 케이스 하나를 빼주면 되는 문제였다.
아주 허탈하다.....
*/



var count int = 0
//잘못된 풀이 1 
func findCases(keyMap []string, clothsTree map[string][]string, currentDepth int) {
	if len(keyMap) == currentDepth {
		count++
		return
	}

	currentKey := keyMap[currentDepth]
	for i := 0; i < len(clothsTree[currentKey]); i++ {
		findCases(keyMap, clothsTree, currentDepth+1)
	}
}
//맞는 풀이
func findCases2(clothsTree map[string][]string) int {
	caseSum := 1
	for _, v := range clothsTree {
		caseSum *= len(v)
	}
	return caseSum - 1
}

func solution(clothes [][]string) int {
	clothsTree := make(map[string][]string)
	for _, elem := range clothes {
		key := elem[1]
		val := elem[0]
		clothsTree[key] = append(clothsTree[key], val)
	}

	// go 는 map 에서 key 의 순서를 보장하지 않는다. DFS 를 위해 keymap을 만들자
	var keyMap []string
	for k := range clothsTree {
		keyMap = append(keyMap, k)
	}

	//key 별로 안입는 케이스 추가
	for _, key := range keyMap {
		clothsTree[key] = append(clothsTree[key], "none")
	}

	// then DFS.
	//findCases(keyMap, clothsTree, 0) //이렇게 푸는게 아니라니....
	return findCases2(clothsTree)
}
