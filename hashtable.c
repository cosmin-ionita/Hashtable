#include <stdio.h>
#include "hashtable.h"

Hashtable* create_hashtable(Hashtable* hashtable, int size)
{
	int i = 0;
	
	hashtable = (Hashtable*)malloc(sizeof(Hashtable));

	hashtable->size = size;

	hashtable->buckets = malloc(size * sizeof(Bucket));
	
	for(i = 0; i<size; i++)
	{
		hashtable->buckets[i].bucket_head = NULL;
	}

	return hashtable;
}

Hashtable* resize_hashtable(Hashtable* hashtable, int size)
{
	int i = 0;
	Node* current_node;

	Hashtable* new_hashtable;

	new_hashtable = create_hashtable(new_hashtable, size);

	for(i = 0; i<hashtable->size; i++)
	{
		current_node = hashtable->buckets[i].bucket_head;

		while(current_node != NULL)
		{
			add_word(new_hashtable, current_node->word);

			current_node = current_node->next_node;
		}
	}

	clear_hashtable(hashtable);

	return new_hashtable;

}

Hashtable* make_double(Hashtable* hashtable)
{
	return resize_hashtable(hashtable, hashtable->size * 2);
}

Hashtable* make_half(Hashtable* hashtable)
{
	return resize_hashtable(hashtable, hashtable->size / 2);
}

void print_hashtable(Hashtable* hashtable)
{
	int i = 0;
	Node* current_node;
	Node* current_node_copy;

	for(i = 0; i<hashtable->size; i++)
	{
		current_node = hashtable->buckets[i].bucket_head;
		current_node_copy = current_node;

		while(current_node != NULL)
		{
			printf("%s ", current_node->word); 
			current_node = current_node->next_node;
		}

		if(current_node != current_node_copy)
			printf("\n");
	}
}

char* find_word(Hashtable* hashtable, char* word)
{
	int position = hash(word, hashtable->size);

	Node* current_node = hashtable->buckets[position].bucket_head;

	if(current_node != NULL)
	{

		while(current_node != NULL)
		{
			if(strcmp(current_node->word, word) == 0)
			{
				return "True";
			}
			current_node = current_node->next_node;
		}

		return "False";
	}
}

void clear_hashtable(Hashtable* hashtable)
{
	int i = 0;
	Node* temp_node;
	Node* head_node;

	for(i = 0; i<hashtable->size; i++)
	{
		head_node = hashtable->buckets[i].bucket_head;

		while(head_node != NULL)
		{
			temp_node = head_node;
			head_node = head_node->next_node;
			
			free(temp_node->word);
			free(temp_node);
		}

		hashtable->buckets[i].bucket_head = NULL;
	}

	hashtable->size = 0;
	
	free(hashtable->buckets);
	free(hashtable);
}

void add_word(Hashtable* hashtable, char* word)
{
	int position = hash(word, hashtable->size);
	
	Node* new_node = NULL;
	Node* current_node = NULL;
	
	if(hashtable->buckets[position].bucket_head == NULL)
	{
		new_node = malloc(sizeof(Node));
		new_node->next_node = NULL;
		new_node->word = malloc((strlen(word) + 1) * sizeof(char));

		strcpy(new_node->word, word);

		hashtable->buckets[position].bucket_head = new_node;
	}
	else
	{
		current_node = hashtable->buckets[position].bucket_head;

		while(current_node->next_node != NULL)
		{
			current_node = current_node->next_node;
		}

		new_node = malloc(sizeof(Node));
		new_node->next_node = NULL;

		new_node->word = malloc((strlen(word) + 1) * sizeof(char));
		strcpy(new_node->word, word);

		current_node->next_node = new_node;
	}
	
}

void remove_word(Hashtable* hashtable, char* word)
{
	int position = hash(word, hashtable->size);
	Node* temp = NULL;
	Node* current_node = hashtable->buckets[position].bucket_head;
	Node* back_node = current_node;

	if(current_node != NULL)
	{

		while(strcmp(current_node->word, word) != 0)
		{
			back_node = current_node;
			current_node = current_node->next_node;
		}

		if(back_node == current_node)
		{
			hashtable->buckets[position].bucket_head = back_node->next_node;
		}
		else
		{
			back_node->next_node = current_node->next_node;
		}

		free(current_node->word);
		free(current_node);
	}
}

void print_bucket(Hashtable* hashtable, int bucket_index)
{
	Node* current_node = hashtable->buckets[bucket_index].bucket_head;

	if(current_node != NULL)
	{

		printf("am asa 1: %s\n", current_node->word);

		current_node = current_node->next_node;

		while(current_node != NULL)
		{
			printf("am asa 2: %s\n", current_node->word);
			current_node = current_node->next_node;
		}
	}
}
