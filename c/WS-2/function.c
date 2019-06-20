#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int sstrlen(const char *str)
{
	const char *runner=str;
	while('\0'!= *runner)
	{
		++runner;
	}
	return(runner-str);
}



int str_cmp(const char *s1, const char *s2)
{
	const char *runner1=s1;
	const char *runner2=s2;
	while('\0'!= *runner1 && *runner1==*runner2)
	{
		++runner1;
		++runner2;
	
	}
	return(*runner1-*runner2);
}

char *str_cpy(char *dest, const char *src)
{	
	char *runner=dest;
	
	assert(NULL!=src);
	assert(NULL!=dest);
	
	while(*src!='\0')
	{
		*runner=*src;
		++runner;
		++src;
	}
	*runner='\0';
	return(dest);
}

char *strn_cpy(char *dest, const char *src, size_t n)
{	
	char *runner1=dest;
	const char *runner2=src;
	unsigned int i;
	assert(NULL!=src);
	assert(NULL!=dest);
	for(i=0; (i<n) && (*src!='\0');i++)
	{
		*runner1=*runner2;
		++runner1;
		++runner2;;
	}
	*runner1='\0';
	return(dest);
}

int strcasecmp(const char *s1, const char *s2)
{
	const char *runner1=s1;
	const char *runner2=s2;
	assert(NULL!=s1);
	assert(NULL!=s2);
	while('\0'!= *runner1 && tolower(*runner1)== tolower(*runner2))
	{
		++runner1;
		++runner2;
	}
	return(tolower(*runner1)-tolower(*runner2));
}

char *strchr(const char *s, int c)
{
	const char *runner=s;
	assert(NULL!=s);
	while('\0' != *runner && *runner != c)
	{
		++runner;
	}
	return((char*)runner);
} 

char *strdup(const char *s)
{
	int size = sstrlen(s)+1;
	char* runner=(char*)malloc(size*sizeof(char));
	char* ben=runner;
	assert(NULL!=s);
	while( '\0' != *s )
	{
		*runner=*s;
		++runner;
		++s;
	}
	runner='\0';
	return(ben);
}

char *strcat1(char *dest, const char *src)
{
	char *runner = dest;
	const char *runner2 = src; 											
																			
																	
	assert(NULL != dest);
	assert(NULL != src);

	
	while(*runner != '\0')
	{
		++runner;
	}
	while(*runner2 != '\0')
	{
		*runner = *runner2;
		++runner;
		++runner2;
		
	}
			*runner = '\0'; 	
	return(dest);
}
char *strncat1(char *dest, const char *src, size_t n)
{
	char *runner = dest;
	const char *runner2 = src;
	unsigned int i = 0;
	assert(NULL != dest);
	assert(NULL != dest);
	
	while(*runner != '\0')
	{
		++runner;
	}
	while(*runner2 != '\0' && i<n)
	{
		
			*runner = *runner2;
			++runner;
			++runner2;
			++i;
	}
		*runner = '\0';	

	return(dest);
}


char *strstr1(const char *haystack, const char *needle)
{
	char *haystack_runner = (char *)haystack;
	char *needle_runner = (char *)needle;
	assert(NULL != haystack);
	assert(NULL != needle);
	
	/*run through needle and haystack until one of them reach NULL */
	while(*haystack_runner != '\0' && *needle_runner != '\0')
	{
		/*Check if characters are matching */	
		if(*needle_runner == *haystack_runner)
		{
			++needle_runner;
		}
		/*If they dont match, Go back to the beginning of needle by subtracting the number of characters already found*/
		else
		{
			needle_runner = (char *)needle;
			haystack_runner = (haystack_runner - (needle_runner - needle));
		}
		++haystack_runner;
	}
	/*Check if the needle has ended */
	if(*needle_runner == '\0')
	{
		return(haystack_runner - (needle_runner - needle));
	}
	else
	{
		return NULL;
	}
}


size_t strspn1(const char *s, const char *accept)
{
	char *s_runner=(char *)s;
	char *accept_runner=(char *)accept;
	size_t counter = 0;
	assert(NULL != s);
	assert(NULL != accept);
	
	while(*s_runner != '\0')
	{
		while(*accept_runner != '\0' && *s_runner != *accept_runner)
		{
			++accept_runner;
		}
		
		if('\0' == *accept_runner)
		{
			return counter;
		}
		else
		{
			counter++;
			accept_runner = (char *)accept;
		}
		
		++s_runner;
	}
	return counter;
}

char *BigAdd(const char *str1, const char *str2, char *res)
{
    int len = sstrlen(str1);
    int tmp = 0;
    while (0 <= len)
    {
        *(res + len) += (*(str1 + len) + *(str2 + len));
        if (9 < *(res + len))
        {
            tmp = (*(res + len) % 10);
            ++(*(res + len - 1));
            *(res + len) = tmp;
        }
        --len;
    }
    return res;
}


