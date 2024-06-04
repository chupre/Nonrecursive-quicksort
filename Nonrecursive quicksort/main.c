#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

// Basic consts
#define UNDEFINED -1
#define ARR_SIZE 10

// Array type
#define RANDOM 0
#define ONES 1
#define SORTED 2

// Displays when user input is incorrect
const char* help =
{
"--ones - to generate an array of ones\n\
--rand - to generate a random array to sort\n\
--sort - to generate random sorted array\n"
};


// Stack realization for nonrecursive quicksort
typedef struct stack_obj
{
	int data;
	struct stack_obj* next;
} stack;

stack* push(stack* top, int data);
stack* pop(stack* top);

// Function definitions
void parse_error();
void fill_arr(int* arr, int type);
void swap(int* a, int* b);
int partition(int* arr, int low, int high);
void quicksort_recursive(int* arr, int low, int high);
void quicksort_nonrecursive(int* arr, int low, int high);

int main(int argc, char** argv)
{
	// Rand initialization
	srand((unsigned int)time(NULL));

	int array_type = UNDEFINED;

	// Parse input
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "--rand") == 0)
			{
				array_type = RANDOM;
			}
			else if (strcmp(argv[i], "--ones") == 0)
			{
				array_type = ONES;
			}
			else if (strcmp(argv[i], "--sorted") == 0)
			{
				array_type = SORTED;
			}
			else
			{
				parse_error();
			}
		}
	}
	else
	{
		parse_error();
	}

	if (array_type == UNDEFINED)
	{
		parse_error();
	}

	//Array initialization
	int arr[ARR_SIZE];

	clock_t start, end;

	// Recusrive sort
	fill_arr(arr, array_type);
	start = clock();
	quicksort_recursive(arr, 0, ARR_SIZE - 1);
	end = clock();
	printf("Array is sorted recursively. Time taken: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);

	// Nonrecursive sort
	fill_arr(arr, array_type);
	start = clock();
	quicksort_nonrecursive(arr, 0, ARR_SIZE - 1);
	end = clock();
	printf("Array is sorted nonrecursively. Time taken: %f\n\n", (double)(end - start) / CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}

// Exit program if args are invalid
void parse_error()
{
	printf("%s", help);
	exit(EXIT_SUCCESS);
}


// Fill array depending on args
void fill_arr(int* arr, int type)
{
	// Filling array with ones
	if (type == ONES)
	{
		memset(arr, 1, ARR_SIZE * sizeof(int));
		return;
	}

	// Filling array with random nums < max int
	for (int i = 0; i < ARR_SIZE; i++)
	{
		arr[i] = rand() % INT_MAX;
	}

	// Sorting if required
	if (type == SORTED)
	{
		quicksort_recursive(arr, 0, ARR_SIZE - 1);
	}
}

// Function to swap two elements 
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// Partition function 
int partition(int arr[], int low, int high)
{

	// initialize pivot to be the first element 
	int pivot = arr[low];
	int i = low;
	int j = high;

	while (i < j) {

		// condition 1: find the first element greater than 
		// the pivot (from starting) 
		while (arr[i] <= pivot && i <= high - 1) {
			i++;
		}

		// condition 2: find the first element smaller than 
		// the pivot (from last) 
		while (arr[j] > pivot && j >= low + 1) {
			j--;
		}
		if (i < j) {
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[low], &arr[j]);
	return j;
}

// Recursive quicksort function 
void quicksort_recursive(int arr[], int low, int high)
{
	if (low < high) {

		// call Partition function to find Partition Index 
		int partition_index = partition(arr, low, high);

		// Recursively call quickSort() for left and right 
		// half based on partition Index 
		quicksort_recursive(arr, low, partition_index - 1);
		quicksort_recursive(arr, partition_index + 1, high);
	}
}


stack* push(stack* top, int data)
{
	stack* ptr = malloc(sizeof(stack));

	ptr->data = data;
	ptr->next = top;

	return ptr;
}


stack* pop(stack* top)
{
	if (top == NULL)
	{
		return top;
	}

	stack* ptr_next = top->next;
	free(top);

	return ptr_next;
}

// Nonrecursive quicksort function
void quicksort_nonrecursive(int* arr, int low, int high)
{
	stack* Stack = NULL;

	Stack = push(Stack, high);
	Stack = push(Stack, low);

	while (Stack != NULL)
	{
		low = Stack->data;
		Stack = pop(Stack);

		high = Stack->data;
		Stack = pop(Stack);

		if (high <= low)
		{
			continue;
		}

		int partition_index = partition(arr, low, high);

		if (partition_index - low > high - partition_index)
		{
			Stack = push(Stack, partition_index - 1);
			Stack = push(Stack, low);
			Stack = push(Stack, high);
			Stack = push(Stack, partition_index + 1);
		}
		else
		{
			Stack = push(Stack, high);
			Stack = push(Stack, partition_index + 1);
			Stack = push(Stack, partition_index - 1);
			Stack = push(Stack, low);
		}
	}
}