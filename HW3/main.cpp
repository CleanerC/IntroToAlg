//
//  main.cpp
//  Linked_List
//
//  Copyright © Tali Moreshet. All rights reserved.
//

#include <iostream>
#include <limits.h>
#include "LinkedList.h"

int main(int argc, const char * argv[]) {

  LinkedList<int> *myLL = new LinkedList<int>(INT_MIN, INT_MAX);
  Node<int> *newNodeLoc;
  
  newNodeLoc = myLL->search(myLL->head, 3);
  myLL->insert(newNodeLoc, 3);
  newNodeLoc = myLL->search(myLL->head, 1);
  myLL->insert(newNodeLoc, 1);
  newNodeLoc = myLL->search(myLL->head, 2);
  myLL->insert(newNodeLoc, 2);

  cout << "Linked list data: \n";
  myLL->printData();

  cout << "\n Linked List entire content: \n";
  myLL->print();
  delete myLL;
  return 0;
}
