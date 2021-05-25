/********************************************
 * Файл: sort.h                             *
 * Краткое описание файла:                  *
 * 		Описание функций сортировки         *
 *                                          *
 * Автор: Вахатов Иван Алексеевич           *
 * Группа: ПРИ20.20                         *
 ********************************************/

#ifndef SORT_H_
#define SORT_H_

/* "Говорящие" константы для параметра SORT_METHOD */
#define BUBBLE 1 //Простой обмен
#define INSERTION 2 //Простая вставка
#define SELECTION 3 //Простой выбор
#define COMB 4 //Расчёской
#define SHELL 5 //Шелла
#define QUICK 6 //Быстрая
#define MERGE 7 //Слиянием
#define HEAP 8 //Пирамидальная

/* "Говорящие" константы для параметра SORT_DIRECTION */
#define ASCENDING 10 //Сортировка по возрастанию
#define DESCENDING 11 //Сортировка по убыванию

#define COMB_DISTANCE 1.3 //Константа для сортировки расчёской
/* Константные значения для последовательности промежутков в сортировке Шелла */
#define SHELL_GAPS {40423, 17966, 7985, 3549, 1577, 701, 301, 132, 57, 23, 10, 4, 1}
#define SHELL_GAPS_NUM 13 //Количество промежутков в сортировке Шелла

extern int SORT_METHOD; //Параметр выбора метода сортировки
extern int SORT_DIRECTION; //Параметр выбора направления сортировки

int comp(void *a, void *b);
void swap(void *a, void *b, int elemsize);
void sort_bubble(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2));
void sort_insertion(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2));
void sort_selection(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2));
void sort_comb(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2));
void sort_shell(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2));
void sort_quick(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2));
void mergefunc(void *array, int size1, int size2, int elemsize, int(*comp)(void *a1, void *a2));
void sort_merge(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2));
int maximum(void *array, int size, int i, int j, int k, int elemsize, int(*comp)(void *a1, void *a2));
void heapify(void *array, int size, int i, int elemsize, int(*comp)(void *a1, void *a2));
void sort_heap(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2));
void array_util(void *array, int size);
void check_array(void *array, int size);
int sort(void *array, int size, int elemsize, int(*comp)(void *a1, void *a2));
int sort_methods_test(int ARRAYSIZE);

#endif