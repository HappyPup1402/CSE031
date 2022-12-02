#include<stdio.h>

int sum(int a, int b){
    return a + b;
}

int main(){
    int m = 10; 
    int n = 5;
    
    printf("%d", sum(m,n));
    return 0;
}