void RmSpaces(char *str)
{
	char *runner = str;
	char *cleanspaces= str;
	char *start=str;
	int saw_white=0;
	while(isspace(*runner))
	{
		++start;
		++runner;
		saw_white=1;
	}
	while(*start != '\0' )
	{	
		if(isspace(*start))
		{
			if(saw_white == 1)
			{
				++start;
			}
			else
			{
				*cleanspaces = *start;
				saw_white = 1;
				++cleanspaces;
				++start;
			}
		}	
		else
		{
			if(saw_white == 1)
			{
				saw_white = 0;
				*cleanspaces=*start;
			}
			else
			{
				*cleanspaces=*start;
			}
			++cleanspaces;
			++start;
		}
	}
		/*Makes sure that you end the string in the right place. */
		if(isspace(*(cleanspaces-1)))
		{
			*(cleanspaces-1)='\0';
		}
		else
		{
			*(cleanspaces)='\0';
		}

	
}
