#include <stdio.h>
#include "hashtable.h"

void free_hashtable(Hashtable *hashtable);

Hashtable *create_hashtable(Hashtable *hashtable, int size)
{
	int i = 0;

	hashtable = malloc(sizeof(Hashtable));

	hashtable->size = size;

	hashtable->buckets = malloc(size * sizeof(Bucket));

	for (i = 0; i < size; i++)
		hashtable->buckets[i].bucket_head = NULL;

	return hashtable;
}

Hashtable *resize_hashtable(Hashtable *hashtable, int size)
{
	int i = 0;
	Node *current_node;

	Hashtable *new_hashtable = NULL;

	new_hashtable = create_hashtable(new_hashtable, size);

	for (i = 0; i < hashtable->size; i++) {
		current_node = hashtable->buckets[i].bucket_head;

		while (current_node != NULL) {
			add_word(new_hashtable, current_node->word);

			current_node = current_node->next_node;
		}
	}

	free_hashtable(hashtable);

	return new_hashtable;
}

Hashtable *make_double(Hashtable *hashtable)
{
	return resize_hashtable(hashtable, hashtable->size * 2);
}

Hashtable *make_half(Hashtable *hashtable)
{
	return resize_hashtable(hashtable, (hashtable->size) / 2);
}

int print_bucket(Hashtable *hashtable, int bucket_index, FILE *out_file)
{
	int return_code = 0;
	int print_newline = 0;
	Node *current_node;

	if (bucket_index > hashtable->size || bucket_index < 0)
		return_code = -1;
	else {
		current_node = hashtable->buckets[bucket_index].bucket_head;

		while (current_node != NULL) {
			if (current_node->next_node == NULL) {
				fprintf(out_file, "%s", current_node->word);
				fprintf(out_file, "\n");
			} else {
				fprintf(out_file, "%s ", current_node->word);
			}

			current_node = current_node->next_node;
		}
	}

	return return_code;
}

int print_hashtable(Hashtable *hashtable, FILE *out_file)
{
	int i = 0, return_code = 0;

	for (i = 0; i < hashtable->size; i++)
		return_code = print_bucket(hashtable, i, out_file);

	return return_code;
}

int find_word(Hashtable *hashtable, char *word, FILE *out_file)
{
	int position = hash(word, hashtable->size), return_code = 0;

	Node *current_node = hashtable->buckets[position].bucket_head;

	while (current_node != NULL) {
		if (strcmp(current_node->word, word) == 0) {
			fprintf(out_file, "%s\n", "True");

			return return_code;
		}
		current_node = current_node->next_node;
	}

	fprintf(out_file, "%s\n", "False");

	return return_code;
}

void clear_hashtable(Hashtable *hashtable)
{
	int i = 0;
	Node *temp_node;
	Node *head_node;

	for (i = 0; i < hashtable->size; i++) {
		head_node = hashtable->buckets[i].bucket_head;

		while (head_node != NULL) {
			temp_node = head_node;
			head_node = head_node->next_node;

			free(temp_node->word);
			free(temp_node);
		}

		hashtable->buckets[i].bucket_head = NULL;
	}
}

void free_hashtable(Hashtable *hashtable)
{
	clear_hashtable(hashtable);

	hashtable->size = 0;

	free(hashtable->buckets);
	free(hashtable);
}

Node *get_new_node(char *word)
{
	Node *new_node;

	new_node = (Node *)malloc(sizeof(Node));
	new_node->next_node = NULL;
	new_node->word = malloc((strlen(word) + 1) * sizeof(char));

	strcpy(new_node->word, word);

	return new_node;
}

int add_word(Hashtable *hashtable, char *word)
{
	int return_code = 0;

	int position = hash(word, hashtable->size);

	Node *new_node = NULL;
	Node *current_node = NULL;

	new_node = get_new_node(word);
	
	if (hashtable->buckets[position].bucket_head == NULL) {
		hashtable->buckets[position].bucket_head = new_node;

		return_code = 0;
	} else {
		current_node = hashtable->buckets[position].bucket_head;

		while (current_node->next_node != NULL) {
			if (strcmp(current_node->word, word) == 0) {
				return_code = 1;
				break;
			}
			current_node = current_node->next_node;
		}

		if (strcmp(current_node->word, word) != 0) {
			current_node->next_node = new_node;
		}
	}

	return return_code;
}

int remove_word(Hashtable *Hash, char *word)
{
	int pos = hash(word, Hash->size), return_code = 0;

	Node *current_node = Hash->buckets[pos].bucket_head;
	Node *back_node = current_node;
	Node *temp_node;

	while (current_node != NULL && strcmp(current_node->word, word) != 0) {
		back_node = current_node;
		current_node = current_node->next_node;
	}

	if (current_node != NULL) {
		if (back_node == current_node) {
			temp_node = Hash->buckets[pos].bucket_head;

			Hash->buckets[pos].bucket_head = back_node->next_node;

			free(temp_node->word);
			free(temp_node);
		} else {
			back_node->next_node = current_node->next_node;

			free(current_node->word);
			free(current_node);

			return_code = 0;
		}
	}

	return return_code;
}
