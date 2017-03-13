#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"

#define COMM_SIZE 20000

int process_command(char *command, Hashtable *hashtable);

int launch_add(Hashtable *hashtable);
int launch_remove(Hashtable *hashtable);
int launch_find(Hashtable *hashtable);
int launch_print_hashtable(Hashtable *hashtable);
int launch_print_bucket(Hashtable *hashtable);
int launch_clear(Hashtable *hashtable);
int launch_resize(Hashtable *hashtable);

Hashtable *Hash;

int main(int argc, char **argv)
{
	FILE *in_file;
	int i = 0, code = 0, size = 0;
	char *result;
	char command[COMM_SIZE];

	if (argc > 1) {

		size = strtol(argv[1], NULL, 10);

		if (size != 0)
			Hash = create_hashtable(Hash, size);
		else {
			fprintf(stderr, "Invalid size");
			return -1;
		}
	} else {
		fprintf(stderr, "The argc is 1!");
		return EXIT_FAILURE;
	}

	if (argc > 2) {
		for (i = 2; i < argc; i++) {

			in_file = fopen(argv[i], "r");

			if (in_file == NULL) {
				free_hashtable(Hash);
				fclose(in_file);

				fprintf(stderr, "Fisierul nu exista");
				return -1;
			}

			while (!feof(in_file)) {
				result = fgets(command, COMM_SIZE, in_file);

				if (result != NULL && result[0] != '\n') {
					code = process_command(command, Hash);

					if (code < 0) {
						free_hashtable(Hash);
						fclose(in_file);
						
						fprintf(stderr, "Eroare");
						return -1;
					}
				}
			}

			fclose(in_file);
		}
	} else if (argc == 2) {
		while (!feof(stdin)) {
			result = fgets(command, COMM_SIZE, stdin);

			if (result != NULL && result[0] != '\n') {
				code = process_command(command, Hash);

				if (code < 0) {
					free_hashtable(Hash);

					fprintf(stderr, "Eroare");
					return -1;
				}
			}
		}
	} else
		fprintf(stderr, "NOT OK");

	free_hashtable(Hash);

	return 0;
}

int process_command(char *command, Hashtable *hashtable)
{
	int return_code = -1;
	char *token;
	const char delimiter[] = " ";

	if (command[strlen(command)-1] == '\n')
		command[strlen(command)-1] = '\0';

	token = strtok(command, delimiter);

	if (strcmp(token, "add") == 0)
		return_code = launch_add(hashtable);

	else if (strcmp(token, "remove") == 0)
		return_code = launch_remove(hashtable);

	else if (strcmp(token, "print_bucket") == 0)
		return_code = launch_print_bucket(hashtable);

	else if (strcmp(token, "find") == 0)
		return_code = launch_find(hashtable);

	else if (strcmp(token, "clear") == 0)
		return_code = launch_clear(hashtable);

	else if (strcmp(token, "resize") == 0)
		return_code = launch_resize(hashtable);

	else if (strcmp(token, "print") == 0)
		return_code = launch_print_hashtable(hashtable);

	return return_code;
}

int launch_add(Hashtable *hashtable)
{
	char *token;
	int return_code = 0;
	const char delimiter[] = " ";

	token = strtok(NULL, delimiter);

	if (token != NULL)
		return_code =  add_word(hashtable, token);
	else
		return_code = -1;

	return return_code;
}

int launch_remove(Hashtable *hashtable)
{
	char *token;
	const char delimiter[] = " ";

	token = strtok(NULL, delimiter);

	if (token != NULL)
		return remove_word(hashtable, token);
	else
		return -1;
}

int launch_print_bucket(Hashtable *hashtable)
{
	FILE *out_file;

	int code = 0, bucket_index = -1;

	const char delimiter[] = " ";
	char *token;
	char *temp_token;

	token = strtok(NULL, delimiter);
	temp_token = strtok(NULL, delimiter);

	if (temp_token == NULL) {
		bucket_index = strtol(token, NULL, 10);

		if (bucket_index == 0)
			code = -1;
		else
			code = print_bucket(hashtable, bucket_index, stdout);
	} else {
		out_file = fopen(temp_token, "a");

		if (out_file != NULL) {

			code = print_bucket(hashtable, atoi(token), out_file);

			fclose(out_file);
		} else
			code = -1;
	}

	return code;
}

int launch_find(Hashtable *hashtable)
{
	int return_code = 0;
	FILE *out_file;
	const char delimiter[] = " ";
	char *token;
	char *temp_token;

	token = strtok(NULL, delimiter);
	temp_token = strtok(NULL, delimiter);

	if (temp_token == NULL) {
		return_code = find_word(hashtable, token, stdout);
	} else {
		out_file = fopen(temp_token, "a");

		if (out_file != NULL) {
			return_code = find_word(hashtable, token, out_file);
			fclose(out_file);
		} else {
			return_code = -1;
		}
	}

	return return_code;
}

int launch_clear(Hashtable *hashtable)
{
	clear_hashtable(hashtable);

	return 0;
}

int launch_resize(Hashtable *hashtable)
{
	int return_code = 0;
	char *token;
	const char delimiter[] = " ";

	token = strtok(NULL, delimiter);

	if (strcmp(token, "double") == 0)
		Hash = make_double(hashtable);
	else if (strcmp(token, "halve") == 0)
		Hash = make_half(hashtable);

	return return_code;
}

int launch_print_hashtable(Hashtable *hashtable)
{
	int return_code = 0;
	FILE *out_file;
	char *token;
	const char delimiter[] = " ";

	token = strtok(NULL, delimiter);

	if (token == NULL) {
		return_code = print_hashtable(hashtable, stdout);
	} else {

		out_file = fopen(token, "a");

		if (out_file != NULL) {

			return_code = print_hashtable(hashtable, out_file);

			fclose(out_file);
		} else {
			return_code = -1;
		}
	}

	return return_code;
}
