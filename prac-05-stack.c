/*Sangmyung University
Computer Science
Data structure
Practice no.5: Stack
Student: Luong Duc Anh ????
ID: 201685044
Professor: Kyungha Min Prof.
prac-05-stack.c*/

/*
  - This program store characters to stack as a linked list
    so the size of stack is size of memmory. Stack will be 
    overflow when memory is full (allocating dynamic memory function
    will return NULL).
  - Each member in the stack is a pointer to a stack-data type.
  - stack-data type is a structure that includes a character variable
  	and a pointer to another stack-data type.
  - Top item is the item which is pushed to the stack after all others. Each
  	time pop and push functions are called, Top item will be changed so there's
  	no TOP() function.
  - initialization can be done by push function -> there's no Init() function.
*/

#include<stdio.h>
#include<stdlib.h>


typedef struct _stack{
	char item;
	struct _stack* next;		//pointer links to next item.
}stack;

/*prototypes*/
int isFull(stack*);				//This function checks if stack is full
void push(stack**,char);		//This function pushes an item to stack
char pop(stack**);				//This function pops an item from stack
void print(stack*);				//This function prints out the stack

int main(void){
	char item;					//Store item
	int choice;					//Read your choice
	//initialize
	stack* top = NULL;			//creating a pointer always point to top item.

	//menu and switch
	puts("MENU");
	puts("1.push\n2.pop\n3.print\n0.Exit\n");
	do{
	choice = 0;
	printf("\nEnter your choice: ");
	scanf("\n%d",&choice);
	switch(choice){
		case 1:{				//calling push function
			//push item to stack
			printf("Enter character: ");
			scanf("\n%c",&item);
			fflush(stdin);		//read exactly 1 character
			push(&top,item);
			break;
		}
		case 2:{				//Invoking pop function
			//pop item from stack
			item = pop(&top);	//popped character will be stored here
			printf("popped character: %c\n",item);
			break;
		}
		case 3:{				//print out stack
			puts("Here is stack: ");
			print(top);
			break;
		}
		default:
			printf("Invalid choice!");
			break;
		}//end switch
	}while(choice != 0);
}//end main

void push(stack** top, char item){
	stack* nItem = (stack*)malloc(sizeof(stack));	//allocating dynamic memory for new item
	if(isFull(nItem)){								//check if stack is full
		printf("Stack is full!(not enough memory)\n");	//Letting you know if stack is full
	}
	else{											//Else,	push new item to the stack
		nItem->item = item;							
		nItem->next = *top;							//Linking the new item to the list
		*top = nItem;								//Changing the top item
	}//end else
}//end function

/*This function will pop out an item and return it*/
char pop(stack** top){
	if(*top == NULL){								//If stack is empty, top pointer points to NULL
		printf("Stack is empty!\n");
		return 0;
	}
	else{											//If stack is not empty...
		stack* tmp = *top;							//copy the address of top item to tmp pointer.
		char item = (*top)->item;					//store top item
		*top = (*top)->next;						//changing top item's address
		free(tmp);									//free the address that is stored in tmp pointer.
		return item;								//return item
	}//end else
}//end function

void print(stack* top){
	while(top != NULL){								//printing respectively all the items in stack.
		printf("%c-->",top->item);
		top = top->next;
	}
	printf("end_stack\n");
}

int isFull(stack* nItem){
	return nItem == NULL;							//if pointer point to NULL return 1, else return 0
}
