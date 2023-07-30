# Introduction
A C library for handling sets of sequences with an equivalence relation. The elements of the sets are non-empty sequences consisting of the numbers 0, 1, and 2. Sequences are represented as strings.

# Library Interface
```
typedef struct seq seq_t;

seq_t *seq_new(void);
void seq_delete(seq_t *p);
int seq_add(seq_t *p, char const *s);
int seq_remove(seq_t *p, char const *s);
int seq_valid(seq_t *p, char const *s);
int seq_set_name(seq_t *p, char const *s, char const *n);
char const *seq_get_name(seq_t *p, char const *s);
int seq_equiv(seq_t *p, char const *s1, char const *s2);
```
# Function Descriptions
seq_new: Creates a new empty set of sequences.

seq_delete: Removes the set of sequences and frees the memory.

seq_add: Adds the given sequence and all non-empty prefixes of it to the set of sequences.

seq_remove: Removes the given sequence and all sequences for which it is a prefix.

seq_valid: Checks if the given sequence belongs to the set of sequences.

seq_set_name: Sets or changes the abstract class name to which the given sequence belongs.

seq_get_name: Returns a pointer to a string containing the name of the abstract class to which the given sequence belongs.

seq_equiv: Merges the abstract classes represented by the given sequences into one. If both abstract classes have names, the new abstract class inherits one of them. If they have different names, the new name is a combination of both. If both abstract classes have the same name, the new abstract class retains that name.
Notes

A valid sequence is a non-empty string ending with the '\0' character, consisting of characters 0, 1, or 2.
A valid abstract class name is a non-empty string ending with the '\0' character.
In case of memory allocation errors, functions set errno to ENOMEM.
In case of invalid parameters, functions set errno to EINVAL.
For more information and usage examples, refer to the seq_example.c file.
