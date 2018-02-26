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
DINAddrT extractDigitInfoStephenM(int*, int/*, DINPtrT* */); // for testing logic
DINPtrT createNewNode(int, int, int, int*);
void appendNode(DINPtrT, DINAddrT*); // adds node to end of list
void printList(DINPtrT);
DINPtrT buildList(int*);
DINPtrT populateList(int, int*, DINPtrT);
void freeList(DINPtrT);
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
    
    
    list = extractDigitInfoStephenM(array, 10);
    
    printf("\n outside function\n");
    printList(list);
    
    freeList(list);
    free(array);
    array = NULL;
    return 0;
}

DINAddrT extractDigitInfoStephenM(int* ary, int size/*, DINPtrT* list */) {
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
    
    // for testing purposes
    for (i = 0; i < 10; i++) {
        printf("\n %d \n", *(countAry + i));
    }
    
    head = buildList(countAry);
    
    printList(head);
    
    head = populateList(noDupSize, tempPtr, head);
    
    printf("\n inside function\n");
    printList(head);
    
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
        for (i = 0; i < list->size; i++) {
            printf("\n node#: %d, node ptr value: (%d)", list->digit, *(list->iPtr + i));
        }
        free(tempNodeIPtr);
        tempNodeIPtr = NULL;
        
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
    
    for (i = 0; i < size; i++) {
        temp = (*(ary + i) < 0) ? -*(ary + i) : *(ary + i);
        do {
            *(countAry + (temp % 10)) += 1;
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
    
    tempPtr->next = nodeAddr; // once while-statement is execute,
                            // tempPtr->next will be equal to NULL,
                            // and nodeAddr will be appended to list
}

void printList(DINPtrT head) {
    int* tempPtr = NULL;
    DINPtrT list = NULL;
    
    list = head;
    
    while (list) {
        printf("\n digit %d, count %d, size %d", list->digit, list->count, list->size);
        tempPtr = list->iPtr;
        for(int i = 0; i < list->size; i++) {
            printf("\n   integers are %d", *(tempPtr + i));
        }
        
        list = list->next;
    }
}

void freeList(DINPtrT list) {
    DINPtrT temp = NULL;
    
    if (list == NULL) {
        return;
    } else {
        while (list != NULL) {
            temp = list;
            list = list->next;
            //free(temp->iPtr);
            free(temp);
            temp = NULL;
        }
    }
}
