#include "include/malloc.h"
#include <stdio.h>

int main() {
	printf("%d\n", getpagesize());
	char *s = malloc(12 * sizeof(char));
	s[11] = 0;
	char c = 'a';
	for (int i = 0; i < 11; i++)
	  s[i] = c++;
	printf("(%p) %s\n", s, s);
}
