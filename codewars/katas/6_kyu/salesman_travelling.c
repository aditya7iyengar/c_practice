// Description:

// A traveling salesman has to visit clients. He got each client's address e.g. "432 Main Long Road St. Louisville OH 43071" as a list.

// The basic zipcode format usually consists of two capital letters followed by a white space and five digits. The list of clients to visit was given as a string of all addresses, each separated from the others by a comma, e.g. :

// "123 Main Street St. Louisville OH 43071,432 Main Long Road St. Louisville OH 43071,786 High Street Pollocksville NY 56432".

// To ease his travel he wants to group the list by zipcode.

// Task

// The function travel will take two parameters r (list of all clients' addresses) and zipcode and returns a string in the following format:

// zipcode:street and town,street and town,.../house number,house number,...

// The street numbers must be in the same order as the streets where they belong.

// If a given zipcode doesn't exist in the list of clients' addresses return "zipcode:/"

// Examples

// r = "123 Main Street St. Louisville OH 43071,432 Main Long Road St. Louisville OH 43071,786 High Street Pollocksville NY 56432"

// travel(r, "OH 43071") --> "OH 43071:Main Street St. Louisville,Main Long Road St. Louisville/123,432"

// travel(r, "NY 56432") --> "NY 56432:High Street Pollocksville/786"

// travel(r, "NY 5643") --> "NY 5643:/"
// Note: You can see the list of all addresses and zipcodes in the test cases.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* copyDigit(char* s);

char* copyFromBlank(char* s);

char** split(char *string, char *delimiter, int *length, char *zipcode);

char* travel(char* orgr, char* zipcode) {
  if (strcmp(zipcode, "") == 0) return ":/";

  int lg = 0;
  char** addressList = split(orgr, ",", &lg, zipcode);
  char* unitNumbers = (char*)malloc(sizeof(char) * 100); *unitNumbers = '\0';
  char* streetNames = (char*)malloc(sizeof(char) *  200); *streetNames = '\0';

  for (int i = 0; i < lg; i++) {
    char* rs = addressList[i];
    char* u = copyDigit(rs);
    strcat(unitNumbers + strlen(unitNumbers), u);
    free(u);
    u = copyFromBlank(rs);
    strcat(streetNames + strlen(streetNames), u);
    free(u);
  }

  char* string = calloc(strlen(zipcode) + strlen(unitNumbers) + strlen(streetNames) + 5, sizeof(char));
  char* aux1 = calloc(2, sizeof(char)); strcpy(aux1, ":");
  char* aux2 = calloc(2, sizeof(char)); strcpy(aux2, "/");
  strcat(string, zipcode);

  if (lg == 0) {
    strcat(string + strlen(string), aux1);
    strcat(string + strlen(string), aux2);
  } else {
    *(unitNumbers + strlen(unitNumbers) - 1) = '\0';
    *(streetNames + strlen(streetNames) - 1) = '\0';
    strcat(string + strlen(string), aux1);
    strcat(string + strlen(string), streetNames);
    strcat(string + strlen(string), aux2);
    strcat(string + strlen(string), unitNumbers);
  }

  for (int i = 0; i < lg; i++) {
    char* rs = addressList[i];
    free(rs);
  }

  free(addressList);
  free(unitNumbers);
  free(streetNames);
  return string;
}
