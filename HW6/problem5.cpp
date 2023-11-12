#include "problem5.h"

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
        my_table['\\'] = (mask)space;
        my_table['|'] = (mask)space;
        my_table['~'] = (mask)space;
        my_table['`'] = (mask)space;
        my_table['\''] = (mask)space;
    }
};

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

int fiveB() {
    
}

/* find the longest palindrom */
int fiveC() {
    vector<char> str = convert("BigData.txt");
    long long int len = str.size();
    vector<int> position(len, 0);                // the length of the longest palindrome centered at i
    long int center = 0;                         // the center of the longest palindrome
    long int right = 0;                          // the right bound of the longest palindrome

    for( long long int ii = 1; ii < len - 1; ii++) {
        long long int jj = 2 * center - ii;       // the mirror of ii

        if(right > ii ) {
            position[ii] = min( static_cast<int>(right - ii), position[jj]);        //safe to cast to int ??? maybe 99% sure? I don't think the palindrome can be that long
        }

        //try to find the longest at ii
        while(str[ii + 1 + position[ii]] == str[ii - 1 - position[ii]]) {
            position[ii]++;
        }

        //update center and right
        if(ii + position[ii] > right) {
            center = ii;
            right = ii + position[ii];
        }
    }

    //find the longest
    int max = 0;                //I think a int is enough
    for(int ii = 1; ii < len - 1; ii++) {
        if(position[ii] > max) {
            max = position[ii];
        }
    }

    return max;
}
