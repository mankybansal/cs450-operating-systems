#include "stdlib.h"
#include "stdio.h"

int main(int argc, char *argv[]){

    int *data = malloc(100 * sizeof(int));
    printf("data:\n");
    for(int i = 0; i < 100; i++){
	data[i] = i;
	printf("%d, ", data[i]);
	if((i+1)%10 == 0){
	   printf("\n");
	}
    }
    printf("\n");

    free(data);
    printf("After free\n");
    for(int i = 0; i < 100; i++){	
    	printf("%d, ", data[i]);
	if((i+1)%10 == 0){
	   printf("\n");
	}
    }
}
