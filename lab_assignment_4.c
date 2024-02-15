// Brendan Rodriguez
// COP3502C_CMB-23Fall 0023
// Dr. Neslisah Torosdagli
// LAB_4 Assignment:
// An alternate method of storing a string is to store each letter of the string in a single node of a linked list,
// with the first node of the list storing the first letter of the string. 

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head) {

	// Local Variable 
	int numNodes = 0;

	// Avoid crashing on an empty list.
	if(head == NULL) 
		return 0;
	
	// Go to next item.
    node* cur = head->next;
	
	// Linear Traversal To Find End of Linked List
	while (cur != NULL){
		
		// Advance to Next Node and Increment Node Count
		cur = cur->next;
		numNodes++;
	}
	// Exit
	return numNodes;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head) {

	// Local Variables
	int index = 0;
	int len = length(head);

	// Allocate Space for String
	char *string = (char*)malloc((len + 1) * sizeof(char));

	// Memory Allocation Failure
	if(string == NULL){
		printf("Failed to Allocate Memory For String.\n");
		exit(1);
	}
	
	// Traverse Linked List / Set Current Node to Head's Next
	node* cur = head;

	// Loop
	while(cur != NULL){
		string[index++] = cur->letter;
		cur = cur->next;
	}

	// Add Terminating String Character
	string[index] = '\0';

	// Return and Exit
	return string;

}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c){

	// Allocate Space for New Node
	node* newNode = (node*)malloc(sizeof(node));


	// Check for Allocation Failure
	if(newNode == NULL){
		printf("Failed to Allocate Memory For New Node.\n");
		exit(1);
	}

	// Initialize newNode Variables
	newNode->letter = c;
	newNode->next = NULL;

	// Check if empty 
	if(*pHead == NULL){
		*pHead = newNode;
	}
	else{
		// Intialize Current Node to Head
    	node* cur = *pHead;
	
		// Traverse List 
		while (cur->next != NULL) {
        	cur = cur->next;
    	}
	
	// Set Next Node to New Node
    cur->next = newNode;

	}

}

// deletes all nodes in the linkedList.
void deleteList(node** pHead){

	// Initialize Current Node to pHead
    node* cur = *pHead;
	
	// Traverse LinkedList and Deallocate Each Node
    while (cur != NULL) {
		// Initialize newNode Variable
        node* nextNode = cur->next;
		// Deallocate
        free(cur);
		// Iterate to Next Node
        cur = nextNode;
    }

	// Set head pointer to NULL after deleting all nodes
    *pHead = NULL;

}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}