#include <stdio.h>
#include "hashtable.h"

Hashtable* create_hashtable(Hashtable* hashtable, int size)
{
	int i = 0;
	
	hashtable = malloc(sizeof(Hashtable));

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

	Hashtable* new_hashtable = NULL;

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

int print_hashtable(Hashtable* hashtable, FILE* out_file)
{
	int i = 0, return_code = 0;
	Node* current_node;
	Node* current_node_copy;
	
	for(i = 0; i<hashtable->size; i++)
	{
		current_node = hashtable->buckets[i].bucket_head;
		current_node_copy = current_node;
		
		while(current_node != NULL)
		{
			if(current_node->next_node == NULL)
			{
				fprintf(out_file, "%s", current_node->word);
				fprintf(out_file, "\n");
			}
			else
			{	
				fprintf(out_file, "%s ", current_node->word);
			}
				
			current_node = current_node->next_node;
		}	
	}
	
	return return_code;
}

int find_word(Hashtable* hashtable, char* word, FILE* out_file)
{
	int position = hash(word, hashtable->size), return_code = -1;

	Node* current_node = hashtable->buckets[position].bucket_head;

	if(current_node != NULL)
	{
		while(current_node != NULL)
		{
			if(strcmp(current_node->word, word) == 0)
			{
				fprintf(out_file, "%s\n", "True");
				return_code = 0;
				
				break;
			}
			current_node = current_node->next_node;
		}
	}
	else
		return_code = -1;
	
	if(return_code == -1)
		fprintf(out_file, "%s\n", "False");
	
	return return_code;
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

Node* get_new_node(char* word)
{
	Node* new_node;
	
	new_node = malloc(sizeof(Node));
	new_node->next_node = NULL;
	new_node->word = malloc((strlen(word) + 1) * sizeof(char));

	strcpy(new_node->word, word);
		
	return new_node;
}

int add_word(Hashtable* hashtable, char* word)
{
	int return_code = 0;	// 0 - success, 1 - the word already exist
	
	int position = hash(word, hashtable->size);
	
	Node* new_node = NULL;
	Node* current_node = NULL;
	
	if(hashtable->buckets[position].bucket_head == NULL)
	{
		Node* new_node = get_new_node(word);

		hashtable->buckets[position].bucket_head = new_node;
		
		return_code = 0;
	}
	else
	{
		current_node = hashtable->buckets[position].bucket_head;

		while(current_node->next_node != NULL)
		{
			if(strcmp(current_node->word, word) == 0)
			{
				return_code = -1;
				break;
			}
			current_node = current_node->next_node;
		}

		new_node = get_new_node(word);
		
		current_node->next_node = new_node;
	}
	
	return return_code;
}

int remove_word(Hashtable* hashtable, char* word)
{
	int position = hash(word, hashtable->size), return_code = 0;

	Node* current_node = hashtable->buckets[position].bucket_head;
	Node* back_node = current_node;

	if(current_node != NULL)
	{
		while(strcmp(current_node->word, word) != 0 && current_node != NULL)
		{
			back_node = current_node;
			current_node = current_node->next_node;
		}
		
		if(strcmp(current_node->word, word) != 0 && current_node == NULL)
				return_code = -1;
		else
		{
			if(back_node == current_node)	// If we remove the first word in the bucket
				hashtable->buckets[position].bucket_head = back_node->next_node;
			else
				back_node->next_node = current_node->next_node;

			free(current_node->word);
			free(current_node);
			
			return_code = 0;
		}
	}
	else
		return_code = -1;
	
	return return_code;
}

int print_bucket(Hashtable* hashtable, int bucket_index, FILE* out_file)
{
	int return_code = 0;
	
	if(bucket_index >= hashtable->size || bucket_index < 0)
		return_code = -1;
	else
	{
		Node* current_node = hashtable->buckets[bucket_index].bucket_head;

		if(current_node != NULL)
		{
			fprintf(out_file, "%s ", current_node->word);

			current_node = current_node->next_node;

			while(current_node != NULL)
			{
				if(current_node->next_node == NULL)
					fprintf(out_file, "%s ", current_node->word);
				else
					fprintf(out_file, "%s", current_node->word);
				
				current_node = current_node->next_node;
			}
		}
	}
	
	return return_code;
}
