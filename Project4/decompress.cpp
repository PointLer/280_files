#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main(int argc, char *argv[]) {
    //build Huffman Tree:
    HuffmanTree huffman = HuffmanTree(argv[1]);

    //open binary file:
    ifstream binaryFile;
    binaryFile.open(argv[2]);
    string line;
    getline(binaryFile, line);
    istringstream iStream(line);
    string code;

    //encode:
    while(iStream >> code){
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
            if(code == huffman.findPath(temp)){
                cout << temp;
                break;
            }
        }
    }
    cout << endl;

    binaryFile.close();
    return 0;
}
