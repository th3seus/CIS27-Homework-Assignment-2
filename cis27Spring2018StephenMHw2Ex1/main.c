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
void extractDigitInfoStephenM(int, DINPtrT*); // for testing logic
//DINPtrT createNewNode(int, int, int, int*, DINPtrT);
DINPtrT createNewNode(int, int, int, int*);
void prependNode(DINAddrT myList, DINPtrT*); // adds node to the beginning of list
void appendNode(DINAddrT, DINPtrT*); // adds node to end of list
void printList(DINPtrT list);
void runMenuHw2(void);
void displayClassInfo(void);
void displayMenuOptions(void);



int main(int argc, const char * argv[]) {
    DINPtrT head = NULL;
    int testInt = 154288859;
    int* iPtr = (int*)malloc(sizeof(int));
    
    *iPtr = 1;
    
    head = createNewNode(1, 1, 1, iPtr);
    
    extractDigitInfoStephenM(testInt, &head);
    
    printList(head);
    
    
    
    free(iPtr);
    iPtr = NULL;
    return 0;
}

void extractDigitInfoStephenM(int num, DINPtrT* list) {
    int countAry[10] = {0};
    int* testPtr = &num;
    int temp = 0;
    int count = 0;
    int size = 1;
    int i = 0;
    
    temp = (num < 0) ? -num : num;
    
    do {
        countAry[temp % 10]++;
        
        temp /= 10;
    } while(temp != 0);
    
    for (i = 0; i < 10; i++) {
        if (countAry[i] > 0)
            count++;
    }
    
    for (i = 0; i < count; i++) {
        if(countAry[i] > 0)
            appendNode(createNewNode(i, countAry[i], size, testPtr), list);
    }
}

// functions for working with nodes

DINPtrT createNewNode(int digit, int count, int size, int* iPtr) {
    DINPtrT tempNodePtr = (DINPtrT)malloc(sizeof(DINT));
    
    tempNodePtr->digit = digit;
    tempNodePtr->count = count;
    tempNodePtr->size = size;
    tempNodePtr->iPtr = iPtr;
    
    return tempNodePtr;
    
}

void appendNode(DINAddrT nodeAddr, DINPtrT* listAddr) {
    DINAddrT tempPtr = NULL;
    
    if (*listAddr != NULL) {
        tempPtr = *listAddr;
        while (tempPtr->next) { // checks if current node in list is last node
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
    
    while (list != NULL) {
        printf("\n digit %d, count %d, size %d", list->digit, list->count, list->size);
        tempPtr = list->iPtr;
        for(int i = 0; i < list->size; i++) {
            printf("\n   integers are %d", *(tempPtr + i));
        }

        list = list->next;
    }
}
