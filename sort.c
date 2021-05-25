/********************************************
 * Файл: sort.c                             *
 * Краткое описание файла:                  *
 * 		Реализация функций сортировки       *
 *                                          *
 * Автор: Вахатов Иван Алексеевич           *
 * Группа: ПРИ20.20                         *
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int SORT_METHOD = QUICK;
int SORT_DIRECTION = ASCENDING;

/* Функция для сравнения двух элементов */
int comp(void *a, void *b) {
	return *(int *)a - *(int *)b;
}

/* Заменяет указанное количество бит между двумя областями в памяти */
void swap(void *a, void *b, int elemsize) {
	char *x = (char *)a, *x_end = x + elemsize;
	char *y = (char *)b, temp;
	while (x < x_end) {
		temp = *x;
		*x = *y;
		*y = temp;
		x++;
		y++;
	}
}

/* ФУНКЦИЯ СОРТИРОВКИ ПУЗЫРЬКОМ
Работает до тех пор, пока весь массив не будет отсортирован.
После n-ой итерации, n самых больших элементов верно расположены в конце массива.
Далее "просматривается" только несортированная часть массива. */
void sort_bubble(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2)) {
	char *start = (char *)array;
	char *end = start + size * elemsize;
	char *ptr1, *ptr2, *lastswap;

	while (start < end) {
		lastswap = start;
		ptr1 = start;
		ptr2 = ptr1 + elemsize;
		while (ptr2 < end) {
			if (comp(ptr1, ptr2) > 0) { /* Если ptr1 > ptr2 */
				swap(ptr1, ptr2, elemsize);
				lastswap = ptr2;
			}
			ptr1 = ptr2;
			ptr2 += elemsize;
		}
		end = lastswap;
	}
}

/* ФУНКЦИЯ СОРТИРОВКИ ВСТАВКОЙ
Работает до тех пор, пока весь массив не будет отсортирован.
Проходит через каждую пару элементов от n-го элемента в массиве до начала массива,
сравнивает их и меняет местами, если они стоят в неправильном порядке. */
void sort_insertion(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2)) {
	char *start = (char *)array;
	char *end = start + size * elemsize;
	char *ptr1, *ptr2, *current;

	for (current = start; current < end; current += elemsize) {
		ptr2 = current;
		ptr1 = ptr2 - elemsize;
		while((ptr2 > start) && (comp(ptr1, ptr2) > 0)) {
			swap(ptr1, ptr2, elemsize);
			ptr2 = ptr1;
			ptr1 -= elemsize;
		}
	}
}

/* ФУНКЦИЯ СОРТИРОВКИ ВЫБОРОМ
Работает до тех пор, пока весь массив не будет отсортирован.
После n-ой итерации, n самых маленьких элементов верно расположены в начале массива.
Далее "просматривается" только несортированная часть массива. */
void sort_selection(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2)) {
	char *start = (char *)array; /* Указатель на начало массива */
	char *end = start + size * elemsize; /* Указатель на конец неотсортированной части массива */
	char *ptr; /* Указатель на сравниваемый элемент */
	char *min; /* Указатель на наименьший элемент, который будет "обменен" */

	while (start < end) {
		min = start;
		ptr = start + elemsize;
		while(ptr < end) {
			if (comp(min, ptr) > 0) {
				min = ptr;
			}
			ptr += elemsize;
		}
		swap(start, min, elemsize);
		start += elemsize;
	}
}

/* ФУНКЦИЯ СОРТИРОВКИ РАСЧЕСКОЙ
Рассчитывает gap с учетом предыдущего gap'a и "коэффициентом сокращения".
Проверяет, отсортирован ли массив.
Если gap больше 1 или происходит перестановка элементов, то массив не отсортирован. */
void sort_comb(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2)) {
	char *start = (char *)array; /* Указатель на начало массива */
	char *end = start + size * elemsize; /* Указатель на конец неотсортированной части массива */
	char *ptr1, *ptr2;
	int FLAG = 0; /* FLAG - переменная-флаг окончания сортировки */
	int gap = size; /* Расстояние между двумя сравниваемыми элементами */

	while (!FLAG) {
		gap = gap / COMB_DISTANCE;
		if (gap <= 1) {
			FLAG = 1;
			gap = 1;
		}

		ptr1 = start;
		ptr2 = ptr1 + gap * elemsize; 
		while(ptr2 < end) {
			if (comp(ptr1, ptr2) > 0) {
				swap(ptr1, ptr2, elemsize);
				FLAG = 0;
			}
			ptr1 += elemsize;
			ptr2 += elemsize;
		}
	}
}

/* ФУНКЦИЯ СОРТИРОВКИ ШЕЛЛА */
void sort_shell(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2)) {
	char *start = (char *)array;
	char *end = start + size * elemsize;
	char *ptr1, *ptr2, *current;
	char *ptr2min;
	
	int gaps[] = SHELL_GAPS;
	int gapscount = SHELL_GAPS_NUM, gap_index, gapsize;

	gap_index = 0;
	while (gap_index < gapscount && gaps[gap_index] >= size) {
		gap_index++;
	}

	while (gap_index < gapscount) {
		gapsize = gaps[gap_index] * elemsize;
		ptr2min = start + gapsize;
		for (current = ptr2min; current < end; current += elemsize) {
			ptr2 = current;
			ptr1 = ptr2 - gapsize; 
			while(ptr2 >= ptr2min && comp(ptr1, ptr2) > 0) {
				swap(ptr1, ptr2, elemsize);
				ptr2 = ptr1;
				ptr1 -= gapsize;
			}
		}
		gap_index++;
	}
}

/* ФУНКЦИЯ БЫСТРОЙ СОРТИРОВКИ */
void sort_quick(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2)) {
	int i = 0;
	int j = size - 1;
	void *pivot = malloc(elemsize);
	memcpy(pivot, array + size/2 * elemsize, elemsize);
	
	do {
		while(comp(array + i*elemsize, pivot) < 0) {
			i++;
		}
		while(comp(array + j*elemsize, pivot) > 0) {
			j--;
		}
		if (i <= j) {
			swap(array + i*elemsize, array + j*elemsize, elemsize);
			i++;
			j--;
		}
	} while (i <= j);
	
	if(j > 0) {
		sort_quick(array, j + 1, elemsize, comp);
	}
	if (i < size) {
		sort_quick(array + i*elemsize, size - i, elemsize, comp);
	}
	free(pivot);
}

/* ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ СОРТИРОВКИ СЛИЯНИЕМ*/
void mergefunc(void *array, int size1, int size2, int elemsize, int(*comp)(void *a1, void *a2)) {
	int array1size = size1 * elemsize;
	char *current = (char *)array;
	char *array1 = (char *)malloc(array1size);
	char *ptr1 = array1, *ptr2 = current + array1size;
	char *ptr1end = array1 + array1size, *ptr2end = ptr2 + size2 * elemsize;

	if (!ptr1) {
		fprintf(stderr, "Недостаточно памяти! \n");
		exit(1);
	}
	memcpy(array1, array, array1size);

	while (ptr1 < ptr1end && ptr2 < ptr2end) {
		if (comp(ptr1, ptr2) <= 0) {
			memcpy(current, ptr1, elemsize);
			ptr1 += elemsize;
		} else {
			memcpy(current, ptr2, elemsize);
			ptr2 += elemsize;
		}
		current += elemsize;
	}

	if (ptr1 < ptr1end) {
		memcpy(current, ptr1, ptr1end - ptr1);
	}
	free(array1);
}

/* ФУНКЦИЯ СОРТИРОВКИ СЛИЯНИЕМ
Алгоритм использует рекурсивный метод "разделяй и властвуй" для сортировки 
половин массива, а затем их объединения. */
void sort_merge(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2)) {
	char *ptr1 = (char *)array, *ptr2;
	int n = size / 2, m = size - n;

	if (size <= 1) {
		return;
	}
	else if (size == 2) {
		ptr2 = ptr1 + elemsize;
		if (comp(ptr1, ptr2) > 0) {
			swap(ptr1, ptr2, elemsize);
		}
	} else {
		ptr2 = ptr1 + n * elemsize;
		sort_merge(array, n, elemsize, comp);
		sort_merge(ptr2, m, elemsize, comp);
		mergefunc(array, n, m, elemsize, comp);
	}
}

/* ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ НАХОЖДЕНИЯ БОЛЬШЕЙ ВЕРШИНЫ ДЛЯ ЧАСТИ ПИРАМИДЫ */
int maximum(void *array, int size, int i, int j, int k, int elemsize, int(*comp)(void *a1, void *a2)) {
	int a = i;
	if ((j < size) && (comp(array + j*elemsize, array + a*elemsize) > 0)) {
		a = j;
	}
	if ((k < size) && (comp(array + k*elemsize, array + a*elemsize) > 0)) {
		a = k;
	}
	return a;
}

/* ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ПОСТРОЕНИЯ НИСХОДЯЮЩЕЙ ПИРАМИДЫ */
void heapify(void *array, int size, int i, int elemsize, int(*comp)(void *a1, void *a2)) {
	while (1) {
		int j = maximum(array, size, i, 2*i + 1, 2*i + 2, elemsize, comp);
		if (j == i) {
			break;
		}
		swap(array + i*elemsize, array + j*elemsize, elemsize);
		i = j;
	}
}

/* ФУНКЦИЯ ПИРАМИДАЛЬНОЙ СОРТИРОВКИ */
void sort_heap(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2)) {
	int i;
	for (i = (size - 2) / 2; i >= 0; i--) {
		heapify(array, size, i, elemsize, comp);
	}
	for (i = 0; i < size; i++) {
		swap(array + (size-i-1)*elemsize, array, elemsize);
		heapify(array, size - i - 1, 0, elemsize, comp);
	}
}

/* ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ДЛЯ СОРТИРОВКИ МАССИВА В ПОРЯДКЕ УБЫВАНИЯ */
void array_util(void *array, int size) {
	int i;
	for (i = 0; i < size; i++) {
		((int *)array)[i] = ((int *)array)[i] * (-1);
	}
}

/* ФУНКЦИЯ, ПРОВЕРЯЮЩАЯ ПРАВИЛЬНОСТЬ ОТСОРТИРОВАННОГО МАССИВА */
void check_array(void *array, int size) {
	int i;
	switch (SORT_DIRECTION) {
		case ASCENDING:
			for (i = 0; i < size - 1; i++) {
				if (((int *)array)[i] > ((int *)array)[i+1]) {
					printf("Массив отсортирован неверно!\n");
					exit(1);
				}
			}
			break;
		case DESCENDING:
			for (i = 0; i < size - 1; i++) {
				if (((int *)array)[i] < ((int *)array)[i+1]) {
					printf("Массив отсортирован неверно!\n");
					exit(1);
				}
			}
			break;
	}
}

/* ИНТЕРФЕЙСНАЯ ФУНКЦИЯ СОРТИРОВКИ */
int sort(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2)) {
	if(SORT_METHOD < 0 || SORT_METHOD > 8) {
		fprintf(stderr, "Сортировка невозможна! Выберите другой номер для метода сортировки\n");
		exit(1);
	}
	else if(SORT_DIRECTION < 10 || SORT_DIRECTION > 11) {
		fprintf(stderr, "Сортировка невозможна! Выберите другой номер для направления сортировки\n");
		exit(1);
	}
	else if(comp == NULL) {
		fprintf(stderr, "Ошибка указателя на функцию сравнения\n");
		exit(1);
	}

	switch (SORT_DIRECTION) {
		case DESCENDING:
			array_util(array, size);
			break;
		case ASCENDING:
			break;
	}

	switch (SORT_METHOD) {
		case BUBBLE:
			sort_bubble(array, size, elemsize, comp);
			break;
		case INSERTION:
			sort_insertion(array, size, elemsize, comp);
			break;
		case SELECTION:
			sort_selection(array, size, elemsize, comp);
			break;
		case COMB:
			sort_comb(array, size, elemsize, comp);
			break;
		case SHELL:
			sort_shell(array, size, elemsize, comp);
			break;
		case QUICK:
			sort_quick(array, size, elemsize, comp);
			break;
		case MERGE:
			sort_merge(array, size, elemsize, comp);
			break;
		case HEAP:
			sort_heap(array, size, elemsize, comp);
			break;
		default:
			sort_quick(array, size, elemsize, comp);
			break;
	}
	
	switch (SORT_DIRECTION) {
		case DESCENDING:
			array_util(array, size);
			break;
		case ASCENDING:
			break;
	}
}

/* ФУНКЦИЯ ДЛЯ ПРОВЕРКИ ВСЕХ МЕТОДОВ СОРТИРОВКИ */
int sort_methods_test(int ARRAYSIZE) {
	int i, method, direction;
	int array[ARRAYSIZE];
	
	for(method = 1; method < 9; method++) {
		for(i = 0; i < ARRAYSIZE; i++) {
			array[i] = rand()%100;
		}
		
		printf("Номер метода сортировки: %d\n", method);
		printf("Сгенерированный массив: \n");
		for (i = 0; i < ARRAYSIZE; i++) {
			printf("%d ", array[i]);
		}
		printf("\n");
		
		for(direction = 10; direction < 12; direction++) {
		
			SORT_METHOD = method;
			SORT_DIRECTION = direction;
			sort(array, ARRAYSIZE, sizeof(array[0]), comp);
			check_array(array, ARRAYSIZE);
			
			if (SORT_DIRECTION == ASCENDING) {
				printf("Отсортированный массив в порядке возрастания: \n");
			} else {
				printf("Отсортированный массив в порядке убывания: \n");
			}
			for (i = 0; i < ARRAYSIZE; i++) {
				printf("%d ", array[i]);
			}
			printf("\n");
		}
		printf("\n");
	}
}