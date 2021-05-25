#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

#define ARRAYSIZE 10

int main() {
	/*int i;
	int array[ARRAYSIZE];
	
	srand(time(NULL));
	for(i = 0; i < ARRAYSIZE; i++) {
		array[i] = rand()%500;
	}
	printf("Сгенерированный массив: \n");
	for (i = 0; i < ARRAYSIZE; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	
	SORT_METHOD = BUBBLE;
	SORT_DIRECTION = DESCENDING;
	sort(array, ARRAYSIZE, sizeof(array[0]), comp);
	check_array(array, ARRAYSIZE);
	
	printf("Отсортированный массив: \n");
	for (i = 0; i < ARRAYSIZE; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");*/

	srand(time(NULL));
	sort_methods_test(ARRAYSIZE);
	return 0;
}