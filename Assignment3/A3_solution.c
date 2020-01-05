//created by Xingya Ren
/* FILE: A3_solutions.c is where you will code your answers for Assignment 3.
 * 
 * Each of the functions below can be considered a start for you. They have 
 * the correct specification and are set up correctly with the header file to
 * be run by the tester programs.  
 *
 * You should leave all of the code as is, especially making sure not to change
 * any return types, function name, or argument lists, as this will break
 * the automated testing. 
 *
 * Your code should only go within the sections surrounded by
 * comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A3_solutions.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A3_provided_functions.h"

unsigned char*
bmp_open( char* bmp_filename,        unsigned int *width, 
          unsigned int *height,      unsigned int *bits_per_pixel, 
          unsigned int *padding,     unsigned int *data_size, 
          unsigned int *data_offset                                  )
{
  unsigned char *img_data=NULL;
  /*
   printf( "bmp_info for file %s:\n", argv[1] );
   printf( "  width         = %d\n", image_width );
   printf( "  height        = %d\n", image_height );
   printf( "  bpp           = %d\n", bits_per_pixel );
   printf( "  padding       = %d\n", row_padding );
   printf( "  data_offset   = %d\n", data_offset );
   */
    // Read the overall file size
    FILE *bmpfile = fopen( bmp_filename, "rb" );
    if( bmpfile == NULL ){
        printf( "I was unable to open the file.\n" );
        return NULL;
        }
    // Read the B and M characters into chars
    char b, m;
    fread (&b,1,1,bmpfile);
    fread (&m,1,1,bmpfile);
    unsigned int overallFileSize;
    fread( &overallFileSize, 1, sizeof(unsigned int), bmpfile );
    // Rewind file pointer to the beginning and read the entire contents.
    rewind(bmpfile);
    //char imageData[overallFileSize];
    img_data = (unsigned char*)(malloc((sizeof (char)) * overallFileSize));
    if( fread( img_data, 1, overallFileSize, bmpfile ) != overallFileSize ){
        printf( "I was unable to read the requested %d bytes.\n", overallFileSize );
        return NULL;
    }
    // Read the width size into unsigned int (hope = 500 since this is the width of utah.bmp)
    //printf("aaa%saaa\n", img_data); // Only gets the first three BM? characters then segfaults?
    unsigned int* wp = (unsigned int*)(img_data+18);
    unsigned int img_width = *wp;
    *width = img_width;
    //after the width comes the height
    unsigned int* ht = (unsigned int*)(img_data+22);
    unsigned int img_height = *ht;
    *height = img_height;
    //read bbp
    unsigned short* bbp = (unsigned short*)(img_data+28);
    unsigned short bitesPerPixel = *bbp;
    *bits_per_pixel = bitesPerPixel;
    //printf("printing bitesPerPixel, %d\n", *bits_per_pixel);
    //compute padding value
    int paddingValue = 0;
    while((img_width*3 + paddingValue) % 4 != 0){
        //width times 3 because there are three bytes per pixel in 24bit bitmaps
        paddingValue++;
    }
    *padding = paddingValue;
    //read File Offset to Pixel Array
    unsigned int* offset = (unsigned int*)(img_data+10);
    unsigned int fileOffset = *offset;
    *data_offset = fileOffset;
  return img_data;
}

void 
bmp_close( unsigned char **img_data )
{
    free(*img_data);
    img_data = NULL;
}

unsigned char***  
bmp_scale( unsigned char*** pixel_array, unsigned char* header_data, unsigned int header_size,
           unsigned int* width, unsigned int* height, unsigned int num_colors,
           float scale )
{
  unsigned char*** new_pixel_array = NULL;
    //recompute the newWidth and the newHeight and replace width and height
    //[height][width][num_colors]--> [height*scale][width*scale][num_colors]
    unsigned int new_width;
    unsigned int new_height;
    new_width = (*width)*scale;
    new_height = (*height)*scale;
    new_pixel_array = (unsigned char***)malloc( sizeof(unsigned char**) * (new_height));
    if( new_pixel_array == NULL ){
        printf( "Error: bmp_to_3D_array failed to allocate memory for image of height %d.\n", (new_height));
        return NULL;
    }
    //create space for the new image
    for( int row=0; row<new_height; row++ ){
        new_pixel_array[row] = (unsigned char**)malloc( sizeof(unsigned char*) * (new_width) );
        for( int col=0; col<new_width; col++ ){
            new_pixel_array[row][col] = (unsigned char*)malloc( sizeof(unsigned char) * (num_colors));
        }
    }
    //copy the old into the new image --> populate the scaled image
    //Set every pixel at [row][col] in the scaled image to the value at
      //[row/scale][col/scale] in the old image.
    for( int row=0; row<new_height; row++ ){
        for( int col=0; col<new_width; col++ ){
            for( int color=0; color<num_colors; color++ ){
                  new_pixel_array[row][col][color] = pixel_array[(int)(((row)/scale))][(int)((col/scale))][color];
            }
        }
    }
    //update data within header_data, namely width, height and overallFileSize
    *(unsigned int*)(header_data+18) = new_width;
    *(unsigned int*)(header_data+22) = new_height;
    *height = new_height;
    *width = new_width;
    int new_padding = ( 4 - (new_width * num_colors) % 4) % 4; //this is the new padding
    int row_size = new_width*num_colors+new_padding;
    int raw_pixel_size = header_size + new_height*row_size; //this is the new_overall_file_size
    *(unsigned int*)(header_data+2) = raw_pixel_size;
    // TO HERE!
    return new_pixel_array;
}         

int bmp_collage( char* background_image_filename,     char* foreground_image_filename,
             char* output_collage_image_filename, int row_offset,                  
             int col_offset,                      float scale )
{
    unsigned char* background_header_data = NULL;
    unsigned int background_header_size;
    unsigned int background_width;
    unsigned int background_height;
    unsigned int background_num_colors;
    unsigned int* background_bbp = NULL;
    unsigned int* background_padding = NULL;
    unsigned int* background_data_size = NULL;
    unsigned int* background_offset = NULL;
    
    unsigned char* output_header_data = NULL;
    unsigned int output_header_size;
    unsigned char* output_img_data=NULL;
    
    unsigned char* foreground_header_data = NULL;
    unsigned int foreground_header_size;
    unsigned int foreground_width;
    unsigned int foreground_height;
    unsigned int foreground_num_colors;
    unsigned int* foreground_bbp = 0;
    unsigned int* foreground_padding = 0;
    unsigned int* foreground_data_size = 0;
    unsigned int* foreground_offset = 0;
    unsigned char*** background_pixel_array = bmp_to_3D_array(background_image_filename, &background_header_data, &background_header_size, &background_width, &background_height, &background_num_colors);
    
    //create a pixel array for the foreground image
    unsigned char*** foreground_pixel_array = bmp_to_3D_array(foreground_image_filename, &foreground_header_data, &foreground_header_size, &foreground_width, &foreground_height, &foreground_num_colors);
    
    //checking if num_colors is 4
    if (background_num_colors != 4 || foreground_num_colors != 4){
        printf("The background and foreground images must have BPP=32 (so num_colors=4).");
        return -1;
    }
    //scaling the foreground img
    //the scaled_pixel_array is the new foreground_pixel_array
    unsigned char*** scaled_pixel_array = bmp_scale(foreground_pixel_array, foreground_header_data, foreground_header_size, &foreground_width, &foreground_height, foreground_num_colors, scale);
    //compare the width and height of the scaled img with the width and height of the background img
    if ((foreground_width > background_width) || (foreground_height > background_height)){
        //the foreground img is larger
        printf("The scaled foreground image must be smaller than the background image.");
        return -1;
    }else{
        //the foreground image is smaller than the background image
        //check the offsets
        
        if (((row_offset + foreground_height) > background_height) || ((col_offset + foreground_width) > background_width)){
            printf("The row and column offsets must be such that the foreground is entirely contained within the background");
            return -1;
        }
        //if the code gets here --> there're no assumptions that are violated
        //scaled_pixel_array is the pointer pointing to the scaled foreground image; background_pixel_array is the background image
        //populate pixels of the arrays, update whenever needed
        for(int i=row_offset; i<foreground_height+row_offset; i++){
            for(int j=col_offset; j<foreground_width+col_offset; j++){
                //check the first color
                if(scaled_pixel_array[i-row_offset][j-col_offset][0] == 0){
                    //found a transparent pixel
                    //corresponding pixel in the output image is the pixel in the background
                    //background shows through
                    background_pixel_array[i][j][0] = background_pixel_array[i][j][0];
                    continue;
                    for (int k=1; k<background_num_colors; k++){
                        background_pixel_array[i][j][k] = scaled_pixel_array[(i-row_offset)][(j-col_offset)][k];
                        //foreground shows through
                    }
                }else{
                    //corresponds to the pixel in the foreground
                    for (int k=0; k<background_num_colors; k++){
                        background_pixel_array[i][j][k] = scaled_pixel_array[i-row_offset][j-col_offset][k];
                    }
                }
            }
        }
        bmp_from_3D_array(output_collage_image_filename, background_header_data, background_header_size, background_pixel_array, background_width, background_height, background_num_colors);
    }
  // TO HERE! 
  return 0;
}              

