/*
    first just open the file, and stream it into a string variable line by line.    
    then strtok it with dilimerator " ". So we can get all the numbers.
    then store numbers on each line into a vector of a vectors. which is 2-D vector.
    each row will be each line in the text file

    then just loop through ever row in the 2-D array, and find all the possible product of subsequences
    then push the max on every row into a vector and print every element on this vectror
    last return the max element on the vector
*/

#include "MaxProduct.h"

using namespace std;

long MaxProductClass::MaxProduct(string fileName){
            ifstream numList(fileName);
            string numberStr;
            vector<vector<int>> nums;
            vector<int> column;
            if(numList.is_open()) {
                while( numList ){
                    string Num;
                    numList >> numberStr;
                    Num = strtok((char*)numberStr.c_str(), " ");
                    if(stoi(Num) == -999999){
                        nums.push_back(column);
                        column.clear();
                    }else{
                        column.push_back(stoi(Num));
                    }
                }
            }
            
            
            vector<long> maxes;
            for(auto ii: nums){
                vector<long> locals;
                if(ii.size() == 1){
                    maxes.push_back(ii[0]);
                } else if(ii.size() == 2){
                    maxes.push_back(ii[0] * ii[1]);
                } else if(ii.size() >= 3){
                    for(int jj = 0; jj <= ii.size() - 3; jj++ ){
                        locals.push_back(ii[jj] * ii[jj+1] * ii[jj+2]);
                    }
                    for(int jj = 0; jj <= ii.size() - 2; jj++){
                        locals.push_back(ii[jj] * ii[jj+1]);
                    }
                    for(auto jj : ii){
                        locals.push_back(jj);
                    }
                    maxes.push_back(*max_element(locals.begin(), locals.end()));
                    locals.clear();
                }
            }

            for(auto ii : maxes){
                cout<<ii<<endl;
            }

            return *max_element(maxes.begin(), maxes.end());
        }
