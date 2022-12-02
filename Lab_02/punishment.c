#include <stdio.h> 
 int main(){
    int numPunish;
    int typoLine;
    int count;

    printf("Enter the number of times to repeat the punishment phrase: ");
    scanf("%d", &numPunish);

    
    while(numPunish <= 0){
        printf("You entered an invalid value for the number of repetitions!");
        printf("\nEnter the number of times to repeat the punishment phrase again: ");
        scanf("%d", &numPunish);
    }

    printf("\nEnter the repetition line where you want to introduce the typo: ");
    scanf("%d", &typoLine);

    
    while(typoLine <=0 || typoLine > numPunish){
        printf("You entered an invalid value for the typo placement!");
        printf("\nEnter the repetition line where you want to introduce the typo again: ");
        scanf("%d", &typoLine);
    }

    for(count = 0; count < numPunish; count++){
        if(count == typoLine-1){
            printf("\nProgramming in C is phun!");
        }
        else{
            printf("\nProgramming in C is fun!");
        }
    }

    return 0; 
}