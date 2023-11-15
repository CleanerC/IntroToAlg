// Author: Jiawei Xiang
// Collaborators: Derek Xu
/*
    *a): Read from a file, and return the number of BU_IDs whose digits add up to a number greater than 28
        I used a state machine to solve this problem. The state machine has 3 states:
            1. not counting
            2. counting)
            3. counting and BU_ID found (when the sum of the digits is greater than 28 and the length is 8)
    *b): Read from a file, and return the number of words in the file that are in the dictionary
        I used a trie to solve this problem. I first read the dictionary into the trie, and then I used the trie to count the occurrences of words in the data file.
    *c): Read from a file, and return the length of the longest palindrome in the file
        set very char as the mid, and try to expand, then return the longest one
*/
#include "Problem5.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unordered_map>

/* helper functions */
bool isNum(const char c) {
    if( c >= '0' && c <= '9') {
        return true;
    }
    return false;

}

vector<char> convert(string filename) {
    ifstream file;
    file.open(filename);
    char c;
    vector<char> ret;
    ret.push_back('^');                     // start of file marker
    if( file.is_open() ) {
        while( file.get(c) ) {
            ret.push_back('$');
            ret.push_back(c);
        }
    } else {
        perror("Error opening file");
        exit(-1);
    }
    ret.push_back('%');                     // end of file marker

    return ret;
}


/*read from a file, and return the number of BU_IDs whose digits add up to a number greater than 28*/
int fiveA() {
    ifstream file;
    file.open("BigData.txt");
    char c;
    int ret = 0;
    int sum = 0;
    int digit = 0;
    bool isBU = false;
    if(file.is_open()) {
        while( file.get(c) ) {
            // cout << c;
            if( c == 'U') {         //to reset
                sum = 0;
                digit = 0;
                isBU = true;
                continue;
            }
            // ONLY ONE can be true at once
            if( isBU && isNum(c) ) {
                digit++;
                sum += (c - '0')    ;
            }
            if( isBU && !isNum(c) ) {
                if(digit == 8 && sum > 28) {
                    ret++;
                    isBU = false;
                } else {
                    isBU = false;
                }
            }
        }
    } else {
        perror("Error opening file");
        exit(-1);
    }
    return ret;
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

            if (node->is_end_of_word && currentWord[currentWord.size() - 1] != 'x') {
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

    // Read the data file into a string
    string bigDataText ( (istreambuf_iterator<char>(data)),
                       (istreambuf_iterator<char>()));

    unordered_map<string, int> wordCounts;
    

    // Count occurrences using the trie
    countOccurrences(trie, bigDataText, wordCounts);

    int count = 0;

    // Print the results
    for (const auto& entry : wordCounts) {
        count += entry.second;
    }

    delete trie.root;

    return count;
}

/* find the longest palindrom with manacher's algorithm */
// int fiveC() {
//     vector<char> str = convert("BigData.txt");
//     long long int len = str.size();
//     vector<int> position(len, 0);                // the length of the longest palindrome centered at i
//     long int center = 0;                         // the center of the longest palindrome
//     long int right = 0;                          // the right bound of the longest palindrome

//     for( long long int ii = 1; ii < len - 1; ii++) {
//         long long int jj = 2 * center - ii;       // the mirror of ii

//         if(right > ii ) {
//             position[ii] = min( static_cast<int>(right - ii), position[jj]);        //safe to cast to int ??? maybe 99% sure? I don't think the palindrome can be that long
//         }

//         //try to find the longest at ii
//         while(str[ii + 1 + position[ii]] == str[ii - 1 - position[ii]]) {
//             position[ii]++;
//         }

//         //update center and right
//         if(ii + position[ii] > right) {
//             center = ii;
//             right = ii + position[ii];
//         }
//     }

//     //find the longest
//     int max = 0;                //I think a int is enough
//     for(int ii = 1; ii < len - 1; ii++) {
//         if(position[ii] > max) {
//             max = position[ii];
//         }
//     }

//     return max;
// }

/* set every char as the mid, and try to expand */
string longestPalindrome(string s) {
    if (s.size()<=1) 
        return s;
    auto min_left = 0;
    auto max_len = 1;
    auto max_right= s.size() - 1;
    for ( auto mid=0; mid < s.size(); ){
        auto left = mid;
        auto right = mid;
        while (right < max_right && s[right+1] == s[right]) {
            right++;                            // Skip duplicate characters in the middle because they are always palindromes
        }
        mid = right+1;                          //for next iter
        while (right < max_right && left > 0 && s[right+1] == s[left-1]) {
            right++; 
            left--;
        }                                       // try ti expand the palindrome

        auto new_len = right-left+1;            //record best palindrome
        if (new_len > max_len){ 
            min_left = left; 
            max_len = new_len; 
        }
    }

    return s.substr( min_left, max_len);           //return the longest palindrome
}

int fiveC() {
    ifstream file;
    file.open("BigData.txt");
    string dataString ( (istreambuf_iterator<char>(file)),
                       (istreambuf_iterator<char>()));              //read the file into a string

    return longestPalindrome(dataString).length();

}  
