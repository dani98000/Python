#include <stdio.h>

int Bursa(int arr[], int arr_length, int *BuyIndex, int *SellIndex)
{
	int *BuyRunner = arr;
	int *SellRunner = arr;
	int profit = *SellRunner - *BuyRunner;
	while(SellRunner - arr < arr_length)
	{
		if(*SellRunner - *BuyRunner > profit)
		{
			profit = *SellRunner - *BuyRunner;
			*SellIndex = SellRunner - arr;
			*BuyIndex = BuyRunner - arr;
		}
		if(*SellRunner < *BuyRunner)
		{
			BuyRunner = SellRunner;
		}
		++SellRunner;
	}
	return profit;
}

int main()
{
	int a[] = {-2,12,3,5,1,-8,9,-10};
	int BuyIndex = 0;
	int SellIndex = 0;
	int profit = Bursa(a,8,&BuyIndex,&SellIndex);
	printf("Profit:%d \nBuy Index:%d \nSell Index:%d\n",profit,BuyIndex,SellIndex); 
	return 0;
}
