#include <stdio.h> /* printf */
#include <pthread.h> /*pthread_create*/ 
#include <stdlib.h> /* malloc */
#include <string.h> /* strcmp */ 
#include <time.h> /* rand */

#define LINES 102305
#define FILE_SIZE 971578
#define NUM_THREADS 2

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct sort
{
	int size;
	char **arr;
};

typedef int (*cmp_f)(const void *s1, const void *s2);
int Merge(char **words_arr, int size, struct sort *sorted_parts);


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
	qsort(sort->arr, sort->size, sizeof(char *), Compare);

	return NULL;
}

int main()
{
    int i = 0;
	char **words = SaveFile("mydict.txt");
	char **shuffled_dict = 	NULL;
	pthread_t thread_id[NUM_THREADS];
	struct sort sort1[NUM_THREADS];
	int block_size = LINES / NUM_THREADS;
	void *buffer = NULL;
	char **test = NULL;

	DoSomeShuffling(words);

	for (; i < NUM_THREADS; ++i)
    {
    	sort1[i].size = block_size;
    	sort1[i].arr = words + i*block_size;
    	if(i == NUM_THREADS - 1)
    	{
    		sort1[i].size += (LINES % NUM_THREADS);
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

	Merge(words, LINES, sort1);

    for (i = 0; i < LINES; ++i)
    {
       printf("%d: |%s|\n", i, words[i]);
    }


    return 0;
}

int Merge(char **words_arr, int size, struct sort *sorted_parts)
{
	char *current_min_word = NULL; 
	char *max_word = "\xFF";
	int i = 0, j = 0, current_index = 0, current_size = 0, min_index = 0;
	char **temp_arr = NULL; 
	char **current_arr = NULL;
	int index_arr[NUM_THREADS];

	temp_arr = (char **)malloc(sizeof(*temp_arr) * size);
	if (NULL == temp_arr)
	{
		return -1;
	}

	for (i = 0; i < NUM_THREADS; ++i)
	{
		index_arr[i] = 0;
	}

	for (i = 0; i < size; ++i)
	{
		current_min_word = max_word;
		min_index = 0;

		for (j = 0; j < NUM_THREADS; ++j) 
		{
			current_index = index_arr[j];
			current_arr = sorted_parts[j].arr;
			current_size = sorted_parts[j].size;

			if (current_index < current_size 
			    && 0 < strcmp(current_min_word, current_arr[current_index]))
			{
				current_min_word = current_arr[current_index];
				min_index = j;
			}
		}

		++index_arr[min_index];
		temp_arr[i] = current_min_word;
	}

	for (i = 0; i < size; ++i)
	{
		words_arr[i] = temp_arr[i];
	}

	free(temp_arr);
	temp_arr = NULL;

	return  0;
}