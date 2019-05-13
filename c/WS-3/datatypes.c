#include <stdio.h>
int main()
{
    /* Sizeof operator is used to evaluate the size of a variable*/
    printf("Size of short int: %ld bytes\n",sizeof(short int));
    printf("Size of unsigned short int: %ld bytes\n",sizeof(unsigned short int));
    printf("Size of unsigned int: %ld bytes\n",sizeof(unsigned int));
    printf("Size of int: %ld bytes\n",sizeof(int));
    printf("Size of long int: %ld byte\n",sizeof(long int));
    printf("Size of unsigned long int: %ld bytes\n",sizeof(unsigned long int));
    printf("Size of char: %ld byte\n",sizeof(char));
    printf("Size of signed char: %ld bytes\n",sizeof(signed char));
    printf("Size of unsigned char: %ld byte\n",sizeof(unsigned char));
    printf("Size of float: %ld bytes\n",sizeof(float));
    printf("Size of double: %ld bytes\n",sizeof(double));
    printf("Size of long double: %ld bytes\n",sizeof(long double));
    

    return 0;
}
