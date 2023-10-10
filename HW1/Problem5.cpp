#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv){
    int Xxpos = 0, Xypos = 0;   //cursor
    char grid[10][10];
    int N = atoi(argv[1]);
    bool EO = (N%2 == 0);   //EVEN or ODD

    for(int ii = 0; ii < 10; ii++){
        for(int jj = 0; jj < 10; jj++){
            grid[ii][jj] = '-';
        }
    }
    //initilze

  
    for(int ii = 0; ii <= N; ii++){
        grid[Xxpos][Xypos] = 'x';
        grid[Xxpos][Xypos+1] = 'x';
        Xxpos++;
        Xypos++;
    }
    //x loop
    
    for(int ii = 0; ii <= N; ii++){
        if(EO == true){
            grid[Xxpos][Xypos] = 'o';
        }else{
            grid[Xxpos+1][Xypos-1] = 'o';
            grid[Xxpos+1][Xypos+1] = 'o';
        }
    }

    //for o

    for(int ii = 9; ii >= 0; ii--){
        for(int jj = 0; jj < 10; jj++){
            cout<<grid[jj][ii];
        }
        cout<<endl;
    }

    //print

    return 0;
}
