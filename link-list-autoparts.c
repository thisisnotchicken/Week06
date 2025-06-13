// Authors: Nicholas D, Vedagya V, Max D
// Assignment #2 - Group #1 Auto Parts Shop

// Nicholas D was in charge of implementing Unique Part ID
// Vedagya V was in charge of implementing Remove
// Max D was in charge of implementing Update
// We all collectively worked on Insert, View, Print List
// We all attempted to swap the scanfs to fgets, getchar, strto


//#include "" with double quotes is a custom header file
#include "link-list-autoparts.h"		//Activity 1: include the link-list header file
 
int main () 
{
  ItemPtr startPtr;		//Activity 2: creating list pointer
  startPtr = NULL;		//Activity 3: initialising the start of the list
  
  char partId[ID_LENGTH];
  int partQuantity;   
  char partType;
      
     
  int choice;
  
  menu ();
  scanf ("%d", &choice);
  clearBuffer();
  
  while (choice != 6)
  {
    switch (choice) //Activity 4: Test your link list operations
    {
       	case 1:getValidPartId(startPtr, partId);	//added functions to retrieve input without using scanf (used fgets, getchar, strto)
            	
			partQuantity = getIntegerInput("\nEnter Value for Part Quantity for Insertion: ");	
			
			partType = getValidPartType();			//also added validations for part id, part type
			
			startPtr = addItem (startPtr, partId, partQuantity, partType);
            printList (startPtr);
            printf ("\n");
           	break; 
       	case 2: printf ("\nEnter Item for deletion : ");
	       scanf ("%10s", partId);
	       
		   startPtr = removeItem (startPtr, partId);
	       printList (startPtr);
	       printf ("\n");
               break;
        case 3: if(!isEmpty(startPtr)){
			printf ("\nEnter Part ID for Update: ");
            scanf ("%10s", partId);      
			printf ("\nEnter Part Quantity to Update: ");
        	scanf ("%d", &partQuantity);
			
			partType = getValidPartType();
				   
			updateItem (startPtr, partId, partQuantity, partType);//printList (startPtr);
			printf ("\n");
			} else{
			puts("list is empty ... nothing to update");
			}
			
			break;
       	case 4: printf ("\nEnter Part ID to View : ");
	       scanf ("%10s", partId);
	       viewItem (startPtr, partId);
	       printf ("\n");
	       break;
       	case 5: printList (startPtr);
	       printf ("\n");
	       break;
       	default:
	       printf ("Invalid Option... Please Try Again \n");
	       break;
    }
      
    menu ();
    
    scanf ("%d", &choice);
  	clearBuffer();
  }
  return 0;
  
}// end of main
