// Header file containing link-list definitions & implementation methods
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ID_LENGTH 11
#define TEMP_BUFFER_SIZE 256

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


/*Function Prototypes*/
ItemPtr makeItem(char partId[ID_LENGTH], int partQuantity, char partType);				//makeItem ();
ItemPtr addItem(ItemPtr sPtr, char partId[ID_LENGTH], int partQuantity, char partType);	//addItem ();
ItemPtr removeItem (ItemPtr sPtr, char partId[ID_LENGTH]);
void updateItem (ItemPtr sPtr, char partId[ID_LENGTH], int partQuantity, char partType);
void printList(ItemPtr sPtr);				//printList ();
void viewItem (ItemPtr sPtr, char partId[ID_LENGTH]);

char getValidPartType();
void getValidPartId(ItemPtr sPtr, char partId_buffer[ID_LENGTH]);
int getIntegerInput(const char *prompt);

void menu ();
int isEmpty(ItemPtr sPtr);
int isPartIdUnique(ItemPtr sPtr, char partId[ID_LENGTH]);

 
/*******Function Definitions******/

void clearBuffer(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int isEmpty(ItemPtr sPtr){
	return (sPtr == NULL);
}

//read int for part quantity
int getIntegerInput(const char *prompt){
	char inputBuffer[TEMP_BUFFER_SIZE];
	char *endPtr;
	long value;
	
	printf("%s", prompt);
	
	if(fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL){
		printf("Error reading input. Exiting.\n");
		exit(EXIT_FAILURE);
	}
	
	inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
	
	value = strtol(inputBuffer, &endPtr, 10);
	
	if ( endPtr == inputBuffer || *endPtr != '\0' || value > INT_MAX || value < INT_MIN){
		printf("Invalid input or value out of integer range. Assuming 0.\n");
		return 0;
	}
	
	return (int)value;
}

//validate part type input
char getValidPartType(){
	char partType;
	do{
		printf("\nEnter Part Type (single character, 'E' for Engine, 'B' for Brake): ");
		scanf(" %c", &partType);
		partType = toupper(partType); //convert to uppercase for case sensitivity
		
		if (partType != 'E' && partType != 'B'){
			printf("Invalid Part Type.\n");
		}
	} while (partType != 'E' && partType != 'B');
	return partType;
}

//validate part id input
void getValidPartId(ItemPtr sPtr, char partId_buffer[ID_LENGTH]){
	char tempIdInput[TEMP_BUFFER_SIZE];
	int isValidId = 0;
	
	do{
		printf("\nEnter Value for Part ID (max %d characters): ", ID_LENGTH - 1);
		
		if (fgets(tempIdInput, sizeof(tempIdInput), stdin) == NULL){
			printf("Error reading input. Exiting.\n");
			exit(EXIT_FAILURE);
		}
		
		tempIdInput[strcspn(tempIdInput, "\n")] = '\0';
		
		if(strlen(tempIdInput) > (ID_LENGTH - 1)) {
			printf("Part ID '%s' is too long. Please enter an ID with at most %d characters.\n", tempIdInput, ID_LENGTH - 1);
			isValidId = 0; //not unique = invalid
		} else if (!isPartIdUnique(sPtr, tempIdInput)){
			printf("The part with ID: '%s' already exists. Cannot add duplicates.\n", tempIdInput);
			isValidId = 0;
		} else {
			isValidId = 1;
		}
	} while (!isValidId);
	
	strcpy(partId_buffer, tempIdInput);
}


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

//isPartIdUnique() {}
int isPartIdUnique(ItemPtr sPtr, char partId[ID_LENGTH]){
	ItemPtr currentPtr = sPtr;
	while (currentPtr != NULL){
		if (strcmp(partId, currentPtr->partId) == 0){
			return 0; // Not unique (duplicate)
		}
		currentPtr = currentPtr->nextPtr;
	}
	return 1; //Unique
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

//removeItem (){}
ItemPtr removeItem (ItemPtr sPtr, char partId[ID_LENGTH]){
	ItemPtr previousPtr, currentPtr, tempPtr;
	previousPtr = NULL;
	currentPtr = sPtr;
	tempPtr = NULL;
	
	if(currentPtr == NULL){
		puts("List is empty.. nothing to remove\n");
		return sPtr;	
	}
	
while(currentPtr != NULL && strcmp(partId, currentPtr->partId) != 0){
		previousPtr = currentPtr;
		currentPtr = currentPtr->nextPtr;
	}
	if(currentPtr == NULL){
		printf("Part with ID '%s' was not found\n", partId);
		
	} else if (previousPtr == NULL){
		tempPtr = sPtr;
		printf("Item with details [ID: %s \tQuantity: %d \tType: %c] is being removed\n", tempPtr->partId, tempPtr->partQuantity, tempPtr->partType);
		sPtr = sPtr->nextPtr;
		free(tempPtr);
	} else {
		tempPtr = currentPtr;
		printf("Item with details [ID: %s \tQuantity: %d \tType: %c] is being removed\n", tempPtr->partId, tempPtr->partQuantity, tempPtr->partType);
		previousPtr->nextPtr = currentPtr->nextPtr;
		free(tempPtr);
	}
	return sPtr;
	//node not found
	
	//node found at the front of list
	//node found elsewhere in the list
}
	
void updateItem (ItemPtr sPtr, char partId[ID_LENGTH], int partQuantity, char partType){
	
	ItemPtr currentPtr = sPtr;
	
	if(currentPtr == NULL){
		puts("List is empty.. nothing to update");
		return;
	}
	
	while(currentPtr != NULL && strcmp(partId, currentPtr->partId) !=0){
		currentPtr = currentPtr->nextPtr;
	}
	
	if (currentPtr == NULL){		// Item not found
		printf("Part with ID#%s was not found\n", partId);
		
	} else {
		puts("\n\tOld values");
		printf("\tID: %s\tQuantity: %d\tType: %c", currentPtr->partId, currentPtr->partQuantity, currentPtr->partType);
		printf("\n");
	
		currentPtr->partQuantity = partQuantity;
		currentPtr->partType = partType; // changed for char 
      	
      	puts("\tNew values");
      	printf("\tID: %s\tQuantity: %d\tType: %c", currentPtr->partId, currentPtr->partQuantity, currentPtr->partType);
      	printf("\n");
	}
}


//printList () {}
void printList(ItemPtr sPtr){
	
	ItemPtr currentPtr = sPtr;
	
	if(currentPtr == NULL){
		puts("List is empty.. nothing to print");
	}
	else
	{
		puts("\n\tThe Auto Parts in the list are: ");
		while (currentPtr != NULL){
			printf("\tPart ID: %s\tQuantity: %d\tType: %c\n", currentPtr->partId, currentPtr->partQuantity, currentPtr->partType);
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
		printf("\n\tPart ID: %s\tQuantity: %d\tType: %c \n\tFound at position: #%d\n", currentPtr->partId, currentPtr->partQuantity, currentPtr->partType, position+1);
	}
}


void menu () 
{
	printf ("\t1: Insert Auto Part into Ordered List\n");
	printf ("\t2: Remove Auto Part from List\n");
	printf ("\t3: Update Auto Part in List\n");
	printf ("\t4: View an Auto Part\n");
	printf ("\t5: Print List of Auto Parts\n");
	printf ("\t6: Exit\n");
	printf ("\tEnter Choice: ");
} 
 
