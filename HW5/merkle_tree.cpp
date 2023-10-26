/*
Implementation of the merkle tree and node classes and helper function to read from an inputed file.
*/

#include "merkle_tree.h"

using namespace std;

/* Hash function*/
inline string fnv1a(string const & text) {
    // 64 bit params
    uint64_t constexpr fnv_prime = 1099511628211ULL;
    uint64_t constexpr fnv_offset_basis = 14695981039346656037ULL;
    
    uint64_t hash = fnv_offset_basis;
    
    for(auto c: text) {
        hash ^= c;
        hash *= fnv_prime;
    }

    return to_string(hash);
}

/* Merkle Tree method for computing the hash of the concatenated hashes of children nodes 
   Using the provided hash function, concatenates child hashes from left to right and returns the hash 
   of the concatenation */
string merkleTree::concatenateHash(const vector<Node*>& nodes){
    string merged;
    //concatenate hashes of all inputed nodes 
    for(const Node* node: nodes){
        merged += node->key;
    }

    //take hash of concatenated nodes
    string mergedHash = fnv1a(merged);

    return mergedHash;
}

/* Print the Merkle Tree, used to visualize the tree and its content */
void merkleTree::printTree(const Node* node, int depth){
        if (node == nullptr){
            return;
        }
        //indent based on depth of the node
        string indent(depth, ' ');

        //print current node
        cout << indent << "Level " << depth << ": " << node->key << endl;

        //Recursive call to print children of the current node
        for(const auto* child: node->children){
            printTree(child,depth + 1);
        }
}


/*helper function to read from a file*/
vector<int> readIntsFromFile(const string& filename) {
    vector<int> data;
    ifstream file(filename);
    if (file.is_open()) {
        int value;
        while(file >> value) {
            data.push_back(value);
        }
    }
}

/*constructor for Node*/
Node::Node(const string& val) {
    key = val;
}

/* defult constructor for MerkleTree class */
merkleTree::merkleTree() {
    root = new Node("");
}

/*build the tree with input data*/
merkleTree::merkleTree(const vector<int>& data) {
    root = new Node("");

    //create all the leaves
    for(auto ii : data) {
        this->data.push_back(ii);
        Node* child = new Node(fnv1a(to_string(ii)));
        leaves.push_back(child);
    }

    //create 1 less parents node than needed to prevent seg fault
    static int cnt = 0;
    for(int ii = 0; ii < data.size()/4; ii++) {
        vector<Node*> children = {leaves[0 + cnt * 4], leaves[cnt * 4 + 1], leaves[cnt * 4 + 2], leaves[cnt * 4 + 3]};
        Node* parent = new Node(concatenateHash(children));
        for(auto jj : children) {
            parent->children.push_back(jj);
        }
        rootChildren.push_back(parent);
        cnt++;
    }

    //check if there is one more parent node to be created
    if(data.size() % 4 != 0) {
        vector<Node*> children = {leaves.begin() + 4 * cnt, leaves.end()};
        Node* parent = new Node(concatenateHash(children));
        for(auto jj : children) {
            parent->children.push_back(jj);
        }
        rootChildren.push_back(parent);
    }

    //change the key store in root
    root->key = concatenateHash(rootChildren);
    for(auto ii : rootChildren) {
        root->children.push_back(ii);
    }
}

/*vallidate the merkle tree*/
void merkleTree::verify() {
    merkleTree *newTree = new merkleTree(data);
    if(newTree->root->key == root->key) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
}

/*overwrite one of the node*/
void merkleTree::overwrite(int originalValue, int newValue) {
    //check if the original value is in the data vector
    if(find(data.begin(), data.end(), originalValue) == data.end()) {
        cout << "Original value not found" << endl;
        return;
    }

    int index;
    //replace the original value with the new value and also rehash the leaf node
    while(data[index++] != originalValue);
    index -= 1;
    data[index] = newValue;
    leaves[index]->key = fnv1a(to_string(newValue));

    //rehash the tree
    rootChildren[index/4]->key = concatenateHash(rootChildren[index/4]->children);
    root->key = concatenateHash(rootChildren);
}

/*insert a new value to the tree*/
void merkleTree::insert(int newValue) {

    data.push_back(newValue);
    Node* newLeaf = new Node(fnv1a(to_string(newValue)));
    leaves.push_back(newLeaf);

    if(data.size()%4 == 0) {
        //enter this block if have to create a parent node
        Node* newParent = new Node("");
        newParent->children.push_back(newLeaf);
        rootChildren.push_back(newParent);
        newParent->key = concatenateHash(newParent->children);
    } 
    else {
        //enter this block if no need to create a parent node
        //find which parent node to be updated
        int index = data.size()/4;
        rootChildren[index]->children.push_back(newLeaf);
        
        //rehash the parent node
        rootChildren[index]->key = concatenateHash(rootChildren[index]->children);

        //rehash the root node
        root->key = concatenateHash(rootChildren);
    }
}

/*Print the Root*/
void merkleTree::printRoot() {
    cout << root->key << endl;
}

/*return the root Node ptr*/
Node* merkleTree::getRoot() {
    return root;
}