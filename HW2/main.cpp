#include <iostream>
#include "MaxProduct.h"

using namespace std;

int main() {
     MaxProductClass mProd;
    long max = mProd.MaxProduct("input.txt");
    cout << "The overall max product is: " << max << endl;
    
    return 0;
} 