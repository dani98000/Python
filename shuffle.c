#include <fcntl.h> /* open */
#include <sys/mman.h> /* mmap */
#include <stdio.h> /* printf */
#include <sys/stat.h> /* open */
#include <pthread.h> /* pthread_create */

#define LINES 12305
#define FILE_SIZE 971578

char *UploadFile()
{
    int file_descriptor = open("mydic", O_RDONLY, S_IRUSR | S_IWUSR);
    char *file_in_memory = mmap(NULL, FILE_SIZE, PROT_READ, MAP_PRIVATE, file_descriptor, 0); /* 0 is  default, can be chunk of 64k */
    if (file_in_memory == MAP_FAILED)       
    {
        printf("failed load\n");

        return 0;
    }

    return file_in_memory;
}

void shuffle(char *file_runner)
{
	int line_count = 0;
	while(*file_runner != EOF)
	{
		while(*file_runner != '\n')
		{
			printf("%c", *file_runner);
			++file_runner;
		}
		++file_runner;
		++line_count;
		printf("\n");
		++file_runner;
	}
	printf("%d", line_count);
}

int main()
{
	char *buff = UploadFile();
	shuffle(buff);

	return 0;
}