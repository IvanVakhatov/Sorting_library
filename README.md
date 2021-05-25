SORT(3)                Linux Programmer's Manual               SORT(3)

NAME
		sort - sort an array
	
SYNOPSIS
		#include <sort.h>

		void sort(void *array, int size, int elemsize,
				  int (*comp)(void *a1, void *a2));

DESCRIPTION
		The sort() function sorts an array with size elements of size
		elemsize.  The array argument points to the start of the array.

		The contents of the array are sorted with one of eight different sorting
		methods (set by the SORT_METHOD parameter) in ascending or descending
		order (set by the SORT_DIRECTION parameter) according to a comparison
		function pointed to by comp, which is called with two arguments
		that point to the objects being compared.

		The comparison function must return an integer less than, equal
		to, or greater than zero if the first argument is considered to
		be respectively less than, equal to, or greater than the second.
		If two members compare as equal, their order in the sorted array
		is undefined.
		
		Mandatory SORT_METHOD options:
		
			BUBBLE = 1
				Simple exchange sort
			INSERTION = 2
				Simple insertion sort
			SELECTION = 3
				Simple selection sort
			COMB = 4
				Comb sort
			SHELL = 5
				Shell sort
			QUICK = 6
				Quick sort
			MERGE = 7
				Merge sort
			HEAP = 8
				Heap sort
		
		Mandatory SORT_DIRECTION options:
		
			ASCENDING = 10
				Sorting in ascending order	
			DESCENDING = 11
				Sorting in descending order
				
RETURN VALUE
		The sort() function return no value.

AUTHOR
		Written by Ivan Vakhatov.

REPORTING BUGS
		Report any translation bugs to
		ivan.vahatov@yandex.ru

GNU                            May 2021                      SORT(3)