#include "Huffman.h"

void Huffman::buildHuffmanTree(char characters[], int freq[], int size) {
    /* create a priority queue of nodes */
    std::priority_queue<Node*, std::vector<Node*>, compare> pq;

    /* create a node for all the characters */
    for (int ii = 0; ii < size; ii++) {
        Node* node = new Node(characters[ii], freq[ii], nullptr, nullptr);
        pq.push(node);
    }

    /* create a node for the sum of the two smallest nodes */
    while(pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* node = new Node('\0', (left->freq + right->freq), left, right);
        pq.push(node);
        root = node;
    }
}

/* print the codes for each character */
void Huffman::printCodes() {
    std::queue<std::pair<Node*, std::string>> q;
    q.push({root, ""});

    while (!q.empty()) {
        auto pair = q.front();
        q.pop();

        Node* node = pair.first;
        std::string code = pair.second;

        // Check if this is a leaf node (no children)
        if (isLeaf(node)) {
            std::cout << node->character << " " << code << "\n";
        }
        //Queue is FIFO, so left is first 
        //if using a stack, right is first
        if (node->left) {
            q.push({node->left, code + "0"});
        }
        if (node->right) {
            q.push({node->right, code + "1"});
        }

    }
}

/* decode the text from the file */
void Huffman::decodeText(const std::string& fileName) {
    std::ifstream file(fileName);
    std::string encodedTxt;
    std::string code;
    std::string decodedText;

    Node* current = root;
    std::getline(file, encodedTxt);
    for(auto c : encodedTxt) {
        if(c == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if(isLeaf(current)) {
            decodedText += current->character;
            current = root;
        }
    }

    std::cout << decodedText << "\n";
}