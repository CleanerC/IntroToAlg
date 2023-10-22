//
//  main.cpp
//  Skip_List
//
//  Copyright © Tali Moreshet. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include "SkipList.h"

int main(int argc, const char * argv[]) {

  /* Uncomment */
  SkipList<int> *mySL= new SkipList<int>(INT_MIN, INT_MAX);
    
  mySL->insert(2);
  // mySL->insert(1);
  // mySL->insert(7);
  // mySL->insert(5);
  // mySL->insert(9);
  // mySL->insert(6);
  // mySL->insert(3);
    
  // mySL->insert(7);
    
  cout << "SkipList data: \n";
  mySL->printData();
    
  cout << "\n SkipList entire content: \n";
  mySL->print();
  // delete mySL;
  

    return 0;
}
