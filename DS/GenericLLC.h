//
// Created by Semih on 10.09.2022.
//

#ifndef CLION_GENERICLLC_H
#define CLION_GENERICLLC_H
#include <stdio.h>
#include <stdlib.h>

class GenericLinkedList
        {
public:
    struct Node{
        void* data;
        struct Node* next;
    };
    void Push(struct Node**  head_ref, void* new_data, size_t data_size){

        struct Node*  nNode = (struct Node*) malloc(sizeof (struct Node));
        nNode->data = malloc(data_size);
        nNode->next = (*head_ref);
        int i = 0;
        for (i = 0; i < data_size; i++)
          *((char *)nNode->data+i ) = *((char *)new_data + i);
        (*head_ref) = nNode;
    }

    static void printList(struct Node* node, void(*fprt)(void *)){
        while(node)
        {
            (*fprt)(node->data);
            node= node->next;
        }
    }

    static void printInt(void *n){
        printf("%d \t", *(int *)n);
    }

    static void printFloat(void *f){
        printf("%f \t", *(float *)f);
    }


    void Run()
    {
        struct Node *start = NULL;

        // Create and print an int linked list
        unsigned int_size = sizeof(int);
        int arr[] = {10, 20, 30, 40, 50}, i;
        for (i=4; i>=0; i--)
            Push(&start, &arr[i], int_size);
        printf("Created integer linked list is \n");
        printList(start, GenericLinkedList::printInt);


        unsigned float_size = sizeof(float);
        start = NULL;
        float arr2[] = {10.1, 20.2, 30.3, 40.4, 50.5};
        for (i=4; i>=0; i--)
            Push(&start, &arr2[i], float_size);
        printf("\n\nCreated float linked list is \n");
        printList(start, GenericLinkedList::printFloat);

    }
};




#endif //CLION_GENERICLLC_H
