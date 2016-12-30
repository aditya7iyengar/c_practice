// Given an array of positive or negative integers

// I= [i1,..,in]

// you have to produce a sorted array P of the form

// [ [p, sum of all ij of I for which p is a prime factor (p positive) of ij] ...]

// P will be sorted by increasing order of the prime numbers. The final result has to be given as a string in Java, C# or C++ and as an array of arrays in other languages.

// Example:

// I = {12, 15}; // result = "(2 12)(3 27)(5 15)"
// [2, 3, 5] is the list of all prime factors of the elements of I, hence the result.

// Notes: It can happen that a sum is 0 if some numbers are negative!

// Example: I = [15, 30, -45] 5 divides 15, 30 and (-45) so 5 appears in the result, the sum of the numbers for which 5 is a factor is 0 so we have [5, 0] in the result amongst others.

// MY SOLUTION:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct Data Data;

struct Data {
  int* array;
  int size;
};

char* array2StringDataInt(Data *d) {
  if (d->size == 0) return "";
  int l = d->size;
  int* list = d->array;
  char *dest = (char*)calloc(l + 1, sizeof(int) + 2);
  char *p = dest;

  for(int i = 0; i < l; i += 2) {
    sprintf(p += strlen(p), "(%d %d)", list[i], list[i + 1]);
  }

  free(d->array);
  free(d);
  return dest;
}

int* arrdup(int const *src, int len) {
  int* p = malloc(len * sizeof(int));
  memcpy(p, src, len * sizeof(int));
  return p;
}

Data* sumOfDividedAux(int* lst, int l) {
  Data* d = (Data*)malloc(sizeof(Data));
  int* list = (int*)malloc(0 * sizeof(int));
  int sizearr =  0;

  int* rem = arrdup(lst, l);
  int max = 0;

  for (int i = 0; i < l; ++i) {
    int v = abs(lst[i]);
    rem[i] = v;
    max = max > v ? max : v;
  }

  for (int fac = 2; fac <= max; ++fac) {
    bool isFactor = false;
    int tot = 0;

    for (int i = 0; i < l; ++i) {
      if (rem[i] % fac == 0) {
        isFactor = true;
        tot += lst[i];
        while (rem[i] % fac == 0)
          rem[i] /= fac;
      }
    }

    if (isFactor) {
      list = (int*)realloc(list, (sizearr + 2) * sizeof(int));
      list[sizearr] = fac;
      list[sizearr + 1] = tot;
      sizearr += 2;
    }
  }

  free(rem);
  d->size = sizearr;
  d->array = list;
  return d;
}

char* sumOfDivided(int* lst, int l) {
  Data* d = sumOfDividedAux(lst, l);
  char* s = array2StringDataInt(d);
  return s;
}
