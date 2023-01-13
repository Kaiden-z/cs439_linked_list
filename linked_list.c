#include <stdlib.h>
#include <stdio.h>

/**
 * Doubly linked node struct
*/
typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node_t;

node_t* header = NULL; /*Reference to first element of linked list*/ 

/**
 * Insert new node into the list with data sorted in order of least to greatest
 * 
 * @param data - int data to be inserted into lost
 */
void add(int data) {
    // Create new node
    node_t* newNode = (node_t*) malloc(sizeof(node_t));
    newNode->data = data;

    if (header == NULL) { /*Set as header if list is empty*/
        header = newNode;
        header->next = NULL;
        header->prev = NULL;
    } else {              /*Place new node into approiate sorted order*/
        node_t* cur = header;
        while (cur != NULL) {
            // Stop if cur data is larger than new data
            if (cur->data > newNode->data) {
                newNode->next = cur;
                newNode->prev = cur->prev;
                // Keep prev null if cur == header
                if (cur == header) {
                    header = newNode;
                } else {
                    cur->prev->next = newNode;
                }
                cur->prev = newNode;
                return;

            // No larger data found, therefore data is last (largest)
            } else if (cur->next == NULL) {
                newNode->prev = cur;
                cur->next = newNode;
                return;
            }

            cur = cur->next;
        }
    }
    
    return;
}

/**
 * Remove a node from the list
 * 
 * @param   data - desired data to be removed
*/
void removeFromList(int data) {
    node_t* cur = header;
    while (cur != NULL) {
        if (cur->data == data) { /*search list for matching data, remove if found*/
            node_t* prevNode = NULL;
            if (cur->prev != NULL) {
                prevNode = cur->prev;
                cur->prev->next = cur->next;
                cur->prev = NULL;
            } else {
                header = cur->next;
            }
            if (cur->next != NULL) {
                cur->next->prev = prevNode;
                cur->next = NULL;
            }
            free(cur);
            
            return;
        }
        cur = cur->next;
    }
    
    return;
}

/**
 * Clears entire list of all data
*/
void clear() {
    node_t* cur = header;
    while (cur != NULL) {
        node_t* nextNode = cur->next;
        free(cur);
        cur = nextNode;
    }
    header->next = NULL;
    header->prev = NULL;
    header = NULL;

    return;
}

/**
 * Create a linked list with incrementing data from 1 to n
 * 
 * @param   size - desired size of list
 * @pre     size >= 1
 */
void initiateLinkedList(int size) {
    if (size < 1) {
        printf("size must be >= 1");
        return;
    }

    for (int i = 1; i <= size; i++) {
        add(i);
    }

    return;
}


/**
 * Print all elements of the linked list
 */
void printList() {
    printf("[");
    node_t* cur = header;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(", ");
        }
        cur = cur->next;
    }
    printf("]\n");

    return;
}

/**
 * Print out the expected output of the list
 * 
 * @param  expectedList - array of expected elements to be present in the list
 * @param  size - size of the expected output array
*/
void printTestResults(int expectedList[], int size) {
    printf("    Expected list: [");
    for (int i = 0; i < size; i++) {
        printf("%d", expectedList[i]);
        if (i != size - 1) {
            printf(", ");
        }
    }
    printf("]\n"); 
    printf("    Current list: ");
    printList();
    printf("\n");

    return;
}


/*~~~~~~~~~[ TESTS ]~~~~~~~~~*/
void testSingleAddRemove() {
    printf("Test 1: Add/Remove\n");
    add(15);
    int expectedList1[] = {15};
    printTestResults(expectedList1, 1);

    removeFromList(15);
    int expectedList2[] = {};
    printTestResults(expectedList2, 0);

    return;
}

void testSingleInitiateClear() {
    printf("Test 2: Inititate/Clear\n");
    initiateLinkedList(5);
    int expectedList1[] = {1, 2, 3, 4, 5};
    printTestResults(expectedList1, 5);

    clear();
    int expectedList2[] = {};
    printTestResults(expectedList2, 0);

    return;
}

void testAddMiddle() {
    printf("Test 3: Add to middle\n");
    initiateLinkedList(5);
    add(2);
    add(4);

    int expectedList[] = {1, 2, 2, 3, 4, 4, 5};
    printTestResults(expectedList, 7);
    clear();

    return;
}

void testAddToStart() {
    printf("Test 4: Add to start\n");
    initiateLinkedList(5);
    add(0);

    int expectedList[] = {0, 1, 2, 3, 4, 5};
    printTestResults(expectedList, 6);
    clear();

    return;
}

void testAddToEnd() {
    printf("Test 5: Add to end\n");
    initiateLinkedList(5);
    add(6);

    int expectedList[] = {1, 2, 3, 4, 5, 6};
    printTestResults(expectedList, 6);
    clear();

    return;
}

void testRemoveMiddle() {
    printf("Test 6: Remove from middle\n");
    initiateLinkedList(5);
    removeFromList(3);

    int expectedList[] = {1, 2, 4, 5};
    printTestResults(expectedList, 4);
    clear();

    return;
}

void testRemoveStart() {
    printf("Test 7: Remove from start\n");
    initiateLinkedList(5);
    removeFromList(1);

    int expectedList[] = {2, 3, 4, 5};
    printTestResults(expectedList, 4);
    clear();

    return;
}

void testRemoveEnd() {
    printf("Test 8: Remove from end\n");
    initiateLinkedList(5);
    removeFromList(5);

    int expectedList[] = {1, 2, 3, 4};
    printTestResults(expectedList, 4);
    clear();

    return;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * Run all listed tests
*/
void runAllTests() {
    testSingleAddRemove();
    testSingleInitiateClear();
    testAddMiddle();
    testAddToStart();
    testAddToEnd();
    testRemoveMiddle();
    testRemoveStart();
    testRemoveEnd();

    return;
}


/**
 * Start of linked list tests
 */
int main() {
    // run tests
    runAllTests();

    // create default list of ints 1 through 5
    int n = 5;
    initiateLinkedList(n);
    printList();

    return 0;
}
