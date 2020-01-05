//created by Xingya Ren
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    //read the file into a string
    if (argc != 2){
        printf("ERROR: Wrong number of arguments. One required.");
        return 0;
    }
    //argv[1] is the file name
    FILE*fp = fopen(argv[1], "r");
    //use code from Lec9 slides to read the txt file into a string
    size_t sz;
    fseek(fp, 0L, SEEK_END);
    sz = ftell(fp);
    rewind(fp);
    char file_data_array[sz+1];
    file_data_array[sz]='\0';
    fread(file_data_array, 1, sz+1, fp);
    //now file_data_array is a string that contains the txt file
    
    //declaring needles
    char *needle1 = "<a href=\"/wiki/";
    char *needle2 = "</a>";
    char *needle3 = "title=\"";
    //declaring pointers
    char *p1 = NULL; //points to the first part of the link
    char *p2 = NULL; //points to the last part of the link
    char *p3 = NULL; //points to the title part
    
    p1 = strstr(file_data_array, needle1); //p1 points to the first <a...in the file
    //find p3 in p1
    if (p1 != NULL){
        p2 = strstr(p1, needle2);
        p3 = strstr(p1, needle3);
    }
    //p2 = strstr(file_data_array, needle2);
    //p3 = strstr(file_data_array, needle3);
    while (p1 != NULL && p2 != NULL && p3 != NULL){
    //find the first part
    p1 = strstr(p1, needle1); //p1 points to the first <a...in the file
    //find the second part
    //find p3 in p1
        if (p1 == NULL){
            break;
        }
    p2 = strstr(p1, needle2);
    // *p1 is < *p2 is <
    //find the title part
    p3 = strstr(p1, needle3);
    // *p3 is 't'
    //compare p3 to p1 and p2
        if (p1 != NULL && p2 != NULL && p3 != NULL){
            int p3_p1;
            p3_p1 = (p3-p1);
            //p3_p1 = (p3-p1); //gives how many chr p3 is to the right of p1; should >0 if title is on the right of p1
            int p2_p3;
            p2_p3 = (p2-p3); //gives how many chr p2 is to the right of p3; should >0 if title is on the left of p2
            if((p3_p1 > 0) && (p2_p3 > 0)){
                //title is in between p1 and p2
                //found a title
                p3 = p3+7;
                while(*p3 != '\"'){ //print the title
                  printf("%c", *p3);
                  p3++;
                }
                printf("\n"); //now the first title is found, print a new line
                if (p1++ == NULL || p2++ == NULL || p3++ == NULL){
                    break;
                }
                p1++;
                p2++;
                p3++;
            }else{
                if (p1++ == NULL || p2++ == NULL || p3++ == NULL){
                    break;
                }
                p1++;
                p2++;
                p3++;
            }
            }//the end of if loop
    }//the end of while loop 
}
