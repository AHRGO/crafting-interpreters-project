/*
Do the same thing for C:
    Get a “Hello, world!” program written and running in Java.
    Set up whatever makefiles or IDE projects you need to get it working.
    If you have a debugger, get comfortable with it and step through your program as it runs.

To get some practice with pointers, define a doubly linked list of heap-allocated strings. 
Write functions to insert, find, and delete items from it. 
Test them.
*/


/**
 * 
 * validating if the code has memory leaks:
 * 1. using the valgrind tool:
 * -    valgrind --leak-check=full ./program
 * 
 * 2. using address sanitizer
 * -    gcc -fsanitize=address -g program.c -o program
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
Node *insert_node(Node *list_node, Node *node_to_insert);
Node *find_last_node(Node *node);
void delete_node(Node **head, Node *node);

void create_and_insert_node(Node *node_in_the_list ,const char *text);

void free_node(Node *node);
void cleanup_mem(Node *first);
void node_freedom_cry(Node *node);

void test_nodes();
void test_nodes_secnd_ed();


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

Node *insert_node(Node *list_node, Node *node_to_insert) {
    if (node_to_insert == NULL) {
        return NULL;
    }

    Node *tail_node = find_last_node(list_node);

    // tail_node->next = malloc(sizeof(Node));
    tail_node->next = node_to_insert;

    return tail_node->next;
}

Node *find_last_node(Node *node) {
    //stop condition
    if (node->next == NULL) {
        return node;
    }

    find_last_node(node->next);
}

void create_and_insert_node(Node *node_in_the_list ,const char *text) {
    Node *node_to_be_inserted = create_node(text);
    insert_node(node_in_the_list, node_to_be_inserted);
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

    printf("\n\n finding the last node ... \n\n");

    Node *tail_node = find_last_node(first);
    printf("\nTail node's message is:: %s\n", tail_node->text);

    cleanup_mem(first);
}

void test_nodes_secnd_ed() {
    Node *first = create_node("Hello");
    create_and_insert_node(first, "Marvelous");
    create_and_insert_node(first, "World");
    create_and_insert_node(first, "!");
    create_and_insert_node(first, "Yeahhaw");

    // Node *current_node = malloc(sizeof(Node));
    Node *current_node = first;
    while (current_node->next != NULL) {
        printf("%s ", current_node->text);
        current_node = current_node->next;
    }

    printf("\n");

    // cleanup_mem(first);
    free_all_the_nodes(first);
    // node_freedom_cry(first);
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

void node_freedom_cry(Node *node) {
    Node *tail_node = find_last_node(node);
    Node *updated_tail_node;// = tail_node->prev;        
    while(tail_node->prev != NULL) {
        updated_tail_node = tail_node->prev;
        free(tail_node);
    }
}

void free_node(Node *node) {
    free(node->text);
    free(node);
}






int main() {
    // printf("Hello World!\n");

    // test_nodes();
    test_nodes_secnd_ed();

    return 0;
}