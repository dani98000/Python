int main(int argc, char *argv[])
{
	int counter = 0;

	WDStart(argc, argv, 60);

	/*while(counter < 10)
	{
		printf("%d\n", ++counter);
		sleep(1);
	}
	WDStop();*/

	while(1)
	{
		printf("%d\n", ++counter);
		sleep(1);
	}

	return 0;
}