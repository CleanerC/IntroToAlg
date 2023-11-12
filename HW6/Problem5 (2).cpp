// Author: Derek Xu
// Collaborators: David Xiang

#include "Problem5.h"

#define NUM_CHARS 256

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;



int fiveA() {
    ifstream file;
    file.open("TinyData.txt");

    char curr;

    int sum = 0;
    int substrSize = 0;
    bool counting = false;

    int count = 0;

    if (!file.is_open()) {
        return -1;
    }

    while (file.get(curr)) {
        if (curr == 'U') {
            // start counting
            counting = true;
            continue;
        }
        // if curr is a digit, add it to the sum
        if (counting && curr <= '9' && curr >= '0') {
            sum += curr - '0';
            substrSize++;
        }

        if (counting && (curr > '9' || curr < '0')) {
            if (sum > 28 && substrSize == 8) {
                count++;
            }
            else {
                counting = false;
                sum = 0;
                substrSize = 0;
            }
        }
    }
    return count;
}


class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool is_end_of_word;
    int count;

    TrieNode() : is_end_of_word(false), count(0) {}
};

class Trie {
public:
    TrieNode* root;

    Trie() : root(new TrieNode()) {}

    void insertWord(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->is_end_of_word = true;
    }
};

void countOccurrences(Trie& trie, const string& text, unordered_map<string, int>& wordCounts) {
    TrieNode* root = trie.root;

    for (size_t i = 0; i < text.size(); ++i) {
        TrieNode* node = root;
        string currentWord;

        char c = text[i];
        int j = i;
        while (node->children.find(c) != node->children.end()) {
            node = node->children[c];
            currentWord += c;

            if (node->is_end_of_word) {
                wordCounts[currentWord]++;
            }

            j++;
            if (j >= text.size()) {
                break;
            }
            c = text[j];
        
        }
    }
}


int fiveB() {

    ifstream dictionary("dictionary.txt");
    ifstream data("BigData.txt");

    Trie trie;
    string word;

    // Build the trie from the dictionary
    while (dictionary >> word) {
        trie.insertWord(word);
    }

    // string bigDataText;
    string line;

    string bigDataText ( (istreambuf_iterator<char>(data)),
                       (istreambuf_iterator<char>()));

    unordered_map<string, int> wordCounts;
    

    // Count occurrences using the trie
    countOccurrences(trie, bigDataText, wordCounts);

    int count = 0;

    // Print the results
    for (const auto& entry : wordCounts) {
        cout << entry.first << ": " << entry.second << " occurrences\n";
        count += entry.second;
    }
    //cout << "Total: " << count << " occurrences\n";

    delete trie.root;

    return count;


}



int min(int a, int b)  
{  
    int res = a;  
    if(b < a)  
        res = b;  
    return res;  
}  



string longestPalindrome(string s) {
    if (s.size()<=1) 
        return s;
    auto min_left=0;
    auto max_len=1;
    auto max_right=s.size()-1;
    for (auto mid=0;mid<s.size();){
        auto left=mid;
        auto right=mid;
        while (right<max_right && s[right+1]==s[right])
            right++; // Skip duplicate characters in the middle
        mid=right+1; //for next iter
        while (right<max_right && left>0 && s[right+1]==s[left-1]){
            right++; 
            left--;
        } // Expand the selection as long it is a palindrom
        auto new_len=right-left+1; //record best palindro
        if (new_len>max_len){ 
            min_left=left; 
            max_len=new_len; 
        }
    }
    return s.substr(min_left, max_len);
}

int fiveC() {
    ifstream file;
    file.open("BigData.txt");
    string dataString ( (istreambuf_iterator<char>(file)),
                       (istreambuf_iterator<char>()));

    return longestPalindrome(dataString).length();

}  
