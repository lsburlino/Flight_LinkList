#ifndef FLIGHT_H
#define FLIGHT_H

#include "stdio.h"
#include "stdlib.h"


typedef struct Node LLNode;
typedef struct FFlight flight;
struct Node {
  flight* info;
  LLNode* next;
};
struct FFlight{
  char airline[2];
  int f_num;
  int t_out;
  int t_in;
};



LLNode * insert(LLNode *, flight *);
LLNode * delete(LLNode * , int);
void printList(LLNode *);
void save(LLNode *, char *);
void freeList(LLNode *);
LLNode * find(LLNode*, int);
flight * makeFlight(char*,int,int, int);
LLNode* readFile(char*);
LLNode* inputFlight (LLNode*,int);


#endif
