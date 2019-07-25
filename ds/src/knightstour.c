#include <stdio.h>/* printf */
#include <string.h>/* memset */
#include <stdlib.h>/* malloc */
#include <time.h>/* clock */

#include "barr.h"
#include "sort.h"

#define BOARD_SIZE 64
#define BASE 8
#define ISFULLBOARD(x) ((x) == 0XFFFFFFFFFFFFFFFF) 

#define NNW(i) i - 17
#define NNE(i) i - 15
#define EEN(i) i - 6
#define EES(i) i + 10
#define SSE(i) i + 17
#define SSW(i) i + 15
#define WWS(i) i + 6
#define WWN(i) i - 10

#define CYAN      "\x1b[36m\x1b[1m"
#define RESET     "\x1b[0m"

static size_t LUT[64] = {0};

static int IsValid(int i, int next_step);
static void LUTInit();
static void PrintBoard(size_t board);
static void GetNext(size_t board, int current, int arr[9]);
static int IsSolved(int *arr);
static size_t my_ktn(const void *value, const void *args);
static int CountOptionsForNext(int pos);

/*static void PrintArr(size_t *arr)
{
    int i =0, j = 0;
    
    for (; i < 64; ++i)
    {
        printf(CYAN" %lu\n", arr[i]);
        printf("\n");
    }
}*/

static int IsValid(int i, int next_step)
{
	if(next_step < 64 && next_step >= 0)
	{
		if((i % BASE <= 1 && (WWS(i) == next_step || WWN(i) == next_step)) ||
		   (i % BASE == 0 && (SSW(i) == next_step || NNW(i) == next_step)) ||
		   (i % BASE >= 6 && (EEN(i) == next_step || EES(i) == next_step)) ||
		   (i % BASE == 7 && (NNE(i) == next_step || SSE(i) == next_step)))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	return 0;
}

static void LUTInit()
{
	int possible_steps[8];
	int i = 0;
	int j = 0;
	int is_valid = 0;

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		possible_steps[0] = NNE(i);
		possible_steps[1] = EEN(i);
		possible_steps[2] = EES(i);
		possible_steps[3] = SSE(i);
		possible_steps[4] = SSW(i);
		possible_steps[5] = WWS(i);
		possible_steps[6] = WWN(i);
		possible_steps[7] = NNW(i);

		for (j = 0,LUT[i] = 0; j < BASE; ++j)
		{
			is_valid = IsValid(i, possible_steps[j]);
			if(is_valid)
			{
				LUT[i] = BARRSetOn(LUT[i], possible_steps[j]);
			}
		}
	}
}

static int RecSolveKnightsTour(size_t board, int index, int *arr, int path_ind)
{
	int current = index;
	int next = 0;
	int i = 0;
	int possible_steps[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	board = BARRSetOn(board, current);	
	arr[path_ind] = current;

	if (ISFULLBOARD(board))
	{
		return 1;
	}

	GetNext(board, current, possible_steps);
	next = possible_steps[i];
	while(-1 != next )
	{
		++i;

		if(RecSolveKnightsTour(board, next, arr, path_ind + 1) == 1)
		{
			return 1;
		}

		next = possible_steps[i];
	}
		
	return 0;
}

static void GetNext(size_t board, int current, int arr[9])
{
	size_t options = (LUT[current] & board) ^ LUT[current];
	int mask = 0;
	int i = 0; 
	int counter = 0;

	while(mask < 64)
	{
		if(BARRIsOn(options, mask))
		{
			arr[i] = mask;
			++i;
			++counter;
		}
		++mask;
	}

	CountingSort(arr, i, sizeof(int), my_ktn, NULL, 63);
	arr[i] = -1;

}

static size_t my_ktn(const void *value, const void *args)
{	
	(void)(args);

	return (CountOptionsForNext(*(int *)value));
}

static int CountOptionsForNext(int pos)
{
	return BARRCountOnLUT(LUT[pos]);
}

int KnightsTour(int *arr, int index)
{
	size_t board = 0x0;

	LUTInit();

	return RecSolveKnightsTour(board, index, arr, 0);
}

int main()
{
	int arr[64];
	int i = 0;
	int res = 0;
	int j = 0;
	clock_t start,end;
	memset(&arr,0,sizeof(int)*BOARD_SIZE);

	for(; j < 64; ++j)
	{

		printf("running index %d: \n", j);
		start = clock();
		KnightsTour(arr, j);
		end = clock();
		printf("took: %f seconds to finish.\n", ((double)end - start) / CLOCKS_PER_SEC);

		for(i = 0; i < BOARD_SIZE; ++i)
		{
			printf("%d,",arr[i]);
		}

		printf("\n");
		
		res = IsSolved(arr);
		if(res)
		{
			printf("\x1B[32m""SUCCESS\n""\x1B[0m");
		}
		else
		{
			printf("\x1B[31m""FAIL\n""\x1B[0m");

		}

		printf("\n");
	}

	return 0;
}

static void PrintBoard(size_t board)
{
	int i = 0;
	int j = 0;
	system("clear");
	printf("--------------------\n");

	for(; i < BASE; ++i)
	{
		for (j = 0; j < BASE; ++j)
		{
			printf("%d ", BARRIsOn(board, i * BASE + j));
		}
		printf("\n");
	}
	printf("--------------------\n");
}

static int IsSolved(int *arr)
{
	int LUT[64] = {0};
	int i = 0;
	int counter = 0;
	for (i = 0; i < 64; ++i)
	{
		if(LUT[arr[i]] == 1)
		{
			return 0;
		}

		LUT[arr[i]] = 1; 
	}
		
	for (i = 0; i < 64; ++i)
	{
		if (LUT[i] == 1)
		{
			++counter;
		}
	}

	return (counter == 64);
}
