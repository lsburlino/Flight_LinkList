#include "flight.h"
#include "stdlib.h"
#include "stdio.h"


//inserts flights in ascending order of flight number
LLNode* insert(LLNode * flights, flight * info){

  //if list empty or end of list reached inserts node there
  if(flights==NULL){
    LLNode* temp = (LLNode*) malloc(sizeof(LLNode));
    temp->next=NULL;
    temp->info=info;
    printf("Inserting Flight: %s %d %d %d\n", temp->info->airline, temp->info->f_num,temp->info->t_out,temp->info->t_in);
    return temp;
  }

  //if flight number is less than the next in list inserts flight
  if(flights->info->f_num>info->f_num){
    LLNode* temp = (LLNode*) malloc(sizeof(LLNode));
    temp->next=flights;
    temp->info=info;
    printf("Inserting Flight: %s %d %d %d\n", temp->info->airline, temp->info->f_num,temp->info->t_out,temp->info->t_in);
    return temp;
  }
  
  //if they equal frees unneeded flight struct and prints error message
  if(flights->info->f_num==info->f_num){
    printf("Flight %d already exists. Could not add to list.\n",info->f_num);
    free(info);
    return flights;
  }
  //else calls recursively
  flights->next = insert (flights->next,info);
  return flights;
}

//deletes nodes and frees them from list
LLNode* delete(LLNode * flights, int f_num){
  if(flights == NULL){
    printf("Flight not found could not delete");
    return flights;
  }

  //if found patches up llist and frees
  if(flights->info->f_num == f_num){
    printf("Deleting flight %d.\n", f_num);
    LLNode* temp = flights->next;
    free(flights->info);
    free(flights);
    return temp;
  }
  //recursively calls
  flights->next=delete(flights->next,f_num);
  return flights;
  
}


//prints list
void printList(LLNode * flights){
  if (flights==NULL)
    return;
  
  printf("Flight List: \n");
  while(flights !=NULL){

    
    printf("%s %d %d %d\n", flights->info->airline, flights->info->f_num,flights->info->t_out,flights->info->t_in);

    
    flights = flights->next;
  }
  printf("\n");
  
}

//saves everything into file called data.txt
void save(LLNode * flights, char * fName){

  FILE* fp = NULL;
  fp= fopen(fName, "w");
  while (flights!=NULL){
    fprintf(fp,"%s %d %d %d\n", flights->info->airline, flights->info->f_num,flights->info->t_out,flights->info->t_in);
    flights = flights->next;
  }
  fclose(fp);
  
  
}

//frees everything
void freeList(LLNode * flights){

  if (flights ==NULL) {
    free(flights);
    return;
  }
  freeList(flights->next);
  free(flights->info);
  free(flights);
  return;
}

//finds if a flight with some flight number exists
LLNode* find(LLNode* flights, int f_num){
  while(flights !=NULL){
    if(f_num==flights->info->f_num)
      return flights;
    flights = flights->next;
  }
  return NULL;
}

//makes flight structs
flight* makeFlight(char*airline,int f_num,int t_out, int t_in){

  flight* info = (flight*) malloc(sizeof(flight));
  info->airline[0] = airline[0];
  info->airline[1] = airline[1];
  info->f_num=f_num;
  info->t_out=t_out;
  info->t_in=t_in;
  return info;
 
}


//reads flights from inserted file
LLNode* readFile(char* fName){

  //opens file for reading
  FILE* fp = NULL;
  fp = fopen(fName,"r");
  if (fp == NULL){
    fclose(fp);
    return NULL;
  }
	  
  //checks for end of file character and runs until then
  LLNode* flights;
  flight* tFlight;
  int lCounter = 1;
  char c;
  for (c=getc(fp);c != EOF; c = getc(fp)){
    if (c=='\n')
	      lCounter++;
  }
  rewind(fp);
  int i;
  char airline[2];
  int x,fNum,depart,arrive;

  //runs til end of file;
  for (i=0;i<lCounter;i++){

    //inputs all values with valid format
    x = fscanf(fp,"%2s %d %d %d", airline, &fNum, &depart, &arrive);
    if (x==4 && airline[1]>='A' && airline[1]<='Z' && airline[0]>='A' && airline[0]<='Z' && depart>0 &&depart<2400 && arrive>0 && arrive<2400 && fNum>0 && fNum<10000){
      tFlight=makeFlight(airline,fNum,depart,arrive);
      flights = insert(flights, tFlight);
    }
    x=-1;
    fNum=-1;
    depart=-1;
    arrive=-1;
  }
  fclose(fp);
  return flights;
}

//allows user to input flights
LLNode* inputFlight (LLNode* flights, int fNum){
  char airline[2];
  int depart,arrive, x;
  flight* tFlight;
  
  //if yes asks for rest of information for flight struct.
  printf("Please enter airline departure time and arrival time:\n");
  printf("<Airline> <Departure Time> <Arrival Time>\n");
  x=scanf("%2s %d %d",airline,&depart,&arrive);
  
  //Checks all values to see if they are valid for the flight struct
  if(x==3 && airline[1]>='A' && airline[1]<='Z' && airline[0]>='A' && airline[0]<='Z' && depart>0 &&depart<2400 && arrive>0 && arrive<2400){
    tFlight= makeFlight(airline,fNum,depart,arrive);
    flights=insert(flights,tFlight);
  }
  
  //if not valid prints error message and allows user to restart
  else printf("Error: Please insert information in a valid format\n");
}
