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
 * 
 */

 //! This code has some memory leaks. Since I'm returning to C, I'm writing this note to future I, so I don't get stuck in the learning proccess
 //todo: Solve memory leaks
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *text;

    struct Node *next;
    struct Node *prev;
} Node;



//create
Node *create_node(const char *text);
void create_and_insert_node(Node *node_in_the_list ,const char *text);
Node *create_node_from_user_input();

//find
Node *find_node(Node *head, const char *target);
Node *find_last_node(Node *node);
Node* find_first_node(Node *node);

//insert
Node *insert_node(Node *list_node, Node *node_to_insert);
Node *insert_node_from_user_input(Node *node_list);

//delete
void delete_node(Node **head, Node *node);

//free
void free_node(Node *node);
void cleanup_mem(Node *first);
void node_freedom_cry(Node *node);
void free_all_the_nodes(Node *node);

//tools
void request_user_input(char *text_buffer, size_t buffer_size) ;
void print_all_nodes();

//test
void test_nodes();
void test_nodes_secnd_ed();
void third_test_nodes();



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

//                                                const here means that the pointer is read only
void create_and_insert_node(Node *node_in_the_list, const char *text) {
    Node *node_to_be_inserted = create_node(text);
    insert_node(node_in_the_list, node_to_be_inserted);
}

Node *create_node_from_user_input() {
    char text_buffer[100];

    request_user_input(text_buffer, sizeof(text_buffer));

    return create_node(text_buffer);
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

Node *find_last_node(Node *node) {
    //stop condition
    if (node->next == NULL) {
        return node;
    }

    find_last_node(node->next);
}

Node* find_first_node(Node *node) {
    if (node->prev == NULL) {
        return node;
    }

    find_first_node(node->prev);
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

Node *insert_node_from_user_input(Node *node_list) {
    // char *text_to_insert = request_user_input();

    // Node *new_node = create_node(text_to_insert);

    Node *new_node = create_node_from_user_input();

    return insert_node(node_list, new_node);
}



//todo: add delete_node()



void free_node(Node *node) {
    free(node->text);
    free(node);
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

void node_freedom_cry(Node *node) {
    Node *tail_node = find_last_node(node);
    Node *updated_tail_node;// = tail_node->prev;        
    while(tail_node->prev != NULL) {
        updated_tail_node = tail_node->prev;
        free(tail_node);
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



void request_user_input(char *text_buffer, size_t buffer_size) {
    printf("Enter node text value: \n");
    fgets(text_buffer, buffer_size, stdin);

    text_buffer[strcspn(text_buffer, "\n")] = '\0';
}

void print_all_nodes(Node *node_list) {
    Node *current_node;
    int node_count = 0;

    //ensures priting starts from the beginning
    if (node_list->prev != NULL) {
        current_node = find_first_node(node_list);
    } else {
        current_node = node_list;
    }

    do {
        node_count++;

        printf("Node %d text value: %s \n", node_count, current_node->text);
        current_node = current_node->next;
    } while (current_node->next != NULL);

    // while (current_node->next != NULL) {
    //     node_count++;

    //     printf("Node %d text value: %s \n", node_count, current_node->text);
    //     current_node = current_node->next;
    // }

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

void third_test_nodes() {
    Node *node_list = create_node_from_user_input();
    Node *updated_node_list = insert_node_from_user_input(node_list);
    
    //! Segmentation fault (core dumped) 
    //! Error at last node printing.
    //todo: debug & fix
    print_all_nodes(updated_node_list);
}




int main() {
    // test_nodes();
    // test_nodes_secnd_ed();
    third_test_nodes();

    return 0;
}