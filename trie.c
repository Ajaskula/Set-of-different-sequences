#include "trie.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "seq.h"

List *try_to_create_list_mock() {
  List *list_mock = (List *)malloc(sizeof(List));
  if (list_mock == NULL) {
    set_errno_to_ENOMEM();
  } else {
    set_list_mock(list_mock);
  }
  return list_mock;
}

void set_list_mock(List *list_mock) {
  list_mock->abstract_class_name = NULL;
  list_mock->next = NULL;
  list_mock->is_first_element = true;
  list_mock->counter = 1;
}
bool compare_names(char const str1[], char const str2[]) {
  int len1 = my_strlen(str1);
  int len2 = my_strlen(str2);
  if (len1 != len2) {
    return false;
  }
  for (int i = 0; i < len1; i++) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
  ;
}
void set_list_node(List *list) {
  list->abstract_class_name = NULL;
  list->next = NULL;
  list->is_first_element = false;
  list->counter = 1;
}
bool are_equiv_parameters_ok(seq_t *ptr, char const *str1, char const *str2) {
  return is_seq_t_mock_ptr(ptr) && is_seq_t_rep_proper(str1) &&
         is_seq_t_rep_proper(str2);
}

seq_t *try_to_create_seq_mock() {
  seq_t *seq_mock = (seq_t *)malloc(sizeof(seq_t));
  if (seq_mock == NULL) {
    set_errno_to_ENOMEM();
  } else {
    List *l_mock = try_to_create_list_mock();
    if (l_mock == NULL) {
      set_errno_to_ENOMEM();
      free(seq_mock);
      seq_mock = NULL;
    } else {
      set_list_mock(l_mock);
      set_seq_mock(seq_mock, l_mock);
    }
  }
  return seq_mock;
}

void set_seq_mock(seq_t *seq_mock, List *l_mock) {
  seq_mock->first = NULL;
  seq_mock->second = NULL;
  seq_mock->third = NULL;
  seq_mock->abstract_class_list = l_mock;
  seq_mock->is_first_element = true;
}

List *try_to_create_list() {
  List *list = malloc(sizeof(List));
  if (list == NULL) {
    set_errno_to_ENOMEM();
    return list;
  }
  set_list_node(list);
  return list;
}

seq_t *find_last_represented_node(seq_t *ptr, const char *str,
                                  char *next_char) {
  int i = 0;
  int ok = 1;
  for (; str[i] != '\0' && ok; i++) {
    if (str[i] == '0') {
      if (ptr->first == NULL) {
        ok = 0;
        i--;
      } else {
        ptr = ptr->first;
      }
    }
    if (str[i] == '1') {
      if (ptr->second == NULL) {
        ok = 0;
        i--;
      } else {
        ptr = ptr->second;
      }
    }
    if (str[i] == '2') {
      if (ptr->third == NULL) {
        ok = 0;
        i--;
      } else {
        ptr = ptr->third;
      }
    }
  }
  *next_char = str[i];
  return ptr;
}
void set_new_node(seq_t *ptr, List *l) {
  ptr->abstract_class_list = l;
  ptr->first = NULL;
  ptr->second = NULL;
  ptr->third = NULL;
  ptr->is_first_element = false;
}

void free_list(List *head) {
  if (head == NULL) {
    return;
  }
  free_list(head->next);
  if (head->abstract_class_name != NULL) {
    free(head->abstract_class_name);
  }
  free(head);
}

void free_seq(seq_t *ptr) {
  if (ptr != NULL) {
    free_seq(ptr->first);
    free_seq(ptr->second);
    free_seq(ptr->third);
    free(ptr);
  }
}

void find_maximum_prefix_and_add(seq_t *ptr, const char *str, int *allocated) {
  int i = 0;
  int ok = 1;
  for (; str[i] != '\0' && ok; i++) {
    if (str[i] == '0') {
      if (ptr->first == NULL) {
        ok = 0;
        i--;
      } else {
        ptr = ptr->first;
      }
    }
    if (str[i] == '1') {
      if (ptr->second == NULL) {
        ok = 0;
        i--;
      } else {
        ptr = ptr->second;
      }
    }
    if (str[i] == '2') {
      if (ptr->third == NULL) {
        ok = 0;
        i--;
      } else {
        ptr = ptr->third;
      }
    }
  }
  // if the whole string is not yet in a set
  if (str[i] != '\0') {
    *allocated = 1;
    add_prefix_missing_nodes(str, i, ptr);
  }
}

void add_prefix_missing_nodes(const char *str, int index, seq_t *ptr) {
  for (int i = index; str[i] != '\0'; i++) {
    if (str[i] == '0') {
      seq_t *new_node = try_to_create_seq_node();
      if (new_node == NULL) {
        return;
      }
      ptr->first = new_node;
      insertAfter(ptr->abstract_class_list, new_node->abstract_class_list);
      ptr = new_node;
    }
    if (str[i] == '1') {
      seq_t *new_node = try_to_create_seq_node();
      if (new_node == NULL) {
        return;
      }
      ptr->second = new_node;
      insertAfter(ptr->abstract_class_list, new_node->abstract_class_list);
      ptr = new_node;
    }
    if (str[i] == '2') {
      seq_t *new_node = try_to_create_seq_node();
      if (new_node == NULL) {
        return;
      }
      ptr->third = new_node;
      insertAfter(ptr->abstract_class_list, new_node->abstract_class_list);
      ptr = new_node;
    }
  }
}

seq_t *try_to_create_seq_node() {
  seq_t *seq = (seq_t *)malloc(sizeof(seq_t));
  if (seq == NULL) {
    set_errno_to_ENOMEM();
  } else {
    List *list = try_to_create_list();
    if (list == NULL) {
      set_errno_to_ENOMEM();
      free(seq);
      seq = NULL;
    } else {
      set_list_node(list);
      set_new_node(seq, list);
    }
  }
  return seq;
}

void insertAfter(List *head, List *new_node) {
  if (head == NULL) {
    return;
  }
  new_node->next = head->next;
  head->next = new_node;
}

int is_seq_in_set(seq_t *ptr, char const *str) {
  int i = 0;
  int ok = 1;

  for (; str[i] != '\0' && ok; i++) {
    if (str[i] == '0') {
      if (ptr->first == NULL) {
        ok = 0;
      } else {
        ptr = ptr->first;
      }
    }
    if (str[i] == '1') {
      if (ptr->second == NULL) {
        ok = 0;
      } else {
        ptr = ptr->second;
      }
    }
    if (str[i] == '2') {
      if (ptr->third == NULL) {
        ok = 0;
      } else {
        ptr = ptr->third;
      }
    }
  }
  if (ok == 0) {
    i--;
  }

  return (str[i] == '\0');
}

seq_t *find_seq_node(seq_t *ptr, char const *str) {
  int i = 0;
  for (; str[i] != '\0'; i++) {
    if (str[i] == '0') {
      ptr = ptr->first;
    }
    if (str[i] == '1') {
      ptr = ptr->second;
    }
    if (str[i] == '2') {
      ptr = ptr->third;
    }
  }
  return ptr;
}

seq_t *find_prev_node(seq_t *ptr, char const *str) {
  int i = 0;
  seq_t *prev = NULL;
  for (; str[i] != '\0'; i++) {
    prev = ptr;
    if (str[i] == '0') {
      ptr = ptr->first;
    }
    if (str[i] == '1') {
      ptr = ptr->second;
    }
    if (str[i] == '2') {
      ptr = ptr->third;
    }
  }
  return prev;
}

void remove_List_node(List **head, List *to_remove) {
  List *prev = NULL;
  List *current = *head;

  while (current != NULL) {
    if (current == to_remove) {
      if (prev != NULL) {
        prev->next = current->next;
      } else {
        *head = current->next;
      }
      if (current->abstract_class_name != NULL) {
        free(current->abstract_class_name);
      }
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
}

void delete_trie(seq_t *ptr, List *head) {
  if (ptr == NULL || ptr->is_first_element == true) {
    return;
  }
  // checks if a node is the only one belonging to this abstraction class
  if (ptr->abstract_class_list->counter > 1) {
    ptr->abstract_class_list->counter--;
  } else {
    remove_List_node(&head, ptr->abstract_class_list);
  }
  delete_trie(ptr->first, head);
  delete_trie(ptr->second, head);
  delete_trie(ptr->third, head);
  free(ptr);
}

void change_name(List *list, char const *s, bool *error) {
  char *name = (char *)malloc((my_strlen(s) + 1) * sizeof(char));

  if (name == NULL) {
    set_errno_to_ENOMEM();
    *error = true;
    return;
  }
  my_strcpy(name, s);
  // frees previous name
  if (list->abstract_class_name != NULL) {
    free(list->abstract_class_name);
  }
  list->abstract_class_name = name;
}

int my_strlen(const char *str) {
  if (str == NULL) {
    set_errno_to_EINVAL();
    return 0;
  }
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

void my_strcpy(char dest[], const char source[]) {
  int i = 0;
  while (source[i] != '\0') {
    dest[i] = source[i];
    i++;
  }
  dest[i] = '\0';
}

bool is_abstract_class_name_empty(List *list) {
  if (list->abstract_class_name == NULL) {
    return true;
  }
  return false;
}

bool will_abstract_class_change(seq_t *ptr, const char *str1,
                                const char *str2) {
  // check if both are in a set
  if (!(is_seq_in_set(ptr, str1) && is_seq_in_set(ptr, str2))) {
    return false;
  }
  // check if both are already in the same abstraction class
  if (find_seq_node(ptr, str1)->abstract_class_list ==
      find_seq_node(ptr, str2)->abstract_class_list) {
    return false;
  }
  return true;
}

List *create_new_abstract_class(List **head, char const *str1,
                                char const *str2) {
  List *new_list = try_to_create_list();
  if (new_list == NULL) {
    return NULL;
  }
  add_at_the_end(head, new_list);
  // create proper name for a new abstract class
  new_list->abstract_class_name = new_class_name(str1, str2);
  return new_list;
}

void add_at_the_end(List **head, List *new_list) {
  List *last = *head;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = new_list;
  set_list_node(new_list);
}

char *new_class_name(char const *str1, char const *str2) {
  // if both are null
  if (str1 == NULL && str2 == NULL) {
    return NULL;
  }
  // if only first is null
  if (str1 == NULL) {
    int len2 = my_strlen(str2);
    char *new_name = (char *)malloc((len2 + 1) * sizeof(char));
    if (new_name == NULL) {
      set_errno_to_ENOMEM();
      return NULL;
    }
    my_strcpy(new_name, str2);
    return new_name;
  }
  // if only second is null
  if (str2 == NULL) {
    int len1 = my_strlen(str1);
    char *new_name = (char *)malloc((len1 + 1) * sizeof(char));
    if (new_name == NULL) {
      set_errno_to_ENOMEM();
      return NULL;
    }
    my_strcpy(new_name, str1);
    return new_name;
  }
  // if both aren't null
  return merge_names(str1, str2);
}
char *merge_names(char const *str1, char const *str2) {
  int len1 = my_strlen(str1);
  int len2 = my_strlen(str2);
  char *new_name = (char *)malloc((len2 + len1 + 1) * sizeof(char));
  if (new_name == NULL) {
    set_errno_to_ENOMEM();
    return NULL;
  }
  int i = 0, j = 0;
  for (i = 0; str1[i] != '\0'; i++) {
    new_name[i] = str1[i];
  }
  for (j = 0; str2[j] != '\0'; j++) {
    new_name[i + j] = str2[j];
  }
  new_name[i + j] = '\0';
  return new_name;
}

void change_abstract_classes(seq_t *p, List *source1, List *source2, List *dest,
                             List **head) {
  if (p == NULL) {
    return;
  }
  // if string is in source1 or source2 abstraction class
  if (p->abstract_class_list == source1 || p->abstract_class_list == source2) {
    // if it's the only node pointing on it
    if (p->abstract_class_list->counter > 1) {
      p->abstract_class_list->counter--;
    } else {
      remove_List_node(head, p->abstract_class_list);
    }
    p->abstract_class_list = dest;
    dest->counter++;
  }
  change_abstract_classes(p->first, source1, source2, dest, head);
  change_abstract_classes(p->second, source1, source2, dest, head);
  change_abstract_classes(p->third, source1, source2, dest, head);
}

bool is_seq_t_ptr(seq_t *ptr) {
  if (ptr == NULL) {
    return false;
  }
  if (ptr != (seq_t *)ptr) {
    set_errno_to_EINVAL();
    return false;
  }
  return true;
}

bool is_seq_t_mock_ptr(seq_t *ptr) {
  if (is_seq_t_ptr(ptr)) {
    if (ptr->is_first_element == true) {
      return true;
    }
  }
  set_errno_to_EINVAL();
  return false;
}
bool are_seq_parameters_ok(seq_t *ptr, char const *str) {
  return is_seq_t_mock_ptr(ptr) && is_seq_t_rep_proper(str);
}

bool is_not_empty(const char *str) {
  if (my_strlen(str) == 0) {
    return false;
  }
  return true;
}

bool is_representing_seq_t(const char *str) {
  for (int i = 0; i < my_strlen(str); i++) {
    if (!(str[i] == '0' || str[i] == '1' || str[i] == '2')) {
      return false;
    }
  }
  return true;
}

bool is_seq_t_rep_proper(const char *str) {
  if (!(is_not_empty(str) && is_representing_seq_t(str))) {
    set_errno_to_EINVAL();
    return false;
  }
  return true;
}
void set_errno_to_ENOMEM() { errno = ENOMEM; }
bool is_name_rep_proper(const char *name) {
  if (!(is_not_empty(name))) {
    set_errno_to_EINVAL();
    return false;
  }
  return true;
}

void set_errno_to_EINVAL() { errno = EINVAL; }
bool are_set_name_parameters_ok(seq_t *ptr, char const *str, char const *name) {
  return is_seq_t_mock_ptr(ptr) && is_seq_t_rep_proper(str) &&
         is_name_rep_proper(name);
}

void set_errno_to_zero() { errno = 0; }
