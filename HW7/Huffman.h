#include <queue>
#include <string>
#include <iostream>
#include <fstream>

class Huffman {
    /* data members */
    public: 
        class Node{
            public:
                char character;
                int freq;
                Node* left;
                Node* right;
                Node(char character, int freq, Node* left, Node* right) : character(character), freq(freq), left(left), right(right) {}
        };

        /* my comparator */
        class compare{
            public:
                bool operator()(Node* left, Node* right){
                    return (left->freq > right->freq);
                }
        };

    /* root */
    public:
        Node* root;

    /* methods */
    public:
        void buildHuffmanTree(char characters[], int freq[], int size);
        void printCodes();
        void decodeText(const std::string& fileName);
        bool isLeaf(Node* node){
            return (node->character != '\0') ? true : false;
        };
        
};