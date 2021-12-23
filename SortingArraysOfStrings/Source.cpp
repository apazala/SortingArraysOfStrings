#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char* a, const char* b) {
	while (*a && *a == *b) {
		a++;
		b++;
	}

	return *a - *b;
}

int lexicographic_sort_reverse(const char* a, const char* b) {
	while (*a && *a == *b) {
		a++;
		b++;
	}

	return *b - *a;
}



int sort_by_number_of_distinct_characters(const char* a0, const char* b0) {
	int charflagsa = 0, charflagsb = 0, bitmask, diff = 0;
	const char *a = a0;
	const char *b = b0;
	for (; *a; a++) {
		bitmask = (1 << (*a - 'a'));
		if ((bitmask&charflagsa) == 0) {
			diff++;
			charflagsa |= bitmask;
		}
	}
	for (; *b; b++) {
		bitmask = (1 << (*b - 'a'));
		if ((bitmask&charflagsb) == 0) {
			diff--;
			charflagsb |= bitmask;
		}
	}


	if (diff == 0)
		diff = lexicographic_sort(a0, b0);

	return diff;
}

int sort_by_length(const char* a0, const char* b0) {
	const char *a = a0;
	const char *b = b0;

	int diff = 0;
	for (; *a; a++)
		diff++;
	for (; *b; b++)
		diff--;

	if (diff == 0)
		diff = lexicographic_sort(a0, b0);

	return diff;
}

void string_sort(char** arr, const int len, int(*cmp_func)(const char* a, const char* b)) {
	/* Insert sort */
	int i, j;
	char * x;
	for (i = 1; i < len; i++) {
		j = i-1;
		x = arr[i];
		while (j >= 0 && cmp_func(arr[j], x) > 0) {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j + 1] = x;
	}
}


int main()
{
	int n;
	scanf("%d", &n);

	char** arr;
	arr = (char**)malloc(n * sizeof(char*));

	for (int i = 0; i < n; i++) {
		*(arr + i) = (char*) malloc(1024 * sizeof(char));
		scanf("%s", *(arr + i));
		*(arr + i) = (char*) realloc(*(arr + i), strlen(*(arr + i)) + 1);
	}

	string_sort(arr, n, lexicographic_sort);
	for (int i = 0; i < n; i++)
		printf("%s\n", arr[i]);
	printf("\n");

	string_sort(arr, n, lexicographic_sort_reverse);
	for (int i = 0; i < n; i++)
		printf("%s\n", arr[i]);
	printf("\n");

	string_sort(arr, n, sort_by_length);
	for (int i = 0; i < n; i++)
		printf("%s\n", arr[i]);
	printf("\n");

	string_sort(arr, n, sort_by_number_of_distinct_characters);
	for (int i = 0; i < n; i++)
		printf("%s\n", arr[i]);
	printf("\n");

	return 0;
}