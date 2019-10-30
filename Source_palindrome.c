/*Sangmyung University
Computer Science
Data structure
Practice no.5: Stack
Student: Luong Duc Anh ????
ID: 201685044
Professor: Kyungha Min Prof.
palindrome.c*/

/*
- This program read strings from file then check whether string is palindrome.
- If the string has special character -> remove it
- If string has uppercase character -> convert it to lowercase
- After string is converted to completely lowercase character, check it as follows:
1. find the length of string.
2. divide the string into 2 halves and store the former half to a stack by push() function
3. pop out the character in the stack and compare it with the latter half of string, because
stack's rule is first in last out so the last character of the former half should be compared
with the first character of the latter half. If string length is odd number, middle character should
be ignored.
4. After comparing, if all characters in the stack are match with corresponding outside characters
return 1, else return 0.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct _stack {
	char item;
	struct _stack *next;
}stack;

/*function prototype*/
int check_pld(char*);

int main(void) {
	/*Reading data from file*/
	FILE* fp = fopen("test.txt", "r+");
	if (fp == NULL) {
		printf("Can not open file!");
		return -1;
	}
	/*Declaring array for storing strings*/
	char string[128];

	/*Checking whether the strings in line are palindrome*/
	while (fscanf(fp, "%[^\n]%*c", string) != EOF) {
		printf("Origial text: \n%s\n", string);					//original string
		if (check_pld(string))									//checking whether string is palindrome
			printf("---->palindrome.\n");
		else
			printf("---->NOT palindrome.\n");
		puts("");
	}
	getchar();
}//end main


 /*This function checks whether string is palindrome or not*/
int check_pld(char* string) {
	int len = strlen(string);					//find stringlength
	if (len == 1)								//if length = 1 then it is palindrome
		return 1;								//end function

												//else
												/*function prototypes. Decalaring these inside check_pld() function will prevents other functions from calling them*/
	void push(stack**, char);
	char pop(stack**);
	char* delete_non_character(char*, char*);
	void convert_to_lower(char*);

	/*Declaring variable and preparing for checking palindrome string*/
	stack* top = NULL;							//pointer always point to the top item of stack
	char string2[128];
	int i, limit;								//i is string2 array's index and limit is the size of stack

	delete_non_character(string, string2);		//after deleting all non-characters, store string in string2
	convert_to_lower(string2);					//convert all uppercase characters to lower case
	len = strlen(string2);						//find the len of the string
	limit = len / 2;								//find the size of stack

													/*This loop will push characters to stack*/
	for (i = 0; i < limit; i++)
		push(&top, string2[i]);

	/*popping the characters out and comparing them respectively*/
	if (len % 2 == 0) {								//in case string length is even number
		i = 0;									//reset i = 0
		while (string2[limit + i] == pop(&top) && i < limit)
			i++;								//string2[limit+0] is the first character of the latter half of string2
		return i == limit;						//after comparing, if all the characters are equivalent to the corresponding
												//character, i will be incremented until the second expression i<limit is not true
												//=> i = limit if string is palindrome and vice versa.
	}//end if
	else										//in case string length is odd number
		i = 0;
	while (string2[limit + i + 1] == pop(&top) && i < limit)
		i++;
	return i == limit;
}

/*This function removes all the characters that is not in alphabet*/
char* delete_non_character(char* string, char* tmp) {
	int i = 0;						//index of first string
	int j = 0;						//index of second string tmp
	while (string[i] != '\0') {		//checking from the first character to the last character
		if (isalnum(string[i])) {		//isalnum will return 0 if character is not alphabet or number
			tmp[j] = string[i];		//if character is alphabet or number, store it in tmp
			i++;
			j++;
		}
		else						//else, ignore it
			i++;
	}
	tmp[j] = '\0';					//put string termination character to complete the string
	return tmp;						//return address of string
}

/*These below functions are similar to the functions in "prac-05-stack.c", I described them in detail there.*/
void push(stack** top, char item) {
	stack* nItem = (stack*)malloc(sizeof(stack));
	if (nItem == NULL) {
		printf("Memory is full.");
	}
	else {
		nItem->item = item;
		nItem->next = *top;
		*top = nItem;
	}
}

char pop(stack** top) {
	if (*top == NULL) {
		return 0;
	}
	else {
		stack* tmp = *top;
		char pop_item = (*top)->item;
		*top = (*top)->next;
		free(tmp);
		return pop_item;
	}
}

void convert_to_lower(char* string) {
	int i = 0;
	while (string[i] != '\0') {
		string[i] = tolower(string[i]);
		i++;
	}
}