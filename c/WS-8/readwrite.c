#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct DateOfBirth
{
	size_t day;
	size_t month;
	size_t year;
};
struct Contact 
{
	size_t ID;
	char f_name[50];
	char l_name[50];
	struct DateOfBirth dob;
};

struct Contact list[10];
struct Contact list2[10];

int main()
{
	int i = 0;
	FILE *fp;
	fp = fopen( "file.txt" , "w" );
	if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    
    for(; i < 10; i++)
    {
        printf("Enter new contact information\n----------------------------------\n");
        printf("enter First Name > ");
        scanf("%s",list[i].f_name);
        printf("enter Last Name  > ");
        scanf("%s",list[i].l_name);
        printf("enter Birthday \n----------------------------------\n");
        printf("enter day    > ");
        scanf("%lu",&list[i].dob.day);
        printf("enter month  > ");
        scanf("%lu",&list[i].dob.month);
        printf("enter year   > ");
        scanf("%lu",&list[i].dob.year);
        printf("enter ID     > ");
        scanf("%lu",&list[i].ID);
        printf("\n\n\n");
    }
	

	fwrite(list, 10, sizeof(struct Contact), fp);
	fclose(fp);
	fp = fopen( "file.txt" , "r" );
	fread(list2, 10, sizeof(struct Contact), fp);
	fclose(fp);
	
			for(i = 0; i < 10; i++)
	{
	    printf(ANSI_COLOR_RED "First Name: %s\nLast Name: %s\nDate Of Birthday: %lu/%lu/%lu\nID: %lu\n"ANSI_COLOR_RESET,list2[i].f_name, list2[i].l_name, list2[i].dob.day, list2[i].dob.month, list2[i].dob.year, list2[i].ID); 
	    printf("\n"); 
	}
	
	return 0;
}





