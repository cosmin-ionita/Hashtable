#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"

#define COMM_SIZE 20000
#define ERROR_CODE -1

int process_command(char *command, Hashtable *hashtable);

void system_exit(FILE *opened_file);

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
			return ERROR_CODE;
		}
	} else {
		fprintf(stderr, "The argc is 1!");
		return ERROR_CODE;
	}

	if (argc > 2) {	/* if we have multiple files as input */

		for (i = 2; i < argc; i++) {

			in_file = fopen(argv[i], "r");

			if (in_file == NULL)
				system_exit(in_file);

			while (!feof(in_file)) {
				result = fgets(command, COMM_SIZE, in_file);

				if (result != NULL && result[0] != '\n') {
					code = process_command(command, Hash);

					if (code < 0)
						system_exit(in_file);
				}
			}

			fclose(in_file);
		}
	} else if (argc == 2) {	/* if we read from stdin */

		while (!feof(stdin)) {
			result = fgets(command, COMM_SIZE, stdin);

			if (result != NULL && result[0] != '\n') {

				code = process_command(command, Hash);

				if (code < 0)
					system_exit(NULL);
			}
		}
	}

	free_hashtable(Hash);

	return 0;
}

/* deallocate resources and exit */
void system_exit(FILE *opened_file)
{
	free_hashtable(Hash);

	if (opened_file != NULL)
		fclose(opened_file);

	exit(ERROR_CODE);
}

int process_command(char *command, Hashtable *hashtable)
{
	int return_code = -1;
	char *token;
	const char delimiter[] = " ";

	/* replace the \n with NULL */

	if (command[strlen(command)-1] == '\n')
		command[strlen(command)-1] = '\0';

	/* get the first command token */

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
	else {
		return_code = -1;
		fprintf(stderr, "The word wasn't supplied");
	}

	return return_code;
}

int launch_remove(Hashtable *hashtable)
{
	char *token;
	int return_code = 0;
	const char delimiter[] = " ";

	token = strtok(NULL, delimiter);

	if (token != NULL)
		return_code = remove_word(hashtable, token);
	else {
		return_code = -1;
		fprintf(stderr, "The word wasn't supplied");
	}

	return return_code;
}

int launch_print_bucket(Hashtable *hashtable)
{
	FILE *out_file;

	int code = 0, bucket_index = -1;

	const char delimiter[] = " ";

	char *token;
	char *file_name;

	token = strtok(NULL, delimiter);
	file_name = strtok(NULL, delimiter);

	/* if we don't have a file as an output */

	if (file_name == NULL) {

		bucket_index = strtol(token, NULL, 10);

		if (bucket_index == 0) {
			code = -1;
			fprintf(stderr, "Invalid bucket index");
		} else
			code = print_bucket(hashtable, bucket_index, stdout);
	} else {
		out_file = fopen(file_name, "a");

		if (out_file != NULL) {

			code = print_bucket(hashtable, atoi(token), out_file);

			fclose(out_file);

		} else {
			code = -1;
			fprintf(stderr, "The file couldn't be opened");
		}
	}

	return code;
}

int launch_find(Hashtable *hashtable)
{
	int return_code = 0;

	FILE *out_file;

	const char delimiter[] = " ";

	char *token;
	char *file_name;

	token = strtok(NULL, delimiter);
	file_name = strtok(NULL, delimiter);

	if (file_name == NULL) {
		return_code = find_word(hashtable, token, stdout);

	} else {
		out_file = fopen(file_name, "a");

		if (out_file != NULL) {

			return_code = find_word(hashtable, token, out_file);
			fclose(out_file);

		} else {
			return_code = -1;
			fprintf(stderr, "The file couldn't be opened");
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

	if (token == NULL)
		return_code = print_hashtable(hashtable, stdout);

	else {

		out_file = fopen(token, "a");

		if (out_file != NULL) {

			return_code = print_hashtable(hashtable, out_file);

			fclose(out_file);

		} else {
			return_code = -1;
			fprintf(stderr, "The file couldn't be opened");
		}
	}

	return return_code;
}
