#include "hash.h" /* My header file */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* malloc */


#define SIZE 10000                /* Number of elements in table */
#define WORD_SIZE 100             /* Max size of word */

#define CLEAR "\033[0m"
#define GREEN "\x1B[32m"
#define RED   "\x1B[31m"
#define CYAN  "\x1B[36m"

#define TEST_EQUAL(res, expected) \
++test_no; ++g_total_tests;\
printf("\ttest %lu: expected: %d, got: %d\n",\
test_no, expected, res); result *= (expected == res); \
(expected == res) ? (++g_total_success) : (++g_total_failed);

#define TEST_SUMMARY(tot, success, fail) \
printf(CYAN "\nTest Result Summary:\n" CLEAR); \
printf("Total:     %lu [100.0%%]\n", tot); \
printf(RED "Failed:     %lu [%.1f%%]\n" CLEAR, fail, \
((float)fail / tot) * 100); \
printf(GREEN "Succeeded: %lu [%.1f%%]\n" CLEAR, success, \
((float)success / tot) * 100);


#define RUN_TEST(test)\
if(!test())\
{\
printf("\033[1;31m");\
printf(#test " - failed!\n");\
printf("\033[0m");\
}\
else\
{\
printf("\033[1;32m");\
printf(#test " - ok!\n");\
printf("\033[0m");\
}

size_t g_total_tests = 0;
size_t g_total_success = 0;
size_t g_total_failed = 0;

static int print_list(void *data, const void *arg);
static int cmp(const void *data, const void *key);
static size_t hash_func(void *key);
static int SearchWord(hash_t *hash, void *data);

static int StringCmp(const void *data, const void *key);
static size_t StringHash(void *data);

int Test_Insert();
int Test_Remove();
int Test_Find();
int Test_Dictionary();

int main()
{

	RUN_TEST(Test_Insert);
	RUN_TEST(Test_Remove);
	RUN_TEST(Test_Find);
	RUN_TEST(Test_Dictionary);
	
	TEST_SUMMARY(g_total_tests, g_total_success, g_total_failed);
	
	return 0;
}

int Test_Insert()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	const size_t range = 10;
	int a = 1;
	int b = 2;
	int c = 10;	
	hash_t *hash = HashCreate(cmp, hash_func, range);

	/*TEST1*/
	res = HashIsEmpty(hash);
	TEST_EQUAL(res, 1);

	HashInsert(hash, &a);

	/*TEST2*/
	res = HashIsEmpty(hash);
	TEST_EQUAL(res, 0);

	/*TEST3*/
	res = HashSize(hash);
	TEST_EQUAL(res, 1);

	HashInsert(hash, &b);

	/*TEST4*/
	res = HashSize(hash);
	TEST_EQUAL(res, 2);

	HashInsert(hash, &c);

	/*TEST4*/
	res = HashSize(hash);
	TEST_EQUAL(res, 3);

	/*HashForEach(hash,print_list, NULL);*/

	HashDestroy(hash);

	return result;
}

int Test_Remove()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	const size_t range = 10;
	int a = 1;
	int b = 2;
	int c = 10;	
	hash_t *hash = HashCreate(cmp, hash_func, range);

	/*TEST1*/
	res = HashIsEmpty(hash);
	TEST_EQUAL(res, 1);


	HashInsert(hash, &a);
	HashInsert(hash, &b);
	HashInsert(hash, &c);

	/*TEST2*/
	res = HashIsEmpty(hash);
	TEST_EQUAL(res, 0);


	/*TEST3*/
	res = HashSize(hash);
	TEST_EQUAL(res, 3);

	HashRemove(hash, &a);

	/*TEST4*/
	res = HashSize(hash);
	TEST_EQUAL(res, 2);

	HashRemove(hash, &b);
	HashRemove(hash, &c);

	/*TEST5*/
	res = HashIsEmpty(hash);
	TEST_EQUAL(res, 1);

	HashDestroy(hash);

	return result;
}

int Test_Find()
{
	int result = 1;
	int res = 0;
	size_t test_no = 0;
	const size_t range = 10;
	int a = 1;
	int b = 2;
	int c = 10;	
	int d = 6;
	int n = 0;
	void *found = NULL;
	hash_t *hash = HashCreate(cmp, hash_func, range);

	HashInsert(hash, &a);
	HashInsert(hash, &b);
	HashInsert(hash, &c);
	HashInsert(hash, &d);

	/*TEST1*/
	res = HashSize(hash);
	TEST_EQUAL(res, 4);

	found = HashFind(hash, &a);
	n = *(int *)found;

	res = HashSize(hash);
	TEST_EQUAL(n, a);

	HashRemove(hash, &a);

	found = HashFind(hash, &a);

	res *= found == NULL;

	HashDestroy(hash);

	return result;
}

int Test_Dictionary()
{
	FILE *fp1;
	int result = 1;
	int res = 0;
	size_t test_no = 0;
    char *one_word = (char *)malloc(WORD_SIZE * 102306);
    char *runner = one_word;
    char c = 0;
    int i = 0;
    int word = 0;
    int counter = 0;
    char *searchword = "zucchini";
    char *searchword2 = "sandra";
    int is_present = 0;
    hash_t *table = HashCreate(StringCmp, StringHash, SIZE);

    fp1 = fopen("/usr/share/dict/words", "r");

    while ((c = getc(fp1)) != EOF)
    {
        *runner = c;
        if(c == '\n')
        {
        	*runner = '\0';
        	HashInsert(table, runner - word);
        	word = 0;
        }
        else
        {
        	++word;
        }

        ++runner;
    }

   /* HashForEach(table,print_list, NULL);*/
    is_present = SearchWord(table, searchword);

	TEST_EQUAL(is_present, 1);

	is_present = SearchWord(table, searchword2);

	TEST_EQUAL(is_present, 0);

   /* printf("IS the searchword %s present : %d \n", searchword, is_present);*/
    /*printf("size:%d\n",HashSize(table));*/
     
    fclose(fp1);
    free(one_word);
   	HashDestroy(table);

   	return result;
}

static int SearchWord(hash_t *hash, void *data)
{
	return (HashFind(hash, data) != NULL);
}

static int  print_list(void *data, const void *arg)
{
	(void)(arg);
    printf("%s->", (char *)data);   

    return 0;
}

static int cmp(const void *data, const void *key)
{
	return (*(int *)data == *(int *)key);
}

static size_t hash_func(void *key)
{
	return ((size_t)*(int *)key + (size_t)5) % 10;
}

static int StringCmp(const void *data, const void *key)
{
	return (0 == strcmp(data, key));
}

static size_t StringHash(void *data)
{
    unsigned hashval;
    char *s = (char *)data;

    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31*hashval;
    }

    return hashval % SIZE;
}
