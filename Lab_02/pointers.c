#include <stdio.h> 
 
int main() { 
    int x=0, y=0, *px, *py; 
    int arr[10] = {1,2,3,4,5,6,7,8,9,10}; 

    printf("%d\n", x);
    printf("%d\n", y);
    printf("%d\n", arr[0]);

    px = &x;
    py = &y;

    printf("%p\n", &x);
    printf("%p\n", &y);
    printf("%p\n", px);
    printf("%p\n", py);

    for(int i = 0; i < 10; i++){
        printf("%d ", *(arr + i));
    }

    printf("\n%p", arr);
    printf("\n%p", &arr[0]);
 
    return 0; 
} 