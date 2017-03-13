#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

typedef struct Node Node;
typedef struct Bucket Bucket;
typedef struct Hashtable Hashtable;

struct Node {
	char *word;
	Node *next_node;
};

struct Bucket {
	Node *bucket_head;
};

struct Hashtable {
	int size;
	Bucket *buckets;
};

Hashtable *create_hashtable(Hashtable *hashtable, int size);

Hashtable *make_double(Hashtable *hashtable);
Hashtable *make_half(Hashtable *hashtable);

void clear_hashtable(Hashtable *hashtable);

int add_word(Hashtable *hashtable, char *word);
int remove_word(Hashtable *hashtable, char *word);

int print_bucket(Hashtable *hashtable, int bucket_index, FILE *out_file);
int print_hashtable(Hashtable *hashtable, FILE *out_file);

int find_word(Hashtable *hashtable, char *word, FILE *out_file);

#endif
