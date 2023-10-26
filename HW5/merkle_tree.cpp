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