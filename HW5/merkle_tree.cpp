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
    int cnt = 0;
    for(int ii = levels.size() - 1; ii >= 0; ii--) {
        for(auto jj : levels[ii]) {
            for(int kk = cnt ; kk > 0; kk--){
                cout<<" ";
            }
            cout<<"Level "<< cnt <<": "<<jj->key<<endl;
        }
        cnt++;
    }
}


/*helper function to read from a file*/
vector<int> readIntsFromFile(const string& filename) {
    vector<int> data;
    ifstream file(filename);
    string line;
    while(getline(file, line)) {
        data.push_back(stoi(line));
    }
    return data;
}

/*check if a number is power of 4*/
bool isPowerOfFour(int n) {
    while (n != 1) {
        if (n % 4 != 0) {
            return false;
        }
        n /= 4;
    }
    return true;
}

/*find how many levels to create*/
int log4(int num) {
    int ret = log(num) / log(4);
    return isPowerOfFour(num) ? ret + 1 : ret + 2;
}

/*find howmany parent to create this level*/
int parentNum(int num) {
    return num / 4 + 1;
}

/*constructor for Node*/
Node::Node(const string& val) {
    key = val;
}

/* defult constructor for MerkleTree class */
merkleTree::merkleTree() {
    levels.push_back(vector<Node*>());
}

/*build the tree with input data*/
merkleTree::merkleTree(const vector<int>& data) {
    root = new Node("");
    int cnt = 0;
    levels.push_back(vector<Node*>());

    //create all the leaves
    for(auto ii : data) {
        this->data.push_back(ii);
        Node* child = new Node(fnv1a(to_string(ii)));
        levels[cnt].push_back(child);
    }

    //create a levels
    while(parentNum(levels[cnt].size()) != 1) {
        //create a new level;
        levels.push_back(vector<Node*>());

        //create 1 less parents node than needed to prevent seg fault
        int ii;
        for(ii = 0; ii < levels[cnt].size()/4; ii++) {
            vector<Node*> children = {levels[cnt][0 + ii * 4], levels[cnt][ii * 4 + 1], levels[cnt][ii * 4 + 2], levels[cnt][ii * 4 + 3]};
            Node* parent = new Node(concatenateHash(children));
            for(auto jj : children) {
                jj->parent = parent;
                parent->children.push_back(jj);
            }
            levels[cnt + 1].push_back(parent);
        }

        //check if there is one more parent node to be created
        if(levels[cnt].size() % 4 != 0) {
            vector<Node*> children = {levels[cnt].begin() + 4 * ii, levels[cnt].end()};
            Node* parent = new Node(concatenateHash(children));
            for(auto jj : children) {
                jj->parent = parent;
                parent->children.push_back(jj);
            }
            levels[cnt + 1].push_back(parent);
        }
        
        //go to the next level
        cnt++;
    }

    if(!isPowerOfFour(levels[0].size())) {
        //create a new level
        levels.push_back(vector<Node*>());
        Node *realRoot = new Node("");
        levels[cnt + 1].push_back(realRoot);
        for(auto ii : levels[cnt]) {
            ii->parent = realRoot;
            realRoot->children.push_back(ii);
        }
        root = realRoot;
        root->key = concatenateHash(root->children);
    }
    else{

        //set the root node
        root = levels[cnt][0];
        root->key = concatenateHash(root->children);
    }
}

/*vallidate the merkle tree*/
void merkleTree::verify() {
    merkleTree *newTree = new merkleTree(data);
    if(newTree->getRoot()->key == root->key) {
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

    int index = 0;
    //replace the original value with the new value and also rehash the leaf node
    while(data[index++] != originalValue);
    data[index - 1] = newValue;
    levels[0][index - 1]->key = fnv1a(to_string(newValue));     //leaf node need to hash seperatly
    
    //rehash the parent node
    Node *itr = levels[0][index - 1]->parent;

    while(itr != nullptr) {
        itr->key = concatenateHash(itr->children);
        itr = itr->parent;
    }
}

/*insert a new value to the tree*/
void merkleTree::insert(int newValue) {

    //need to create or not
    int cnt = 0;
    bool toCreate = (levels[cnt].size()%4 == 0);

    //create new leaf, add to data vector and also add to the tree
    Node* newLeaf = new Node(fnv1a(to_string(newValue)));
    data.push_back(newValue);
    levels[0].push_back(newLeaf);


    if(data.size() == 1) {
        root = newLeaf;
        levels[0].push_back(root);
        return;
    } else if (data.size() == 2){
        levels.push_back(vector<Node*>());
        Node* newRoot = new Node(concatenateHash({root, newLeaf}));
        newRoot->children.push_back(root);
        newRoot->children.push_back(newLeaf);
        root->parent = newRoot;
        newLeaf->parent = newRoot;
        root = newRoot;
        levels[1].push_back(root);
        return;
    }

    //add new leaf to the tree w/o creating new parent nodes
    if(!toCreate) {
        levels[1][levels[1].size() - 1]->children.push_back(newLeaf);
        newLeaf->parent = levels[1][levels[1].size() - 1];
    }

    //rebuilt the tree and rehash the parent nodes
    while(toCreate) {
        Node *newParent = new Node("");
        newParent->children.push_back(levels[cnt][levels[cnt].size() - 1]);
        levels[cnt][levels[cnt].size() - 1]->parent = newParent;
        //move to the next level;
        cnt++;
        toCreate = (levels[cnt].size()%4 == 0);
        levels[cnt].push_back(newParent);   
    }

    if(cnt + 1 == levels.size()) { 
        //create a new root node
        Node *newRoot = new Node("");
        levels.push_back(vector<Node*>());
        levels[cnt + 1].push_back(newRoot);
        for(auto ii : levels[cnt]) {
            ii->parent = newRoot;
            newRoot->children.push_back(ii);
        }
        root = newRoot;
    } else if(cnt != 0 && cnt + 1 < levels.size()){
        //add the new parent node to the tree
        levels[cnt + 1][levels[cnt + 1].size() - 1]->children.push_back(levels[cnt][levels[cnt].size() - 1]);
        levels[cnt][levels[cnt].size() - 1]->parent = levels[cnt + 1][levels[cnt + 1].size() - 1];
    } 
    
    //rehash the parent nodes
    Node *itr = newLeaf->parent;
    while(itr != nullptr) {
        itr->key = concatenateHash(itr->children);
        itr = itr->parent;
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
