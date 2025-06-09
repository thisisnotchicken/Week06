//#include "" with double quotes is a custome header file
#include "link-list-autoparts.h"		//Activity 1: include the link-list header file
 
int main () 
{
  ItemPtr startPtr;		//Activity 2: creating list pointer
  startPtr = NULL;		//Activity 3: initialising the start of the list
  
  char partId[11];
  int partQuantity;   
  char partType;
      
     
  int choice;
  
  menu ();
  scanf ("%d", &choice);
  while (choice != 5)
  {
    switch (choice) //Activity 4: Test your link list operations
    {
      case 1:
        printf ("\nEnter Value for Part ID for Insertion: ");
        scanf ("%10s", partId);
        printf ("\nEnter Value for Part Quantity for Insertion: ");
        scanf ("%d", &partQuantity);
        printf ("\nEnter Value for Part Type for Insertion (single character, 'E' for Engine, 'B' for Brake): ");
        scanf (" %c", &partType); 
			  startPtr = addItem (startPtr, partId, partQuantity, partType);
			  printList (startPtr);
			  printf ("\n");
	      break;
      case 2: //printf ("\nEnter Item for deletion : ");
	      //scanf ("%d", &value);
	      //startPtr = removeItem (startPtr, value);
	      //printList (startPtr);
	      //printf ("\n");
        break;
      case 3: printf ("\nEnter Part ID to View : ");
	      scanf ("%10s", partId);
	      viewItem (startPtr, partId);
	      printf ("\n");
	      break;
      case 4: printList (startPtr);
	      printf ("\n");
	      break;
      default:
	      printf ("Invalid Option... Please Try Again \n");
	      break;
    }
      
    menu ();
    scanf ("%d", &choice);
  }
  
}// end of main