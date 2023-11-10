//
//  Problem5.h
//  ec330_hw6
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <algorithm>
#include <iterator>

using namespace std;

#ifndef Problem5_h
#define Problem5_h

/* class of white spaces*/
class my_ctype : public ctype<char> {
    mask my_table[table_size];
public:
    my_ctype(size_t refs = 0) : ctype<char>(&my_table[0], false, refs) {
        const ctype<char>& ct = use_facet<ctype<char> >(locale());
        copy_n(&ct.table()[0], table_size, &my_table[0]);
        my_table[' '] = (mask)space;
        my_table['\n'] = (mask)space;
        my_table['\t'] = (mask)space;
        my_table['\r'] = (mask)space;
        my_table['@'] = (mask)space;
        my_table['.'] = (mask)space;
        my_table['!'] = (mask)space;
        my_table['?'] = (mask)space;
        my_table[':'] = (mask)space;
        my_table[';'] = (mask)space;
        my_table[','] = (mask)space;
        my_table['-'] = (mask)space;
        my_table['"'] = (mask)space;
        my_table['('] = (mask)space;
        my_table[')'] = (mask)space;
        my_table['['] = (mask)space;
        my_table[']'] = (mask)space;
        my_table['{'] = (mask)space;
        my_table['}'] = (mask)space;
        my_table['#'] = (mask)space;
        my_table['$'] = (mask)space;
        my_table['%'] = (mask)space;
        my_table['^'] = (mask)space;
        my_table['&'] = (mask)space;
        my_table['*'] = (mask)space;
        my_table['+'] = (mask)space;
        my_table['='] = (mask)space;
        my_table['<'] = (mask)space;
        my_table['>'] = (mask)space;
        my_table['/'] = (mask)space;
    }
};

/* helper functions */
bool isNum(const char c) {
    if( c >= '0' && c <= '9') {
        return true;
    }
    return false;

}


/*read from a file, and return the number of BU_IDs whose digits add up to a number greater than 28*/
int fiveA() {
    ifstream file;
    file.open("TinyData.txt");
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
            if( isBU && isNum(c) ) {
                digit++;
                sum += c - '0';
            }
            if( isBU && !isNum(c) ) {
                if(digit == 8 && sum > 28) {
                    ret++;
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

int fiveB() {
    ifstream file;
    file.open("dictionary.txt");
    string word;
    locale x(locale::classic(), new my_ctype);
    file.imbue(x);
    int ret = 0;
    if( file.is_open() ) {
        while( file >> word ) {
            if( word[word.length()-1] == 'x' ) {
                ret++;
            }
        }
    } else {
        perror("Error opening file");
        exit(-1);
    }
    return ret;
}


int fiveC();

#endif /* Problem5_h */