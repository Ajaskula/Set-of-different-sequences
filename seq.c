#include "seq.h"
#include "trie.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

// creates new set for represtenig strings
seq_t *seq_new() { return try_to_create_seq_mock(); }

// removes set representing strings
void seq_delete(seq_t *p) {
  if (is_seq_t_mock_ptr(p)) {
    free_list(p->abstract_class_list);
    free_seq(p);
  }
}
// adds string to a set
int seq_add(seq_t *p, char const *s) {
  if (!are_seq_parameters_ok(p, s)) {
    return -1;
  }
  int allocated = 0;
  char next_char = '5';
  // the last node which is in set befor adding
  seq_t *last_represented = find_last_represented_node(p, s, &next_char);
  find_maximum_prefix_and_add(p, s, &allocated);

  // in case of fail of memory allocation
  if (allocated == -1) {

    if (next_char == '0') {
      delete_trie(last_represented->first, p->abstract_class_list);
      last_represented->first = NULL;
    }
    if (next_char == '1') {
      delete_trie(last_represented->second, p->abstract_class_list);
      last_represented->second = NULL;
    }
    if (next_char == '2') {
      delete_trie(last_represented->third, p->abstract_class_list);
      last_represented->third = NULL;
    }
    allocated = 0;
  }
  return allocated;
}

// removes string from a set
int seq_remove(seq_t *p, char const *s) {
  if (!are_seq_parameters_ok(p, s)) {
    return -1;
  }
  if (!is_seq_in_set(p, s)) {
    return 0;
  }
  // finds maximum prefix node
  List *head = p->abstract_class_list;
  seq_t *prev = find_prev_node(p, s);
  seq_t *to_remove = find_seq_node(p, s);
  if (prev->first == to_remove) {
    prev->first = NULL;
  } else if (prev->second == to_remove) {
    prev->second = NULL;
  } else if (prev->third == to_remove) {
    prev->third = NULL;
  }
  // removes down from a given node
  delete_trie(to_remove, head);

  return 1;
}

// checks if string is in a set
int seq_valid(seq_t *p, char const *s) {
  if (!are_seq_parameters_ok(p, s)) {
    return -1;
  }

  return is_seq_in_set(p, s);
}
// set name for string abstraction class
int seq_set_name(seq_t *p, char const *s, char const *n) {
  if (!are_set_name_parameters_ok(p, s, n)) {
    return -1;
  }
  if (!is_seq_in_set(p, s)) {
    return 0;
  } else {
    // checks if current and new abstract class names are the same
    if (compare_names(
            find_seq_node(p, s)->abstract_class_list->abstract_class_name, n)) {
      return 0;
    }
  }
  bool error = false;
  change_name(find_seq_node(p, s)->abstract_class_list, n, &error);
  if (error) {
    return -1;
  }
  return 1;
}

// gets name of string's abstraction class
char const *seq_get_name(seq_t *p, char const *s) {
  if (!are_seq_parameters_ok(p, s)) {
    return NULL;
  }

  if (!is_seq_in_set(p, s) ||
      is_abstract_class_name_empty(find_seq_node(p, s)->abstract_class_list)) {
    errno = 0;
    return NULL;
  }

  return find_seq_node(p, s)->abstract_class_list->abstract_class_name;
}

// links two strings to have same abstraction class
int seq_equiv(seq_t *p, char const *s1, char const *s2) {
  if (!are_equiv_parameters_ok(p, s1, s2)) {
    return -1;
  }

  if (!will_abstract_class_change(p, s1, s2)) {
    return 0;
  }

  List *dest = create_new_abstract_class(
      &p->abstract_class_list,
      find_seq_node(p, s1)->abstract_class_list->abstract_class_name,
      find_seq_node(p, s2)->abstract_class_list->abstract_class_name);
  change_abstract_classes(p, find_seq_node(p, s1)->abstract_class_list,
                          find_seq_node(p, s2)->abstract_class_list, dest,
                          &(p->abstract_class_list));
  return 1;
}
