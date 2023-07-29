#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

//a list that stores abstraction classes
typedef struct List{
    char* abstract_class_name;
    struct List* next;
    bool is_first_element;
    int counter;
}List;

//The structure that stores a set of seq_t strings
struct seq{
    struct seq* first;
    struct seq* second;
    struct seq* third;
    List* abstract_class_list;
    bool is_first_element;
};

typedef struct seq seq_t;

//tries to create first element of the list
//in case of error handle it
List* try_to_create_list_mock();

//initlialize default values for first list element
void set_list_mock(List* list_mock);

//initialize default values
void set_list_node(List* list);

//tries to creat structure for holding
//set of strings
seq_t* try_to_create_seq_mock();

//initializes default values of structure
//which holds set of strings
void set_seq_mock(seq_t* seq_mock, List* l_mock);
bool compare_names(char const str1[], char const str2[]);
//tries to create new node
//for stroing new string in a set
List* try_to_create_list();

//initilaize default values for node which
//stores string
void set_new_node(seq_t* ptr, List* list);

void free_list(List* list);

//frees up all memory occupied by
//set of strings
void free_seq(seq_t *ptr);

//finds node which is the last one already in a set
seq_t* find_last_represented_node(seq_t* ptr, const char* str, char* next_char);

//check parameters for seq_equiv function
bool are_equiv_parameters_ok(seq_t* ptr, char const* str1, char const* str2);

//finds last node which is represented in current set
//and adds missing nodes in order to the whole str string can be represented
void find_maximum_prefix_and_add(seq_t* ptr, const char* str, int* allocated);

//finds last node of str which is represented in current set
void add_prefix_missing_nodes(const char* str, int index, seq_t* ptr);

//tries new node of structure which
//holds strings
seq_t* try_to_create_seq_node();

//inserts new element of the list after head node
void insertAfter(List* head, List* new_el);

//checks whether a string is represented in a set
int is_seq_in_set(seq_t *ptr, char const *str);

//finds node which represents str string in set
seq_t* find_seq_node(seq_t *ptr, char const *str);

void remove_List_node(List **head, List *to_remove);

//deletes all elements below given node including this node
void delete_trie(seq_t *ptr, List* head);

//changes name of abstraction class
void change_name(List* list, char const *s, bool *error);

int my_strlen(char const *str);

void my_strcpy(char dest[], const char source[]);

bool is_abstract_class_name_empty(List* list);

//check whether will set of abstract clasess change
bool will_abstract_class_change(seq_t *ptr, const char* str1, const char* str2);

// int compare_names(char str1[], char str2[]);

//creates new abstract class and figures out it's name based on given strings
List* create_new_abstract_class(List** head, char const *str1, char const *str2);

void add_at_the_end(List** head, List* new_list);

//figures new abstract class name based on passed trings
char* new_class_name(char const *str1, char const *str2);

//concatenates two given names
char* merge_names(char const *str1, char const *str2);

//set all nodes which point at source1, source 2
//to point at new (dest) abstraction class node
void change_abstract_classes(seq_t* p, List* source1, List* source2, List* dest, List** head);

//checks whether the pointer points at seq_t structure
bool is_seq_t_ptr(seq_t* ptr);

//checks whether pointer points at the first node
//of set which represents strings collaction
bool is_seq_t_mock_ptr(seq_t* ptr);

//checks if pointer points at good type and if string is not empty
//and represents string in a proper way
bool are_seq_parameters_ok(seq_t *p, char const *s);

bool is_name_rep_proper(const char* name);

bool is_not_empty(const char* str);

//checks if string includes only proper digits
bool is_representing_seq_t(const char* str);

//checks if string is represened properly due to task rules
bool is_seq_t_rep_proper(const char* str);

void set_errno_to_ENOMEM();

void set_errno_to_EINVAL();

//checks parameters for seq_set_name function
bool are_set_name_parameters_ok(seq_t *ptr, char const *str, char const *name);

void set_errno_to_zero();

//returns one node before one representd by a given string
seq_t* find_prev_node(seq_t *ptr, char const *str);

#endif