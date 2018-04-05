//Mayank Bansal<br>
//A20392482<br>
//mbansal5@hawk.iit.edu

//Josiah Hunt<br>
//A20350987<br>
//jhunt5@hawk.iit.edu


#include <stdlib.h>
#include <stdio.h>
int NUM = 5;
int NUM2 = 4;

int NEAT = 0;
int NEAT2 = 0;

int main(int argc, char* argv[]){

    int *test = malloc(5*sizeof(*test));

    for(int i = 0; i<NUM; i++){
	test[i] = i;
	printf("INT: %d\n", test[i]);

    }
    if(NEAT){
	free(test);
    }

    int *test2[NUM];
    for (int i=0; i<NUM; i++)
         test2[i] = (int *)malloc(NUM2 * sizeof(int));

    int count = 0;
    for (int i = 0; i <  NUM; i++)
      for (int j = 0; j < NUM2; j++)
         test2[i][j] = ++count;

    for (int i = 0; i <  NUM; i++){
      for (int j = 0; j < NUM2; j++){
         printf("%d ", test2[i][j]);
      }
      printf("\n");
    }

    if(NEAT2){
	for(int i = 0; i < NUM; i++){
	    free(test2[i]);
	}
    }

}
