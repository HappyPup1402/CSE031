#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>
#include <float.h>

//collaborator christopher fabian

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int b = 1; //index in the char word array that we are currently looking for
int done = 0; //will be true when the final letter in the word has been found

void CAPS_conversion(char* word, int size){ //converts any letter that is a lower case in word to its upper case version
    for(int i = 0; i < size; i++){
        if( *(word+i) >= 'a' && *(word+i) <= 'z' ){
            *(word+i) = *(word+i) - 32;
        }
    }
}

int numberOfDigits(int num){ //gets the total amount of digits that are in the index array
    int d = log10(num)+1;
    return d;
}

int lookForLetter(char** arr, char* word, int i, int j, int letterFind) { //looks for the letter in a certain direction
	if (*(*(arr+i)+j) == *(word+letterFind)){
		return 1;
	}
	return 0;
}
void removeOneIndex(int** indexArr, int i, int j){
    int t = *(*(indexArr+i)+j);
    int ten = numberOfDigits(t);
    int k = (pow(10, ten-1));
    int l = t % k;
    if (t == l) {
        *(*(indexArr+i)+j) = 0;
    }
    else{
        *(*(indexArr+i)+j) = l;
    }

}

int editIndex(int** indexArr, int i, int j, int letterFind, int sizeOfWord) { //adds the index of the letter that is found into the index array
	int t = *(*(indexArr+i)+j); //a temporary element of the index array

    int nextLetter; //will hold the index of the next letter to be found in the word array

    //adds the current index of the word array to index array

	if (t != 0){ //if the index has been used for a letter before
        if(t > 9) { //if the index value is more than one digit "concatinate" the next index at the end
            int ten = numberOfDigits(t);
            nextLetter = letterFind + 1;
		    t = (nextLetter*(pow(10,ten))) + t;
		    *(*(indexArr+i)+j) = t;
        }
        else{ //if the index is one digit just add the index value
            nextLetter = letterFind + 1;
		    t = (nextLetter*10) + t;
		    *(*(indexArr+i)+j) = t;
        }
        
	}
	else{ //if the index has not been used for a letter before
        nextLetter = letterFind + 1;
	    *(*(indexArr+i)+j) = nextLetter;
	}
    
    if (nextLetter == sizeOfWord-1){ //if the final letter has been found mark the search as complete
        done = 1;
    }
    return nextLetter; //returns the index of the next number
}

void lookAround(char** arr, int n, int i, int j, int** indexArr, char* word, int sizeOfWord, int letterFind){ //letterFind is the index of the word array that we are looking for

    if(b == sizeOfWord-1) { //means that the entire word is found so do not resume search
		return;
	}

	if(letterFind == 1){ //when we start at the first letter the index array will start as a 2D array of zeros
		for(int y = 0; y < n; y++) {
			for(int x = 0; x < n; x++){
				*(*(indexArr+y)+x) = 0;
			}
		}
	}

    if(b == 1) { //marks the first index
        *(*(indexArr+i)+j) = 1;
    }

	if (i != 0){
		if (i-1 >= 0) {//looks up
            if(lookForLetter(arr, word, i-1, j, letterFind) == 1) {

                b = editIndex(indexArr, i-1, j, letterFind, sizeOfWord);

				lookAround(arr, n, i-1, j, indexArr, word, sizeOfWord, b);
                if(b == sizeOfWord-1){
                    return; //if the recursion is broken out of back out
                }
                removeOneIndex(indexArr, i-1, j);                    
			}
        }
		if (i-1 >= 0 && j+1 < n){//looks to the top right
            if(lookForLetter(arr, word, i-1, j+1, letterFind) == 1) {
				
                b = editIndex(indexArr, i-1, j+1, letterFind, sizeOfWord);

				lookAround(arr, n, i-1, j+1, indexArr, word, sizeOfWord, b);
                if(b == sizeOfWord-1){
                    return; //if the recursion is broken out of back out
                }
                removeOneIndex(indexArr, i-1, j+1);        
			}
        }
	}
          
          
    if (j+1 < n){//looks at the right
        if(lookForLetter(arr, word, i, j+1, letterFind) == 1) {

			b = editIndex(indexArr, i, j+1, letterFind, sizeOfWord);
                              
			lookAround(arr, n, i, j+1, indexArr, word, sizeOfWord, b);
            if(b == sizeOfWord-1){
                    return; //if the recursion is broken out of back out
                }
            removeOneIndex(indexArr, i, j+1);        
		}
    }
    if (i+1 < n && j+1 < n) {//looks at the bottom right
        if(lookForLetter(arr, word, i+1, j+1, letterFind) == 1) {

            b = editIndex(indexArr, i+1, j+1, letterFind, sizeOfWord);

			lookAround(arr, n, i+1, j+1, indexArr, word, sizeOfWord, b);
            if(b == sizeOfWord-1){
                    return; //if the recursion is broken out of back out
                }
            removeOneIndex(indexArr, i+1, j+1);        
		}
    }
	if (i+1 < n) { //looks at the bottom
		if(lookForLetter(arr, word, i+1, j, letterFind) == 1) {
			
            b = editIndex(indexArr, i+1, j, letterFind, sizeOfWord);

			lookAround(arr, n, i+1, j, indexArr, word, sizeOfWord, b);
            if(b == sizeOfWord-1){
                    return; //if the recursion is broken out of back out
                }
            removeOneIndex(indexArr, i+1, j);        
		}
	}
	if (j!=0){
		if (i+1 < n && j-1 >= 0) {//looks at the bottom left
			if(lookForLetter(arr, word, i+1, j-1, letterFind) == 1) {
                                        
                b = editIndex(indexArr, i+1, j-1, letterFind, sizeOfWord);

				lookAround(arr, n, i+1, j-1, indexArr, word, sizeOfWord, b);
                if(b == sizeOfWord-1){
                    return; //if the recursion is broken out of back out
                }
                removeOneIndex(indexArr, i+1, j-1);        
			}
	    }

		if (j-1 >= 0) {//looks at the left
			if(lookForLetter(arr, word, i, j-1, letterFind) == 1) {
				
                b = editIndex(indexArr, i, j-1, letterFind, sizeOfWord);

				lookAround(arr, n, i, j-1, indexArr, word, sizeOfWord, b);
                if(b == sizeOfWord-1){
                    return; //if the recursion is broken out of back out
                }
                removeOneIndex(indexArr, i, j-1);        
			}
		}
        
		if(i-1 >= 0 && j-1 >=0) {//looks at the top left
			if(lookForLetter(arr, word, i-1, j-1, letterFind) == 1) {
                                        
                b = editIndex(indexArr, i-1, j-1, letterFind, sizeOfWord);

				lookAround(arr, n, i-1, j-1, indexArr, word, sizeOfWord, b);
                if(b == sizeOfWord-1){
                    return; //if the recursion is broken out of back out
                }
                removeOneIndex(indexArr, i-1, j-1);        
			}
		}
	}
}

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%c ", *(*(arr+i)+j));
            if(j == bSize-1){
                printf("\n");
            }
        }
    }
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    char r;
    int count = 0;
    char* temp = word;

    //gets the size of the word
    while ((r = *(temp+count))){
        count++;
    }
    
    int sizeOfWord = count+1;

    CAPS_conversion(word, sizeOfWord);

    int** indexArr;

    indexArr = (int**)malloc(bSize * sizeof(int*));

	for(int i = 0; i < bSize; i++){
    	*(indexArr+i) = (int*)malloc(bSize * sizeof(int));
    }

    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            if (*(*(arr+i)+j) == *(word)){
                if(!done){ //done will be marked as true if the last letter is found
                    b = 1;
                    lookAround(arr, bSize, i, j, indexArr, word, sizeOfWord, b);
                } 
            }
                    

        }
    }
        
    if(b != sizeOfWord-1){
        printf("\nWord not found!\n");
    }

    else{

        printf("\nWord found!");
        printf("\nPrinting the search path:\n");
        for(int i = 0; i < bSize; i++) {
            for(int j = 0 ; j < bSize; j++) {
                printf("%d\t", *(*(indexArr+i)+j));
            }
            printf("\n");
        }
    }
    
}
