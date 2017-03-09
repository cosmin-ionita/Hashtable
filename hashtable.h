#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Bucket Bucket;
typedef struct Hashtable Hashtable;

struct Node
{
	char* word;
	Node* next_node;
};

struct Bucket
{
	Node* bucket_head;		

};

struct Hashtable
{
	int size;

	Bucket* buckets;
};

Hashtable* create_hashtable(Hashtable* hashtable, int size);
void clear_hashtable(Hashtable* hashtable);

#endif
