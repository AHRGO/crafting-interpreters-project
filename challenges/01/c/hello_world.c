/*
Do the same thing for C:
    Get a “Hello, world!” program written and running in Java.
    Set up whatever makefiles or IDE projects you need to get it working.
    If you have a debugger, get comfortable with it and step through your program as it runs.

To get some practice with pointers, define a doubly linked list of heap-allocated strings. 
Write functions to insert, find, and delete items from it. 
Test them.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *text;

    struct Node *next;
    struct Node *prev;
} Node;


Node *create_node(const char *text);
Node *find_node(Node *head, const char *target);
void delete_node(Node **head, Node *node);

void free_node(Node *node);
void cleanup_mem(Node *first);

void test_nodes();


Node *create_node(const char *text) {
    Node *node = malloc(sizeof(Node)); //aloc memory for node variable

    if (node == NULL) {
        return NULL;
    }

    node->text = malloc(strlen(text) + 1); //alocate memory to fit the string within node-> text

    if (node->text == NULL) {
        free(node); //if memory wasn't alocated successfully, clean the node and ends creation proccess
        return NULL;
    }

    strcpy(node->text, text); //insert value inside node->text

    node->next = NULL;
    node->prev = NULL;

    return node;
}

Node *find_node(Node *head, const char *target) {
    Node *current = head;

    while (current != NULL) {
        if (strcmp(current->text, target) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void test_nodes() {
    Node *first = create_node("Hello");
    Node *second = create_node("World");
    Node *third = create_node("!\n");

    first->next = second;
    
    second->next = third;
    second->prev = first;

    third->prev = second;

    printf("%s ", first->text);
    printf("%s ", first->next->text);
    printf("%s", first->next->next->text);

    cleanup_mem(first);
}


void cleanup_mem(Node *first) {

    //checks if third is in memory before trying to free it
    if (first->next->next == NULL) { 
        return;
    } else {
        free_node(first->next->next); //maybe it will get an error, bc it is not an pointer?
    }

    if (first->next == NULL) {
        return;
    } else {
        free_node(first->next);
    }

    if (first == NULL) {
        return;
    } else {
        free_node(first);
    }
}

//todo: try to create a recursive function to cleanup the memory
void free_all_the_nodes(Node *node) {
    if (node->next == NULL && node->prev == NULL) {
        //stop condition: it's the last single node. Free it and end the function;
        free_node(node);
        return;
    }
    
    if (node->next != NULL) {
        //it's a middle node. Need to go until the last node
        free_all_the_nodes(node->next);
    }

    Node *next_node_to_free = node->prev;

    free_node(node);
    free_all_the_nodes(next_node_to_free);

}

void free_node(Node *node) {
    free(node->text);
    free(node);
}






int main() {
    // printf("Hello World!\n");

    test_nodes();
    // cleanup_mem();

    return 0;
}