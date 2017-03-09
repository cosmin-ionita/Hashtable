#include <stdio.h>
#include "hashtable.h"

Hashtable* create_hashtable(Hashtable* hashtable, int size)
{
	hashtable->size = size;

	hashtable = malloc(sizeof(Hashtable));

	hashtable->buckets = malloc(size * sizeof(Bucket));


	return hashtable;
}

void clear_hashtable(Hashtable* hashtable)
{
	hashtable->size = 0;
	
	free(hashtable->buckets);
	free(hashtable);
}
