#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) {
    // TODO: implement this function.
    this->str = str;
    this->num = num;
    this->left = left;
    this->right = right;
}

Node* Node::leftSubtree() const{
    // TODO: implement this function.  
    return this->left;
}

void Node::setleft(Node *n) {
    // TODO: implement this function.  
    this->left = n;
}

Node* Node::rightSubtree() const{
    // TODO: implement this function. 
    return this->right; 
}

void Node::setright(Node *n) {
    // TODO: implement this function.  
    this->right = n;
}

string Node::getstr() const {
    // TODO: implement this function.  
    return this->str;
}

int Node::getnum() const {
    // TODO: implement this function.  
    return this->num;
}

void Node::incnum() {
    // TODO: implement this function.
    this->num ++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {//这里用了dynamic
    // TODO: implement this function.
    Node *new_node = new Node(leftNode->str + rightNode->str, leftNode->num + rightNode->num, leftNode, rightNode);
    return new_node;
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode){
    // TODO: implement this function.
    this->root = rootNode;
}

static void destroy_helper(Node *rootNode){
    if(rootNode == nullptr){
        return;
    }
    if(rootNode->leftSubtree() != nullptr){
        destroy_helper(rootNode->leftSubtree());
    }
    if(rootNode->rightSubtree() != nullptr){
        destroy_helper(rootNode->rightSubtree());
    }
    delete rootNode;
}

BinaryTree::~BinaryTree() {//需要多品品（就是不确定是不是都是dynamic）
    // TODO: implement this function.
    destroy_helper(this->root);
}

static string findPath_helper(const string &s, string res, Node *cur){
    if(cur == nullptr)
        return "-1";
    if(cur->getstr() == s)
        return res;
    else if(findPath_helper(s, res + "0", cur->leftSubtree()) != "-1")
        return findPath_helper(s, res + "0", cur->leftSubtree());
    else if(findPath_helper(s, res + "1", cur->rightSubtree()) != "-1")
        return findPath_helper(s, res + "1", cur->rightSubtree());
    return "-1";
}

string BinaryTree::findPath(const string &s) const{
    // TODO: implement this function.
    return findPath_helper(s, "", this->root);
}

static int sum_helper(Node *cur, int res){
    if(cur == nullptr){
        return res;
    }
    return res + cur->getnum() + sum_helper(cur->leftSubtree(), 0) + sum_helper(cur->rightSubtree(), 0);
}

int BinaryTree::sum() const {
    // TODO: implement this function.
    return sum_helper(this->root, 0);
}

static int depth_helper(Node *cur, int depth){
    if(cur == nullptr){
        return depth;
    }
    depth++;
    if(depth_helper(cur->leftSubtree(), depth) > depth_helper(cur->rightSubtree(), depth)){
        return depth_helper(cur->leftSubtree(), depth);
    }
    return depth_helper(cur->rightSubtree(), depth);
}

int BinaryTree::depth() const {
    // TODO: implement this function.
    return depth_helper(this->root, 0);
}

static void preorder_num_helper(Node *cur){
    if(cur == nullptr){
        return;
    }
    std::cout << cur->getnum() << " ";
    preorder_num_helper(cur->leftSubtree());
    preorder_num_helper(cur->rightSubtree());
}

void BinaryTree::preorder_num() const {
    // TODO: implement this function.
    preorder_num_helper(this->root);
    std::cout << std::endl;
}

static void inorder_str_helper(Node *cur){
    if(cur == nullptr){
        return;
    }
    inorder_str_helper(cur->leftSubtree());
    std::cout << cur->getstr() << " ";
    inorder_str_helper(cur->rightSubtree());
}

void BinaryTree::inorder_str() const {
    // TODO: implement this function.
    inorder_str_helper(this->root);
    std::cout << std::endl;
}

static void postorder_num_helper(Node *cur){
    if(cur == nullptr){
        return;
    }
    postorder_num_helper(cur->leftSubtree());
    postorder_num_helper(cur->rightSubtree());
    std::cout << cur->getnum() << " ";
}

void BinaryTree::postorder_num() const {
    // TODO: implement this function.
    postorder_num_helper(this->root);
    std::cout << std::endl;
}

static bool allPathSumGreater_helper(int sum, Node *cur){
    if(cur == nullptr){
        if(sum < 0) return true;
        else return false;
    }
    return allPathSumGreater_helper(sum - cur->getnum(), cur->leftSubtree()) 
        && allPathSumGreater_helper(sum - cur->getnum(), cur->rightSubtree());
}

bool BinaryTree::allPathSumGreater(int sum) const {
    // TODO: implement this function.
    return allPathSumGreater_helper(sum, this->root);
}

static bool covered_by_helper(Node *this_tree, Node *input_tree){
    if(this_tree == nullptr)
        return true;
    else if(input_tree == nullptr)
        return false;
    if(this_tree->getnum() != input_tree->getnum())
        return false;
    return covered_by_helper(this_tree->leftSubtree(), input_tree->leftSubtree())
        && covered_by_helper(this_tree->rightSubtree(), input_tree->rightSubtree());
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    return covered_by_helper(this->root, tree.root);
}

static bool contained_by_helper(Node *this_tree, Node *input_tree){
    if(this_tree == nullptr)
        return true;
    else if(input_tree == nullptr)
        return false;
    return covered_by_helper(this_tree, input_tree)
        || covered_by_helper(this_tree, input_tree->leftSubtree())
        || covered_by_helper(this_tree, input_tree->rightSubtree());
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    return contained_by_helper(this->root, tree.root);
}

static Node* copy_helper(Node *copy_from){
    if(copy_from == nullptr)
        return nullptr;
    Node* new_tree = new Node(copy_from->getstr(), copy_from->getnum());
    new_tree->setleft(copy_helper(copy_from->leftSubtree()));
    new_tree->setright(copy_helper(copy_from->rightSubtree()));
    return new_tree;
}

BinaryTree BinaryTree::copy() const {
    // TODO: implement this function.(Use deep copy)
    BinaryTree new_tree(copy_helper(this->root));
    return new_tree;
}

BinaryTree::BinaryTree(const BinaryTree &is){
    //destroy_helper(root);
    this->root = nullptr;
    this->root = copy_helper(is.root);
}

BinaryTree &BinaryTree::operator= (const BinaryTree &is){
    destroy_helper(this->root);
    this->root = copy_helper(is.root);
    return *this;
}