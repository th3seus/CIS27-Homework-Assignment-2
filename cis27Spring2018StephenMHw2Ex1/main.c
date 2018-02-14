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
    int* intPtr;
    struct DigitInfoNodeStephenM* next;
};

typedef struct DigitInfoNodeStephenM DINT;
typedef struct DigitInfoNodeStephenM* DINPtrT;
typedef struct DigitInfoNodeStephenM* DINAddrT;

// function prototypes
DINPtrT extractDigitInfoStephenM(int*, int);
DINPtrT createNewNode(int, int, int, int*, DINPtrT);
void prependNode(DINAddrT, DINPtrT*);
void appendNode(DINAddrT, DINPtrT);
void runMenuHw2(void);
void displayClassInfo(void);
void displayMenuOptions(void);


int main(int argc, const char * argv[]) {
    
    return 0;
}
