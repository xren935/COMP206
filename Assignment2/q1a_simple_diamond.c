//created by Xingya Ren
#include<stdio.h>
#include <stdlib.h> 

int main(int argc, char*argv[]){
	if (argc != 2){
	printf("ERROR: Wrong number of arguments. One required."); 
	return 0; 
	}

	int userNumber; //the user input, gives number of rows 
	userNumber = atoi(argv[1]);   
	
	//there can be only 1 input, and the input has to be a positive and odd integer)
	if(argc != 2){
		printf("ERROR: Wrong number of arguments. One required."); 
        	return 0; 
	}else if ((userNumber <= 0) || ((userNumber % 2) ==0)){
		printf("ERROR: Bad argument. Height must be positive odd integer.");
		return 0;
	}else{ 
		int numOfRows = (userNumber/2)+1; 
		int row, space, star; 
		for (row=1; row<=numOfRows; row++){
			//use a for loop to print the spaces
			for(space=numOfRows-row; space>=1; space--){
			printf(" "); 
			}
			//use a for loop to print the stars 
			for(star=1; star<=(row*2)-1; star++){
			printf("*"); 
			}
		printf("\n"); 
		}	
		for(row=numOfRows-1; row>=1; row--){
			for (space=1; space<=numOfRows-row; space++){
			printf(" "); 
			}	
			//the for loop for the stars 
			for(star=1; star<=2*row-1; star++){
			printf("*"); 
			}
			printf("\n"); 
		}	
	}
}


	


