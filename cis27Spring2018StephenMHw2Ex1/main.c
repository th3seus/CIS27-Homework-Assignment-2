/**
 * Program Name: CIS27Spring2018StephenMHw2Ex1.c
 * Discussion:   Homework Assignment #2
 * Written By:   Stephen Miller
 * Due Date:     2018/02/23
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
//DINPtrT extractDigitInfoStephenM(int*, int);
void extractDigitInfoStephenM(int*, int, DINPtrT*); // for testing logic
//DINPtrT createNewNode(int, int, int, int*, DINPtrT);
DINPtrT createNewNode(int, int, int, int*);
void prependNode(DINAddrT myList, DINPtrT*); // adds node to the beginning of list
void appendNode(DINAddrT, DINPtrT*); // adds node to end of list
void printList(DINPtrT list);
void sortArray(int*, int);
int removeDuplicates(int*, int);
int* countDigits(int*, int);
void runMenuHw2(void);
void displayClassInfo(void);
void displayMenuOptions(void);



int main(int argc, const char * argv[]) {
    DINPtrT list = NULL;
    int* array = NULL;
    int origSize = 10;
    int newSize = 0;
    
    array = (int*)malloc(origSize * sizeof(int));
    
    *(array + 0) = 154487;
    *(array + 1) = 56369;
    *(array + 2) = 154487;
    *(array + 3) = 20;
    *(array + 4) = 20;
    *(array + 5) = 37854;
    *(array + 6) = 46565;
    *(array + 7) = 37854;
    *(array + 8) = 154487;
    *(array + 9) = 7;
    
    
    
    return 0;
}

void extractDigitInfoStephenM(int* ary, int size, DINPtrT* list) {
    int* countAry = NULL;
    int* tempPtr = NULL;
    int* tempNodeIPtr = NULL;
    int intCount = 0;
    int noDupSize = 0;
    int temp = 0;
    int nodePos = 0;
    int nodePtrSize = 0;
    int count = 0;
    int i = 0;
    int j = 0;
    
    // safety checks
    if (countAry != NULL)
        free(countAry);
    if (tempPtr != NULL)
        free(tempPtr);
    
    tempPtr = ary; // assign user array to temp variable to not alter original
    
    countAry = countDigits(tempPtr, size); // get digit count of orig array
    
    noDupSize = removeDuplicates(tempPtr, size); // sort and remove duplicates from array
    
    // begin building linked list
    // beginning with even digits
    for (i = 0; i < 10; i += 2) {
        if (*(countAry + i) > 0) {
            // creating nodes without node->size or node->iPtr
            appendNode(createNewNode(i, *(countAry + i), 0, NULL), list);
            count++;
        }
    }
    
    // odd digits
    for (i = 1; i < 10; i += 2) {
        if (*(countAry + i) > 0) {
            // creating nodes without node->size or node->iPtr
            appendNode(createNewNode(i, *(countAry + i), 0, NULL), list);
            count++;
        }
    }

    
    while(list) {
        nodePos = (*list)->digit;
        nodePtrSize = (*list)->size;
        tempNodeIPtr = (*list)->iPtr;
        
        
        for (i = 0; i < noDupSize; i++) {
            temp = (*(tempPtr + i) < 0) ? -*(tempPtr + i) : *(tempPtr + i);
            do {
                if (temp % 10 == nodePos) {
                    nodePtrSize++;
                    temp = 0;
                } else {
                    temp /= 10;
                }
            } while (temp != 0);
        }
        
        tempNodeIPtr = (int*)malloc(nodePtrSize * sizeof(int));
        
        for (i = 0; i < nodePtrSize; i++) {
            for (j = 0; j < noDupSize; j++) {
                temp = (*(tempPtr + j) < 0) ? -*(tempPtr + j) : *(tempPtr + j);
                do {
                    if (temp % 10 == nodePos) {
                        *(tempNodeIPtr + i) = temp;
                        temp = 0;
                        j = noDupSize;
                    } else {
                        temp /= 10;
                    }
                } while (temp != 0);
            }
        }
        
        list = (*list)->next;
    }
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
    int countAry[10] = {0};
    int temp = 0;
    int i = 0;
    
    
    for (i = 0; i < size; i++) {
        temp = (*(ary + i) < 0) ? -*(ary + i) : *(ary + i);
        do {
            countAry[temp % 10]++;
            temp /= 10;
        } while (temp != 0);
    }
    
    return countAry;
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

void appendNode(DINAddrT nodeAddr, DINPtrT* listAddr) {
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
    
    tempPtr->next = nodeAddr; // once while-statement is execute,
                            // tempPtr->next will be equal to NULL,
                            // and nodeAddr will be appended to list
}

void printList(DINPtrT list) {
    int* tempPtr = NULL;
    
    while (list) {
        printf("\n digit %d, count %d, size %d", list->digit, list->count, list->size);
        tempPtr = list->iPtr;
        for(int i = 0; i < list->size; i++) {
            printf("\n   integers are %d", *(tempPtr + i));
        }
        
        list = list->next;
    }
}
