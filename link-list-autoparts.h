// Header file containing link-list definitions & implementation methods
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_LENGTH 11

// Structure Definition
struct item{
	char partId[ID_LENGTH];
	int partQuantity;
	char partType;
	struct item *nextPtr;
};

// Structure renaming
typedef struct item Item;
typedef struct item *ItemPtr;

/* Function Prototypes */
ItemPtr makeItem(char partId[ID_LENGTH], int partQuantity, char partType);				//makeItem ();
ItemPtr addItem(ItemPtr sPtr, char partId[ID_LENGTH], int partQuantity, char partType);	//addItem ();
void printList(ItemPtr sPtr);				//printList ();
//removeItem ();
void updateItem(ItemPtr sPtr, char searchPartId[ID_LENGTH]);
void viewItem (ItemPtr sPtr, char partId[ID_LENGTH]);
void displayMenuOptions ();
 
/*******Function Definitions******/

//makeItem () {}
ItemPtr makeItem(char partId[ID_LENGTH], int partQuantity, char partType){

	ItemPtr newPtr = (ItemPtr)malloc(sizeof(Item));
	
	if(newPtr == NULL){
		puts("Memory Issues... Item not created");
	} else {
	    strcpy(newPtr->partId, partId);
		newPtr->partQuantity = partQuantity;
		newPtr->partType = partType;
		newPtr->nextPtr = NULL;
	}
	return newPtr;

}

//addItem () {}
ItemPtr addItem(ItemPtr sPtr, char partId[ID_LENGTH], int partQuantity, char partType){

	ItemPtr previousPtr, currentPtr, newPtr;
	previousPtr = NULL;
	currentPtr = sPtr;
	newPtr = makeItem(partId, partQuantity, partType);
	
	// compares partIDs using strcmp for alphabetical ordering
	while (currentPtr != NULL && strcmp(partId, currentPtr->partId) > 0){
		previousPtr = currentPtr;
		currentPtr = currentPtr->nextPtr;
	}
	
	if(previousPtr == NULL){			//inserting at front
		newPtr->nextPtr = sPtr;
		sPtr = newPtr;
	}else{							//inserting elsewhere
		previousPtr->nextPtr = newPtr;
		newPtr->nextPtr = currentPtr;
	}
	return sPtr;
}

//printList () {}
void printList(ItemPtr sPtr){
	
	ItemPtr currentPtr = sPtr;
	
	if(currentPtr == NULL){
		puts("List is empty.. nothing to print");
	}
	else
	{
		puts("The Auto Parts in the list are: ");
		while (currentPtr != NULL){
			printf("Part ID: %s\t Quantity: %d\tType: %c\n", currentPtr->partId, currentPtr->partQuantity, currentPtr->partType);
			currentPtr = currentPtr->nextPtr;
		}	
	}
}

//viewItem (){}   //<-add this code block

void viewItem(ItemPtr sPtr, char searchPartId[ID_LENGTH]){
	
	ItemPtr currentPtr = sPtr;
	int position = 0;
	
	if(currentPtr == NULL){
		puts("List is empty... nothing to view");
		return;
	}
	
	while(currentPtr != NULL && strcmp(searchPartId, currentPtr->partId) != 0){
		currentPtr = currentPtr->nextPtr;
		position++;
	}
	
	if(currentPtr == NULL){
		printf("Part with ID '%s' was not found\n", searchPartId);
	} else {
		printf("Part ID: %s\t Quantity: %d\tType: %c found at position %d\n", currentPtr->partId, currentPtr->partQuantity, currentPtr->partType, position+1);
	}
}

//removeItem (){}

void updateItem(ItemPtr sPtr, char searchPartId[ID_LENGTH])
{
	if (sPtr == NULL) {
		printf("List is empty :\\\n");
		return;
	}

	ItemPtr currPtr = sPtr;
	printf("Searching for partID = %s\n", searchPartId);
	while (currPtr->nextPtr != NULL && strcmp(currPtr->partId, searchPartId) != 0) {
		currPtr = currPtr->nextPtr;
	}

	if (strcmp(currPtr->partId, searchPartId) == 0) {
		printf("Part ID found! :D\n");
		char newId[ID_LENGTH];
		int newQuantity;
		char newType;		

		printf("\nEnter updated partId: ");
        scanf("%10s", newId);
        printf("\nEnter updated partQuantity: ");
        scanf("%d", &newQuantity);
        printf("\nEnter updated partType (single character, 'E' for Engine, 'B' for Brake): ");
        scanf(" %c", &newType);

		ItemPtr updatedItem = makeItem(newId, newQuantity, newType);
		
	} else {
		printf("Part ID %s not found :(\n", searchPartId);
	}

}

void displayMenuOptions () 
{
	printf ("1: Insert Auto Part into Ordered List\n");
	printf ("2: Remove Auto Part from List\n");
	printf ("3: Update Auto Part from List\n");
	printf ("4: View Auto Part from List\n");
	printf ("5: Printing the List\n");
	printf ("6: Exit\n");
	printf ("Enter Choice: ");
} 
 
