/*
Sample main file for testing the merkle tree implementation.
*/

#include "merkle_tree.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv){

    /* read from the file named in the first argument -- File should consist of one value per line */
    string input = "";
    if(argc == 2){
        input = argv[1];
    }

    /* Then stores input values in a data vector - intial tree is built over that vector. */
    vector<int> data = readIntsFromFile(input); //function must be implemented in order to read data from file input

    cout << "Inputted data: ";
    for (int i: data){
        cout << i << " ";
    }
    cout << endl;

    /* Roots are printed as new values are inserted or overwritten. */
    merkleTree tree(data);
    
    cout << "Root value: ";
    tree.printRoot();

    tree.overwrite(7, 100);

    cout << "7 overwritten to 100" << endl;

    cout << "New root value: ";
    tree.printRoot();

    cout << "Inserting: 50" << endl;
    tree.insert(50);

    cout << "New root value: ";
    tree.printRoot();

    cout << "Inserting 1, 2, 3, 4, 5, 6" << endl;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    
    /* Tree is printed. */
    tree.printTree(tree.getRoot());

    /* Tree root is verified before and after a malicious attack occurs on the data vector. */
    cout << "Verifying tree..." << endl;
    cout << "Is data secure: ";
    tree.verify();
    cout << endl; //should be True

    cout << "Malicious data attack occurs!" << endl;
    tree.data[3] = 100;

    cout << "Verifying tree..." << endl;
    cout << "Is data secure: ";
    tree.verify();
    cout << endl; //should be False

    /* New tree is constructed from using just the insert function. */
    merkleTree newTree;
    // cout << "Creating a new tree from inserts" << endl;
    // cout << "Inserting: 20, 10, 1 to new tree" << endl;

    newTree.insert(20);
    newTree.insert(10);
    newTree.insert(1);

    /* Root is saved and verified. */
    cout << "New tree final root value: ";
    newTree.printRoot();
    
    cout << "Verifying tree..." << endl;
    cout << "Is data secure: ";
    newTree.verify();
    cout << endl; //should be True

    /* Tree is printed. */
    newTree.printTree(newTree.getRoot());

    return 0;
}