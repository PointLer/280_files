//问题：空行会同时输出一个\n和' ',应该只有\n
#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void frequency_count(const char &line, int frequency[]);
    //REQUIRE: the size of the frequency array should be at least 28
    //EFFECT: update the frequency of each characters to the array (a-z in 0-25, ' 'in 26 and \n in 27)

bool cmp_huf(const Node* first, const Node* second);
    //EFFECT: decide the order of two node to be used in sort(), in descending order

int main(int argc, char *argv[]) {
    //read a file:
    char a_char;
    string line;
    ifstream iFile;
    iFile.open(argv[argc - 1]);

    //count the frequency:
    int frequency[28] = {0}; 
    a_char = iFile.get();
    while(a_char != EOF){
        frequency_count(a_char, frequency);
        a_char = iFile.get();
    }

    //build nodes:
    vector<Node*> huf_tree;
    for(int i = 0; i < 28; i++){
        string temp;
        if(i < 26){
            temp.push_back(i + 'a');
        }
        else if(i == 26){
            temp.push_back(' ');
        }
        else{
            temp.push_back('\n');
        }
        if(frequency[i] != 0){
            Node * new_node = new Node(temp, frequency[i]);
            huf_tree.push_back(new_node);
        }
    }

    //sort and merge:
    while(huf_tree.size() > 1){
        sort(huf_tree.begin(), huf_tree.end(), cmp_huf);
        int cur_size = huf_tree.size();
        Node* new_parent;
        new_parent = new_parent->mergeNodes(huf_tree[cur_size - 2], huf_tree[cur_size - 1]);
        huf_tree.pop_back();
        huf_tree.pop_back();//似乎没有delete,但是为什么没有报错嘞
        huf_tree.push_back(new_parent);
    }

    //build the Huffman Tree:
    HuffmanTree huffman = HuffmanTree(huf_tree[0]);
    if(argc == 3){
        huffman.printTree();
    }
    else{
        iFile.clear();
        iFile.seekg(0, ios::beg);
        while(getline(iFile, line)){
            for(int j = 0; j < (int)line.size(); j++){
                string path;
                path.push_back(line[j]);
                cout << huffman.findPath(path) << " ";
            }
            cout << huffman.findPath("\n") << " ";
        }
        cout << endl;
    }

    iFile.close();
    return 0;
}

void frequency_count(const char &line, int frequency[]){
    if('a' <= line && line <= 'z'){
        frequency[(int)(line - 'a')] ++;
    }
    else if(line == ' ')
        frequency[26] ++;
    else if(line == '\n')  
        frequency[27] ++;
}

bool cmp_huf(const Node* first, const Node* second){//降序排列，最小的在队尾
    if(first->getnum() != second->getnum()){
        return first->getnum() > second->getnum();
    }
    return first->getstr() > second->getstr();
}