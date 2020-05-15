// 트라이 공부한 김에 풀어본 문제
// 순수하게 트라이를 구현해서 풀면 풀리는 문제이다.

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Node{
    public:
        Node(string val){
        value = val;
        end = false;
    }
    string value;
    map<char,Node*> child;
    bool end;
};

class NodeTree{
    public:
    Node* root = new Node("");

    void insert(string str){
        Node* currentNode = root;

        for(int i = 0; i<str.length() ; i++){
            char currentChar = str[i];
            if( currentNode->child.find(currentChar) == currentNode->child.end() ){
                string acc = currentNode->value + currentChar;
                currentNode->child.insert((make_pair(currentChar,new Node(acc))));
            }
            currentNode = currentNode->child[currentChar];
        }
        currentNode->end = true;
    }

    int search(string str){
        Node* currentNode = root;

        for(int i = 0; i<str.length() ; i++){
            char currentChar = str[i];
            if( currentNode->child.find(currentChar) != currentNode->child.end() ){
                currentNode = currentNode->child[currentChar];
            } else {
                if(!currentNode->child.empty()){
                    return false;
                }
            }
        }
        if(currentNode->child.empty()){
            return true;
        }
        return false;
    }
};

bool solution(vector<string> phone_book) {
    bool answer = true;
    NodeTree trie = NodeTree();

    for(int i = 0 ; i< phone_book.size(); i++) {
        trie.insert(phone_book[i]);
    }

    for(int i = 0 ; i< phone_book.size(); i++) {
        answer = trie.search(phone_book[i]);
        if (answer == false) return answer;
    }

    return answer;
}
