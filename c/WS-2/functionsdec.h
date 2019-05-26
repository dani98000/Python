int sstrlen(const char *str);
int str_cmp(const char *s1, const char *s2);
char *str_cpy(char *dest, const char *src);
char *strn_cpy(char *dest, const char *src, size_t n);
int strcasecmp(const char *s1, const char *s2);
char *strchr(const char *s, int c);
char *strdup(const char *s);
char *strcat1(char *dest, const char *src);
char *strncat1(char *dest, const char *src, size_t n);
char *strstr1(const char *haystack, const char *needle);
size_t strspn1(const char *s, const char *accept);
void RmSpaces(char *str);
char *BigAdd(const char *str1, const char *str2, char *res);
char *strtok1(char *str, const char *delim);

