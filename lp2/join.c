#include <stdio.h>

const char base_string[] = "base_string";
char out_string [100];
int number = 123;
sprintf("out_string, %s %d", base_string, number);
printf("out_string = %s\n", out_string);