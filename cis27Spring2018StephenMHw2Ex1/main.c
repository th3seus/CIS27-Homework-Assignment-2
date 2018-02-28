/**
 * Program Name: CIS27Spring2018StephenMHw2Ex1.c
 * Discussion:   Homework Assignment #2
 * Written By:   Stephen Miller
 * Due Date:     2018/03/01
 */
#include <stdio.h>
#include <stdlib.h>

// Type Definitions
struct DigitInfoNodeStephenM{
    /* node to build a linked list in order to count the
     occurrence of digits in an array of integers supplied
     by the user */
    int digit;
    int count;
    int size;
    int* iPtr;
    struct DigitInfoNodeStephenM* next;
};

typedef struct DigitInfoNodeStephenM DINT;
typedef struct DigitInfoNodeStephenM* DINPtrT;
typedef struct DigitInfoNodeStephenM* DINAddrT;

// function prototypes
DINAddrT extractDigitInfoStephenM(int*, int);
int* countDigits(int*, int);
void sortArray(int*, int);
int removeDuplicates(int*, int);
DINPtrT buildList(int*);
DINPtrT populateList(int, int*, DINPtrT);
void printList(DINPtrT);

DINPtrT createNewNode(int, int, int, int*);
void appendNode(DINPtrT, DINAddrT*); // adds node to end of list
void freeList(DINPtrT*);

void runMenuHw2(void);
void displayClassInfo(void);
void displayMenuOptions(void);



int main(int argc, const char * argv[]) {
    
    displayClassInfo();
    runMenuHw2();
    
    return 0;
}

DINAddrT extractDigitInfoStephenM(int* ary, int size) {
    int* countAry = NULL;
    int* tempPtr = NULL;
    DINPtrT head = NULL;
    int noDupSize = 0;
    int i = 0;

    // safety checks
    if (countAry != NULL)
        free(countAry);
    if (tempPtr != NULL)
        free(tempPtr);
    
    // assign user array to temp variable to not alter original
    tempPtr = (int*)malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
        *(tempPtr + i) = *(ary + i);
    }
    
    countAry = countDigits(tempPtr, size); // get digit count of orig array
    
    noDupSize = removeDuplicates(tempPtr, size); // sort and remove duplicates from array
    
    head = buildList(countAry);
    
    head = populateList(noDupSize, tempPtr, head);
    
    free(countAry);
    countAry = NULL;
    free(tempPtr);
    tempPtr = NULL;
    
    return head;
}

DINPtrT populateList(int size, int* array, DINPtrT head) {
    DINPtrT list = NULL;
    int* tempNodeIPtr = NULL;
    int nodePos = 0;
    int nodePtrSize = 0;
    int temp = 0;
    int i = 0;
    int j = 0;

    list = head;
    
    while(list) {
        /* first section counts number of unique integers containing digit correlating to
            list->digit */
        nodePos = (list)->digit;
        nodePtrSize = 0;
        
        for (i = 0; i < size; i++) {
            temp = (*(array + i) < 0) ? -*(array + i) : *(array + i);
            do {
                if (temp % 10 == nodePos) {
                    nodePtrSize++;
                    temp = 0;
                } else {
                    temp /= 10;
                }
            } while (temp != 0);
        }
        
        /* second section assigns number of unique digits to list->size, allocates a pointer
            to an array of integers using nodePtrSize, and finishes by storing the unique integers
            in the array of integers and assigning that array to list->iPtr */
        (list)->size = nodePtrSize;
        
        tempNodeIPtr = (int*)malloc(nodePtrSize * sizeof(int));
        
        for (i = 0; i < nodePtrSize; i++) {
            for (j = 0; j < size; j++) {
                temp = (*(array + j) < 0) ? -*(array + j) : *(array + j);
                do {
                    if (temp % 10 == nodePos) {
                        *(tempNodeIPtr + i) = *(array + j);
                        temp = 0;
                        i++;
                    } else {
                        temp /= 10;
                    }
                } while (temp != 0);
            }
        }
        
        (list)->iPtr = tempNodeIPtr;
        
        list = (list)->next;
    }
    return head;
}

DINPtrT buildList(int* array) {
    DINPtrT head = NULL;
    int listFlag = 0; // becomes 1 after first node is created
    int i = 0;
    
    head = (DINPtrT)malloc(sizeof(DINT));
    
    // begin building linked list
    // beginning with even digits
    for (i = 0; i < 10; i += 2) {
        if (*(array + i) > 0) {
            // creating nodes without node->size or node->iPtr
            if (listFlag == 0) {
                head = createNewNode(i, *(array + i), 0, NULL);
                listFlag = 1;
            } else {
                appendNode(createNewNode(i, *(array + i), 0, NULL), &head);
            }
        }
    }
    
    // odd digits
    for (i = 1; i < 10; i += 2) {
        if (*(array + i) > 0) {
            // creating nodes without node->size or node->iPtr
            if (listFlag == 0) {
                head = createNewNode(i, *(array + i), 0, NULL);
                listFlag = 1;
            } else {
                appendNode(createNewNode(i, *(array + i), 0, NULL), &head);
            }
        }
    }
    
    return head;
}

void sortArray(int* ary, int size) {
    // bubble sort algorithm to sort array from least to greatest
    int temp = 0;
    int i = 0;
    int j = 0;
    
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (ary[j] > ary[j + 1]) {
                temp = ary[j];
                ary[j] = ary[j + 1];
                ary[j + 1] = temp;
            }
        }
    }
}

int removeDuplicates(int* ary, int size) {
    // removes duplicate values from array after sorting it
    int prev = 0;
    int i = 0;
    
    sortArray(ary, size);
    
    for (i = 0; i < size; ++i) {
        if (ary[i] != ary[prev]) {
            ary[++prev] = ary[i];
        }
    }
    
    return prev + 1;
}

int* countDigits(int* ary, int size) {
    // counts total number of digits from all values in the array
    int* countAry = NULL;
    int temp = 0;
    int i = 0;
    
    countAry = (int*)malloc(10 * sizeof(int));
    
    for (i = 0; i < 10; i++) {
        *(countAry + i) = 0;
    }
    
    for (i = 0; i < size; i++) {
        temp = (*(ary + i) < 0) ? -*(ary + i) : *(ary + i);
        do {
            *(countAry + (temp % 10)) += 1;
            temp /= 10;
        } while (temp != 0);
    }
    
    return countAry;
}

void runMenuHw2() {
    int* userArray = NULL;
    DINPtrT userList = NULL;
    int option = 0;
    int size = 0;
    int i = 0;
    
    do {
        displayMenuOptions();
        printf("\nEnter an integer for option + ENTER: ");
        scanf("%d", &option);
        
        switch(option) {
            case 1: // call function
                printf("\n  How many integers? ");
                scanf("%d", &size);
                
                userArray = (int*)malloc(size * sizeof(int));
                
                for (i = 0; i < size; i++) {
                    printf("\n   Enter integer #%d: ", i + 1);
                    scanf("%d", (userArray + i));
                }
                
                printf("\n  The original array: ");
                for (i = 0; i < size; i++) {
                    printf("\n   %d", *(userArray + i));
                }
                
                printf("\n\nCalling extractDigitInfoStephenM()\n");
                userList = extractDigitInfoStephenM(userArray, size);
                
                printf("\nAfter the function completed and returned the info,"
                       "\n interesting facts are shown below.");
                printList(userList);
                
                freeList(&userList);
                
                break;
            case 2: // quit
                printf("\nQUITTING CAUSE FUN\n");
                break;
            default: // wrong option
                printf("\nWRONG OPTION");
                break;
        }
    } while (option != 2);
}

void displayMenuOptions() {
    printf("\n******************************************"
          "\n*              MENU – HW #2              *"
          "\n* 1. Calling extractDigitInfoStephenM()  *"
          "\n* 2. Quit                                *"
          "\n******************************************");
}

void displayClassInfo() {
    printf("CIS 27 - Data Structures\n"
           "Laney College\n"
           "Stephen Miller\n\n"
           "Assignment Information --\n"
           "  Assignment Number:    Homework 2,\n"
           "                        Coding Assignment -- Exercise #1\n"
           "  Written By:           Stephen Miller\n"
           "  Submitted Date:       2018/03/01\n\n");
}

// functions for working with nodes

DINPtrT createNewNode(int digit, int count, int size, int* iPtr) {
    DINPtrT tempNodePtr = (DINPtrT)malloc(sizeof(DINT));
    
    tempNodePtr->digit = digit;
    tempNodePtr->count = count;
    tempNodePtr->size = size;
    tempNodePtr->iPtr = iPtr;
    tempNodePtr->next = NULL;
    
    return tempNodePtr;
}

void appendNode(DINPtrT nodeAddr, DINAddrT* listAddr) {
    DINAddrT tempPtr = NULL;
    
    if (*listAddr != NULL) {
        tempPtr = *listAddr;
        while (tempPtr->next != NULL) { // checks if current node in list is last node
            tempPtr = tempPtr->next;
        }
    } else {
        *listAddr = nodeAddr;
        return;
    }
    
    tempPtr->next = nodeAddr;
}

void printList(DINPtrT head) {
    int* tempPtr = NULL;
    DINPtrT list = NULL;
    
    list = head;
    
    while (list) {
        printf("\n   Digit %d is seen %d times; and"
               "\n      %d can be found in",
               list->digit, list->count, list->digit);
        tempPtr = list->iPtr;
        for(int i = 0; i < list->size; i++) {
            printf("\n        %d", *(tempPtr + i));
        }
        
        list = list->next;
    }
}

void freeList(DINAddrT* headAddr) {
    DINPtrT temp = NULL;
    DINPtrT next = NULL;

    temp = *headAddr; // de-ref the head node to get to the actual node
    
    while (temp != NULL) {
        next = temp->next;
        free(temp->iPtr); // free iPtr in node
        free(temp);
        temp = next;
    }
    
    *headAddr = NULL; // set head caller to NULL to kill the real list
}
