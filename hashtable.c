#include <stdio.h>
#include "hashtable.h"

Hashtable* create_hashtable(Hashtable* hashtable, int size)
{
	hashtable = (Hashtable*)malloc(sizeof(Hashtable));

	hashtable->size = size;

	hashtable->buckets = malloc(size * sizeof(Bucket));

	return hashtable;
}

void clear_hashtable(Hashtable* hashtable)
{
	hashtable->size = 0;
	
	free(hashtable->buckets);
	free(hashtable);
}

void add_word(Hashtable* hashtable, char* word)
{
	int position = 3; // through the hash function
	
	Node* new_node = NULL;
	Node* current_node = NULL;
	
	if(hashtable->buckets[position].bucket_head == NULL)
	{
		printf("IS NULL");
		/*hashtable->buckets[position].bucket_head = malloc(sizeof(Node));
	
		new_node = malloc(sizeof(Node));
		new_node->next_node = NULL;
		new_node->word = malloc(strlen(word) * sizeof(char));
		strcpy(new_node->word, word);

		hashtable->buckets[position].bucket_head = new_node;
	*/}
	else
	{
	printf("IS NOT NULL");
	
		current_node = hashtable->buckets[position].bucket_head;

		while(current_node->next_node != NULL)
		{
			current_node = current_node->next_node;
		}

		new_node = malloc(sizeof(Node));
		new_node->next_node = NULL;

		new_node->word = malloc(strlen(word) * sizeof(char));
		strcpy(new_node->word, word);

		current_node->next_node = new_node;
	}
}

void print_bucket(Hashtable* hashtable, int bucket_index)
{
	Node* current_node = hashtable->buckets[bucket_index].bucket_head;

	printf("%s\n", current_node->word);

	current_node = current_node->next_node;

	while(current_node != NULL)
	{
		printf("%s\n", current_node->word);
		current_node = current_node->next_node;
	}

}
