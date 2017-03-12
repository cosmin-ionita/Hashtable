#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "hashtable.h"

#define COMM_SIZE 20000

int process_command(char *command, Hashtable* hashtable);

int launch_add(Hashtable* hashtable);
int launch_remove(Hashtable* hashtable);
int launch_find(Hashtable* hashtable);
int launch_print_hashtable(Hashtable* hashtable);
int launch_print_bucket(Hashtable* hashtable);
int launch_clear(Hashtable* hashtable);
int launch_resize(Hashtable* hashtable);

Hashtable* main_hashtable;

int main(int argc, char** argv)
{
	FILE* in_file;
	int i = 0, code = 0;
	char* result;
	char command[COMM_SIZE];

	if(argc > 1)
		main_hashtable = create_hashtable(main_hashtable, atoi(argv[1]));
	else
		fprintf(stderr, "Not OK");
	
	if (argc > 2)
	{
		for(i = 2; i<argc; i++)
		{
			in_file = fopen(argv[i], "r");
			DIE(in_file == NULL, "File does not exist");
			
			while(!feof(in_file))
			{
				result = fgets(command, COMM_SIZE, in_file);
				
				if(result != NULL && result[0] != '\n')
				{
					code = process_command(command, main_hashtable);
					
					DIE(code > 0, "Error");
					
					if(code < 0)
						fprintf(stderr, "error");
				}
			}
		}
	}
	else if(argc == 2)
	{
		while(!feof(stdin))
		{
			result = fgets(command, COMM_SIZE, stdin);
			
			if(result != NULL && result[0] != '\n')
			{
				code = process_command(command, main_hashtable);
				
				DIE(code > 0, "Error");
				
				fprintf(stderr, "Error");

			}
		}
	}
	else
		fprintf(stderr, "NOT OK");

	free_hashtable(main_hashtable);
	
	return 0;
}

int process_command(char* command, Hashtable* hashtable)
{
	int return_code = 1;
	char* token;
	const char delimiter[1] = " ";
	
	if(command[strlen(command)-1] == '\n')
		command[strlen(command)-1] = '\0';
	
	token = strtok(command, delimiter);
	
	if(strcmp(token, "add") == 0)
		return_code = launch_add(hashtable);
	
	else if(strcmp(token, "remove") == 0)
		return_code = launch_remove(hashtable);
	
	else if(strcmp(token, "print_bucket") == 0)
		return_code = launch_print_bucket(hashtable);
	
	else if(strcmp(token, "find") == 0)
		return_code = launch_find(hashtable);
	
	else if(strcmp(token, "clear") == 0)
		return_code = launch_clear(hashtable);
	
	else if(strcmp(token, "resize") == 0)
		return_code = launch_resize(hashtable);

	else if(strcmp(token, "print") == 0)
		return_code = launch_print_hashtable(hashtable);
	
	return return_code;
}

int launch_add(Hashtable* hashtable)
{
	char* token;
	char delimiter[1] = " ";
	
	token = strtok(NULL, delimiter);
		
	return add_word(hashtable, token);
}

int launch_remove(Hashtable* hashtable)
{
	char* token;
	char delimiter[1] = " ";
	
	token = strtok(NULL, delimiter);
	
	return remove_word(hashtable, token);
}

int launch_print_bucket(Hashtable* hashtable)
{
	FILE* out_file;
	
	int result_code = 0, bucket_index = -1;
	
	char delimiter[1] = " ";
	char* token;
	char* temp_token;

	token = strtok(NULL, delimiter);
	temp_token = strtok(NULL, delimiter);
	
	if(temp_token == NULL)
	{
		bucket_index = strtol(token, NULL, 10);

		if(bucket_index == 0)
			result_code = 1;
		else
			result_code = print_bucket(hashtable, bucket_index, stdout);
	}
	else
	{
		out_file = fopen(temp_token, "a");
		DIE(out_file == NULL, "File couldn't be opened!");
		
		result_code = print_bucket(hashtable, atoi(token), out_file);
		
		fclose(out_file);
	}

	return result_code;
}

int launch_find(Hashtable* hashtable)
{	
	int return_code = 0;
	FILE* out_file;
	char delimiter[1] = " ";
	char* token;
	char* temp_token;
	
	token = strtok(NULL, delimiter);
	temp_token = strtok(NULL, delimiter);
	
	if(temp_token == NULL)
	{
		return_code = find_word(hashtable, token, stdout);
	}
	else
	{
		out_file = fopen(temp_token, "a");
		DIE(out_file == NULL, "File couldn't be opened!");
		
		return_code = find_word(hashtable, token, out_file);
		
		fclose(out_file);
	}
	
	return return_code;
}

int launch_clear(Hashtable* hashtable)
{
	clear_hashtable(hashtable);	
	
	return 0;
}

int launch_resize(Hashtable* hashtable)
{
	int return_code = 0;
	FILE* out_file;
	char* token;
	char delimiter[1] = " ";
	
	token = strtok(NULL, delimiter);
		
	if(strcmp(token, "double") == 0)
	{
		main_hashtable = make_double(hashtable);
	}
	else if(strcmp(token, "halve") == 0)
	{
		main_hashtable = make_half(hashtable);
	}
	
	return return_code;
}

int launch_print_hashtable(Hashtable* hashtable)
{
	int return_code = 0; 
	FILE* out_file; 
	char* token;
	
	char delimiter[1] = " ";
	
	token = strtok(NULL, delimiter);
	
	if(token == NULL)
	{
		return_code = print_hashtable(hashtable, stdout);
	}
	else
	{
		out_file = fopen(token, "a");
		DIE(out_file == NULL, "File couldn't be opened!");
		
		return_code = print_hashtable(hashtable, out_file);
		
		fclose(out_file);
	}
	
	return return_code;
}

