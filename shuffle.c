#include <stdio.h> /* printf */
#include <pthread.h> /*pthread_create*/ 
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */ 
#include <time.h> /* rand */

#define LINES 102305
#define FILE_SIZE 971578
#define NUM_THREADS 4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct sort
{
	int from;
	int to;
	char **arr;
};

typedef int (*cmp_f)(const void *s1, const void *s2);

void swap(char **str1, char **str2)
{
	char *temp = *str1;
	if(str1 != str2)
	{
		*str1 = *str2;
		*str2 = temp;  
	}
}

int Compare(const void *s1, const void *s2)
{
	return strcmp(*(char **)s1 ,*(char **)s2);
}

void DoSomeShuffling(char **words)
{
    int line_count = 0;
    srand(time(NULL));  

    while(line_count < LINES)  
    {
        swap(&words[line_count], &words[rand() % LINES]);
    	++line_count;
    }
}

char **SaveFile(const char *filename)
{
    int i = 0;
    FILE *fp = fopen(filename, "r");
    char **words = (char **)malloc(sizeof(*words) * LINES);
    char *buffer = NULL;
    size_t buflen = 0;
    int line_count = 0;

    for (i = 0; i < LINES && getline(&buffer, &buflen, fp) != -1; ++i)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        words[i] = buffer;
        buffer = 0;
        buflen = 0;
    }

    free(buffer);
    fclose(fp);
    
    return words;
}

void SaveToFile(char **words, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    char *buffer = NULL;
    size_t buflen = 0;
    int line_count = 0;
    int i = 0;

    for (i = 0; i < LINES; ++i)
    {
        fwrite(words[i],sizeof(char), strlen(words[i]),fp);
        fwrite("\n",sizeof(char), 1,fp);
    }
}

void *Sort(void *args)
{
	struct sort *sort = (struct sort *)args;
	qsort(sort->arr + sort->from, sort->to - sort->from, sizeof(char *), Compare);

	return NULL;
}

void Merge(char **arr1, char **arr2, char **array3)
{
        char *array1[LINES], *array2[LINES], m, n, i, j, k = 0;
        i = 0;
        j = 0;

        while (i < m && j < n) 
        {
            if (Compare(array1,array2)) 
            {
            	swap(&array3[k], &array1[i]);
                i++;
            }
            else 
            {
            	swap(&array3[k], &array2[j]);
                j++;
            }
            k++;
        }

        if (i >= m) 
        {
            while (j < n) 
            {
            	swap(&array3[k], &array2[j]);
                j++;
                k++;
            }
        }
 
        if (j >= n) 
        {
            while (i < m)
            {
            	swap(&array3[k], &array1[i]);
                i++;
                k++;
            }
        }
}

int main()
{
    int i = 0;
	char **words = SaveFile("mydic");
	char **shuffled_dict = 	NULL;
	pthread_t thread_id[NUM_THREADS];
	struct sort sort1[NUM_THREADS];
	int block_size = LINES / NUM_THREADS;
	void *buffer = NULL;
	char **test = NULL;

	DoSomeShuffling(words);

	for (; i < NUM_THREADS; ++i)
    {
    	sort1[i].from = i * block_size;
    	sort1[i].to = sort1[i].from + block_size;
    	sort1[i].arr = words;
    	if(i == NUM_THREADS - 1)
    	{
    		sort1[i].to += (LINES % NUM_THREADS);
    	}

        if (0 != pthread_create(&thread_id[i], NULL, Sort, &sort1[i]))
        {
            printf("failed to create thread.\n");

            return 1;
        }
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        if (0 != pthread_join(thread_id[i], NULL))
        {
            printf("failed to join thread.\n");

            return 1;
        }
    }
	/*SaveToFile(words ,"shuff_dict.txt");
	shuffled_dict = SaveFile("shuff_dict.txt");*/

	Merge(sort1[0].arr,sort1[1].arr, test);

    for (i = 0; i < LINES; ++i)
    {
       printf("%d: |%s|\n", i, test[i]);
    }


    return 0;
}