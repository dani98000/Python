#include <stdio.h>

#define BOARD_SIZE 64
#define BASE 8

#define NNW(i) i+2*BASE-1
#define NNE(i) i+2*BASE+1
#define EEN(i) i+BASE+2
#define EES(i) i-BASE+2
#define SSE(i) i-2*BASE-1
#define SSW(i) i-2*BASE+1
#define WWS(i) i-BASE-2
#define WWN(i) i+BASE-2

static size_t LUT[64];
static size_t Board[64]

static int IsValid(int i, int next_step);
static void LUTInit(size_t LUT[]);

static int IsValid(int i, int next_step)
{
	flag = 0;

	if(next_step < 64 && next_step >= 0)
	{
		if((i % base <= 1 && WWS(i) == next_step || WWN(i) == next_step) ||
		   (i % base == 0 && SSW(i) == next_step || NNW(i) == next_step) ||
		   (i % base >= 6 && EEN(i) == next_step || EES(i) == next_step) ||
		   (i % base == 7 && NNW(i) == next_step || SSW(i) == next_step))
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

static int GetNextStep(int i)
{
	return ((LUT[i] && Board[i]) ^ LUT[i]);
}

static void LUTInit(size_t LUT[])
{
	int possible_steps[8];
	int i = 0;
	int j = 0;
	int is_valid = 0;

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		steps[0] = NNW(i);
		steps[1] = NNE(i);
		steps[2] = EEN(i);
		steps[3] = EES(i);
		steps[4] = SSE(i);
		steps[5] = SSW(i);
		steps[6] = WWS(i);
		steps[7] = WWN(i);
	}

	for (LUT[i] = 0; j < BASE; ++i)
	{
		is_valid = IsValid(i, steps[j]);
		LUT[i] = BarrSetBit(LUT[i], steps[j], is_valid);
	}
}

static void BoardInit()
{
	int i = 0;

	for (i = 0; i < BOARD_SIZE; ++i)
	{
		Board[i] = 0;
	}
}

static int RecSolveKnightsTour(int index, int *arr)
{
	int current = index;
	int next = 0;
	BARRSetOn(Board, current);	
	next = GetNextStep(current)

	*arr = current;
	++arr;
	if(next == 0)
	{
		if (BARRCountOn(Board) == BOARD_SIZE)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (Board[next] == 1)
	{
		RecSolveKnightsTour(current);
	}
	else
	{
		RecSolveKnightsTour(next);
	}

	
}

int KnightsTour(int *arr)
{
	RecSolveKnightsTour(0);
}

int main()
{
	int arr[64];

	KnightsTour(&arr)
	return 0;
}



/*void KnightsTourInit(int *arr, )
{
	int i = 0;
	for(; i < 64; ++i)
	{
		if(i + 2 * base - 1 > 0 && i + 2 * base - 1 < 64)
		{
			BARRSetOn(LUT[i], i + 2 * base + 1)
		}
		BARRSetOn(LUT[i], i + 2 * BASE - 1)
		BARRSetOn(LUT[i], i - 2 * BASE + 1)
		BARRSetOn(LUT[i], i - 2 * BASE - 1)
		BARRSetOn(LUT[i], i + 1 * BASE + 2)
		BARRSetOn(LUT[i], i + 1 * BASE - 2)
		BARRSetOn(LUT[i], i - 1 * BASE + 2)
		BARRSetOn(LUT[i], i - 1 * BASE - 2)
		if (i % base == 0)				
		{
				
		}	
		if (i % base == 1)				
		{
				
		}					
	}
}*/