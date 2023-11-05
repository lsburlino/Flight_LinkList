#include "flight.h"
#include <stdio.h>
#include "stdlib.h"
#include "string.h"

int main(int argv, char* argc[]){

	// check for number of arguments passed in if more than 2 ends program.
	if(argv > 2){
	  fprintf(stderr, "Error: too many arguments\nUSAGE: ./flight <flight file> or ./flight.\n");
	  return EXIT_FAILURE;
	}

	
	LLNode* top = NULL;
	//If there is an input file this adds all flights to link list
	if(argv==2){

	  top = readFile(argc[1]);
	  if (top == NULL)
	    printf("Error: File is empty or DNE");
	}
	printList(top);



	
	int r = 0;
	char input[5], str[5];
	//asks user if they want to add or delete any flights from flight list
	while (r <1){
	  printf("Enter flight number to delete or add.\n Enter 'q' or 'Q' to quit and print Flight List to 'data.txt'\n");
	  scanf("%s", input);
	  sprintf(str,"%d",atoi(input));

	  // if q is entered if quits from program and saves flightlist in data.txt
	  if (*input == 'q'||*input =='Q'){
	    printList(top);
	    save(top,"data.txt");
	    printf("Flight List saved in 'data.txt'\n"); 
	    freeList(top);
	    return EXIT_SUCCESS;
	  }
	  else if (strcmp(input,str)==0 && atoi(input)<10000){
	    if (find(top,atoi(input)) != NULL){
	      printf("Flight found.\n");
	      top=delete(top, atoi(input));
	    }
	    else{
	      //tells user that flight was not found
	      //asks if they would like to add a flight
	      printf("Flight not found. Would you like to add a flight with this number?\n(Enter y or Y to continue)\n");
	      char c[5];
	      scanf("%s",c);

	      //if yes inputs flight;
	      if (*c=='y' || *c=='Y'){
		top=inputFlight(top, atoi(input));
	      }
	    }

	    //prints list at the end of each action
	    printList(top);
	  }
	  else printf("Error: Please insert information in a valid format\n");
	}
	return EXIT_SUCCESS;
}
