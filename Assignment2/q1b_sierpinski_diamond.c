//created by Xingya Ren
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <math.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("ERROR: Wrong number of arguments. Two required.");
        return 0;
    }
    long customerHeight;
    customerHeight = atoi(argv[1]);
    int fractalLevel;
    fractalLevel = atoi(argv[2]);
    
    if (argc != 3){
        printf("ERROR: Wrong number of arguments. Two required.");
        return 0;
    }else if ((customerHeight <= 0) || ((customerHeight %2)==0)){
        printf("ERROR: Bad argument. Height must be positive odd integer.");
    }else if ( ceil(log2(ceil(customerHeight/2.0)))!=floor(log2(ceil(customerHeight/2.0))) || (ceil(customerHeight/2.0)) < pow(2, (fractalLevel-1))){
        printf("ERROR: Height does not allow evenly dividing requested number of levels.");
    }else{
  int Height = (((customerHeight/2)+1));
  int longestRow = customerHeight;
  char graph [longestRow+1][longestRow+1]; //+1 line for the \0 terminators  

  //adding \0 to the horizontal lines
  for(int i=0; i<(longestRow+1); i++){
    graph[longestRow][i]='\0';
  }

  //adding \0 to the end of all strings
  for (int i=0; i<longestRow+1; i++){
    graph[i][longestRow]='\0';
  }
  int row, space, star;

  //initializing every spot to _
  for (int r=0; r<longestRow; r++){
	   for (int c=0; c<longestRow; c++){
	      graph[r][c] = ' ';
	   }
  }
  for (row=0; row<Height; row++){ //printing the stars for the upper half 
    for (int column=0; column<longestRow; column++){
      int spaceNum = Height-1-row;
      int starNum = (row+1)*2-1; //ending of stars: (longestRow-1-(spaceNum))
      int leftest = (Height-1-row);
      while(leftest <= longestRow-1-(Height-1-row)){
        graph[row][leftest]='*';
        leftest++;
      }
    }
  }

 //printing the stars for the lower half  
 for(row=Height; row<longestRow; row++){
	 for(int column=0; column<longestRow; column++){
	 int spaceNum = row-Height;
	 int leftest = (row-Height)+1;
		 while(leftest <= longestRow-(row-Height)-2){
                   graph[row][leftest]='*';
		   leftest++;
		 }
   }
 }
 /*
 for(int i=0; i<longestRow; i++){
   for (int j=0; j<longestRow; j++){
     printf("%c", graph[i][j]);
   }
   printf("\n");
 }
*/
    
int cut(int level, int x, int y, int Height, int longestRow, char graph[longestRow+1][longestRow+1]); 
//take the coordinates needed to cut all the small triangles 
//the coordinates being the tips of triangles on the bottom 

cut(fractalLevel, Height-1, 0, Height, longestRow, graph); 

int temp = customerHeight / 2;

 for(int i=0; i<longestRow; i++){
   if (i < temp) {
     for (int j=0; j<longestRow; j++){
       printf("%c", graph[i][j]);
     }
     printf("\n");
   }
 }

 for (int r=longestRow/2; r < longestRow; r++) {
   for (int j=0; j<longestRow; j++){
     printf("%c", graph[temp][j]);
   }
  temp -= 1;
  printf("\n");
 }
}
}

//THIS IS THE END OF THE MAIN FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!

int cut(int level, int x, int y, int Height, int longestRow, char graph[longestRow+1][longestRow+1]){
//take the coordinates needed to cut all the small triangles
//the coordinates being the tips of triangles on the bottom
  if (level==1){
  return 0;
  }
  int midPointY = y+Height-1;  //[x][y+longestRow/2]
  int leftMiddleX = ((x-Height/2))+1;
  int leftMiddleY = ((y+y+Height)/2)-1; 
  int rightMiddleX = x-Height/2+1; 
  int rightMiddleY = (2*y+(2*Height)-1+Height)/2; 
  int rightMostX = x; 
  int rightMostY = y+(2*x); 
/*
printf("midPointY is: %d", midPointY);
printf("\n"); 
printf("leftMiddleX is: %d", leftMiddleX);
printf("\n");
printf("leftMiddleY is: %d", leftMiddleY);
printf("\n");
printf("rightMiddleX is: %d", rightMiddleX);
printf("\n");
printf("rightMiddleY is: %d", rightMiddleY);
printf("\n");
printf("rightMostX is: %d", rightMostX);
printf("\n");
printf("rightMostY is: %d", rightMostY);
*/
 
//two for loops, one for Xs, one for Ys
int k=1;  
for (int r=leftMiddleX; r<=x; r++){//shift by row 
  	for (int c=leftMiddleY+k; c<=rightMiddleY-k; c++){ //shift by column 
        graph[r][c] = ' '; 
	}
k++; 
}
//recursion call: call cut on the small triangles 
cut(level-1, leftMiddleX-1, leftMiddleY+1, Height/2, longestRow, graph); 
cut(level-1, x, y, Height/2, longestRow, graph); 
cut(level-1, x, midPointY+1, Height/2, longestRow, graph);   

return 0;
}

int isPowerTwo(long customerHeight){
    if (ceil (log2(ceil(customerHeight/2))) == floor (log2(ceil(customerHeight/2)))){
        return 1;
    }else{
        return 0;
    }
}
