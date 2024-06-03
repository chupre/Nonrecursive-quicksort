#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

//Basic consts
#define UNDEFINED -1
#define ARR_SIZE 2048

//Array type
#define RANDOM 0
#define ONES 1

//Displays when user input is incorrect
const char* help =
{
	"\t--ones - to sort an array of ones\n\
	--rand - to generate a random array to sort\n\n"
};

void parse_error();
void fill_arr(int* arr, int type);

int main(int argc, char** argv)
{
	//Rand initialization
	srand(time(NULL));

	int array_type = UNDEFINED;

	//Parse input
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
	fill_arr(arr, array_type);

	return EXIT_SUCCESS;
}

//Exit program if args are invalid
void parse_error()
{
	printf("%s", help);
	exit(EXIT_SUCCESS);
}


//Fill array depending on args
void fill_arr(int* arr, int type)
{
	//Filling array with ones
	if (type == ONES)
	{
		memset(arr, 1, ARR_SIZE * sizeof(int));
		return;
	}

	//Filling array with random nums < max int
	for (int i = 0; i < ARR_SIZE; i++)
	{
		arr[i] = rand() % INT_MAX;
	}
}