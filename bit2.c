/**************************************************************
 *
 *                     bit2.c
 *
 *     Assignment: assignment
 *     Authors:  Theodore Schneider (tschne02), Lindsay Garfinkel (lgarfi01) 
 *     Date:     Feb 5th, 2023
 *
 *     summary:
 *
 *     This is the implementation of the bit2 interface. The functions
 *     below are able to create and free a bit2, as well as perform
 *     other operations.
 *
 **************************************************************/

#include "bit.h"
#include "bit2.h"
#define T Bit2_T 


struct T {
        Bit_T mainArr;
        int height;
        int width;
};

/**********findIndex********
 *
 * Purpose: find the index of a pixel in the Bit2 arr 
 * Inputs:
 *      Bit2_T bitArr: a two-dimensional array of pixel data
 *      int col: the column where the pixel is
 *      int row: the row where the pixel is
 * Return: the new Bit2_T that was created
 * Expects
 *      Bit2_T to not be NULL
 * Notes:
 *      Will CRE if bitArr is NULL
 ************************/
int findIndex(Bit2_T bitArr, int col, int row) 
{
        assert(bitArr != NULL);
        int width = bitArr->width;
        return row * width + col;
}

/**********Bit2_new********
 *
 * Purpose: Create a new Bit2_T array (2d array) with the 
 *          specified height and width
 * Inputs:
 *      int col: the number of columns in the Bit2 array
 *      int row: the number of rows in the Bit2 array
 *
 * Return: the new Bit2 array that was created
 * Expects
 *      col and row to be greater than or equal to 0
 * Notes:
 *      Will CRE if int row or int col are negative
 *      May CRE if malloc fails
 *      Memory allocated in this function is freed in bit2_free
 ************************/
T Bit2_new(int col, int row) 
{
        assert(col >= 0 && row >= 0);

        int arrSize = col * row;

        T myBitArr = malloc(sizeof(*myBitArr));
        assert(myBitArr != NULL);
        
        myBitArr->mainArr = Bit_new(arrSize);
        myBitArr->width = col;
        myBitArr->height = row;

        return myBitArr;
}

/**********Bit2_width********
 *
 * Purpose: Return the width of the given Bit2_T array
 * Inputs:
 *      Bit2_T arr: a two-dimensional array of data
 * Return: the width (number of columns) in the array 
 *              
 * Expects:
 *      Bit2_T bitArr to not be NULL 
 * Notes: 
 *      Will CRE if Bit2_T bitArr is NULL
************************/
int Bit2_width(Bit2_T bitArr) 
{
        assert(bitArr != NULL);
        return bitArr->width;
}

/**********Bit2_height********
 *
 * Purpose: Return the height of the given Bit2_T array
 * Inputs:
 *      Bit2_T bitArr: a two-dimensional array of data
 * Return: the height (number of rows) in the array 
 *      
 * Expects:
 *      Bit2_T bitArr to not be NULL    
 * Notes: 
 *      Will CRE if Bit2_T bitArr is NULL
************************/
int Bit2_height(Bit2_T bitArr) 
{
        assert(bitArr != NULL);
        return bitArr->height;
}

/**********Bit2_get********
 *
 * Purpose: get the value of the bit stored at the specified index
 * Inputs:
 *      Bit2_T: a two-dimensional array of bits
 *      int col: the column where the bit is located 
 *      int row: the row where the bit is located
 * Return: the integer bit value at the index
 * Expects:
 *      Bit2_T bitArr to not be null 
 *      col and row to be greater than or equal to 0
 *      row is <= the number of rows in the bit2 array
 *      col is <= the number of columns in the bit2 array

 * Notes:
 *      Will CRE if col or row is negative
 *      Will CRE if Bit2_T bitArr is NULL
 *      Will CRE if row is >= the number of rows in the bit2 array
 *      Will CRE if col is >= the number of columns in the bit2 array
 *      
 ************************/
int Bit2_get(Bit2_T bitArr, int col, int row) 
{
        assert(bitArr != NULL);
        assert(col < bitArr->width);
        assert(row < bitArr->height);

        int index = findIndex(bitArr, col, row);
        assert(index >= 0);
        return Bit_get(bitArr->mainArr, index);
}

/**********Bit2_put********
 *
 * Purpose: insert a new bit in a specified index in the array of bits
 * Inputs:
 *      Bit2_T: a two-dimensional array of bits
 *      int col: the column where the bit will be inserted 
 *      int row: the row where the bit will be inserted
 *      int bit: the value of the new bit
 * Return: the value of the previous bit in the index
 * Expects:
 *      Bit2_T bitArr to not be null 
 *      bit to be equal to 1 or 0 
 *      col and row to be greater than or equal to 0
 *      row is <= the number of rows in the bit2 array
 *      col is <= the number of columns in the bit2 array
 * Notes:
 *      Will CRE if col or row is negative
 *      Will CRE if Bit2_T bitArr is NULL
 *      Will CRE if bit is not 1 or 0
 *      Will CRE if row is >= the number of rows in the bit2 array
 *      Will CRE if col is >= the number of columns in the bit2 array
 ************************/
int Bit2_put(Bit2_T bitArr, int col, int row, int bit) 
{
        assert(bitArr != NULL);
        assert(col < bitArr->width);
        assert(row < bitArr->height);

        int index = findIndex(bitArr, col, row);
        assert(index >= 0);
        return Bit_put(bitArr->mainArr, index, bit);
}



/**********Bit2_map_col_major********
 *
 * Purpose: Calls the fuction pointed to by apply for every element in the 2d 
 *          array. The apply function is called on elements in column major 
 *          order. 
 * Inputs:
 *       Bit2_T arr: a two-dimensional array of data
 *       void apply: a function taking in 5 parameters 
 *                  (int col, int row, Bit2_T giveBitArr, void *val, void *cl)
 *                  where [col, row] is an index, giveBitArr is a provided
 *                  array, val is a pointer to the value at [col, row], and cl 
 *                  is a pointer to a provided closure
 *       void *cl: an application specific pointer which is passed to apply as 
 *                 an argument
 *              
 * Return: Nothing
 * Expects:
 *      Bit2_T bitArr to not be NULL
 * Notes:
 *              Will CRE if Bit2_T bitArr is NULL
 ************************/
void Bit2_map_col_major(Bit2_T bitArr, void apply(int col, int row, 
                          Bit2_T giveBitArr, int valueBit, void *cl), void *cl) 
{
        assert(bitArr != NULL);
        int col = 0;
        for (int i = 0; i < bitArr->width; i++){
                int row = 0;
                for (int j = 0; j < bitArr->height; j++) {
                        int index = findIndex(bitArr, col, row);
                        
                        apply (col, row, bitArr, Bit_get(bitArr->mainArr,
                               index), cl);
                        row++;
                }
                col++;
        }        
}


/**********Bit2_map_row_major********
 *
 * Purpose: Calls the fuction pointed to by apply for every element in the 2d 
 *          array. The apply function is called on elements in row major 
 *          order. 
 * Inputs:
 *       Bit2_T bitArr: a two-dimensional array of bits
 *       void apply: a function taking in 5 parameters 
 *                   (int col, int row, Bit_T giveBitArr, void *val, void *cl),
 *                   where [col, row] is an index, giveBitArr is a provided
 *                   array, val is a pointer to the value at [col, row], and 
 *                   cl is a pointer to a provided closure
 *                   
 *       void *cl: an application specific pointer which is passed to apply as 
 *                 an argument
 *              
 * Return: Nothing
 * Expects:
 *      Bit2_T bitArr to not be NULL
 * Notes:
 *              Will CRE if Bit2_T bitArr is NULL
 ************************/
void Bit2_map_row_major(Bit2_T bitArr, void apply(int col, int row, 
                          Bit2_T giveBitArr, int valueBit, void *cl), void *cl)
{
        assert(bitArr != NULL);
        int row = 0;
        for (int i = 0; i < bitArr->height; i++){
                int col = 0;
                for (int j = 0; j < bitArr->width; j++) {
                        int index = findIndex(bitArr, col, row);
                        
                        apply (col, row, bitArr, Bit_get(bitArr->mainArr,
                               index), cl);
                        col++;
                }
                row++;
        }        
}


/**********Bit2_free********
 *
 * Purpose: Deallocate all space on heap allocated by the Bit2 functions
 * Inputs:
 *       Bit2_T *arr: a pointer to a two-dimensional array of data
 * Return: none (void function)
 *
 * Expects:
 *      Bit2_T bitArr to not be NULL 
 * Notes: 
 *      Will CRE if Bit2_T bitArr is NULL
************************/
void Bit2_free(Bit2_T *bitArr)
{
        assert(bitArr != NULL);
        Bit_free(&(*bitArr)->mainArr);
        free(*bitArr);
}