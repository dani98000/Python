int add(int x,int y)
{
	int carry = 0;

	if(y == 0)
	{
		return x;
	}
	
	carry = x & y;
	x = x ^ y;	
	return add(x,(carry)<<1);
}


int main()
{
	int res = add(5,9);
	printf("%d",res);
	
	return 0;
}
