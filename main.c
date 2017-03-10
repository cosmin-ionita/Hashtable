#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "hashtable.h"

#define COMM_SIZE 20000

int process_command(char* command, Hashtable* hashtable);

int main(int argc, char** argv)
{
	FILE* in_file;
	int i = 0;
	char* result;
	char command[COMM_SIZE];
	Hashtable* hashtable = NULL;
		
	hashtable = create_hashtable(hashtable, atoi(argv[1]));
	
	if(argc > 2)
	{
		for(i = 2; i<argc; i++)
		{
			in_file = fopen(argv[i], "r");
			DIE(in_file == NULL, "File does not exist");
			
			while(!feof(in_file))
			{
				result = fgets(command, COMM_SIZE, in_file);
				DIE(result == NULL, "Could not read the line");
				
				i = process_command(command, hashtable);
			}
		}
	}
	else
	{
		//read from stdin!
	}
	
	return 0;
}

int process_command(char* command, Hashtable* hashtable)
{
	char* token;
	char* temp_token;
	
	FILE* out_file;
	
	char delimiter[1] = " ";
	 
	token = strtok(command, delimiter);
	
	if(strcmp(token, "add"))
	{
		token = strtok(NULL, delimiter);
		
		return add_word(hashtable, token);
	}
	else if(strcmp(token, "remove"))
	{
		token = strtok(NULL, delimiter);
		
		return remove_word(hashtable, token);
	}
	else if(strcmp(token, "print_bucket"))
	{
		token = strtok(NULL, delimiter);
		temp_token = strtok(NULL, delimiter);
		
		if(temp_token == NULL)
		{
			print_bucket(hashtable, atoi(token), stdout);
		}
		else
		{
			out_file = fopen(temp_token, "a");
			DIE(out_file == NULL, "File couldn't be opened!");
			
			print_bucket(hashtable, atoi(token), out_file);
			
			fclose(out_file);
		}
	}
	else if(strcmp(token, "find"))
	{
		token = strtok(NULL, delimiter);
		temp_token = strtok(NULL, delimiter);
		
		if(temp_token == NULL)
		{
			return find_word(hashtable, token, stdout);
		}
		else
		{
			out_file = fopen(temp_token, "a");
			DIE(out_file == NULL, "File couldn't be opened!");
			
			find_word(hashtable, token, out_file);
			
			fclose(out_file);
		}
	}
	else if(strcmp(token, "clear"))
	{
		clear_hashtable(hashtable);
	}
	else if(strcmp(token, "resize"))
	{
		token = strtok(NULL, delimiter);
		
		if(strcmp(token, "double"))
		{
			hashtable = make_double(hashtable);
		}
		else if(strcmp(token, "halve"))
		{
			hashtable = make_half(hashtable);
		}
	}
	else if(strcmp(token, "print"))
	{
		token = strtok(NULL, delimiter);
		
		if(token == NULL)
		{
			print_hashtable(hashtable, stdout);
		}
		else
		{
			out_file = fopen(token, "a");
			DIE(out_file == NULL, "File couldn't be opened!");
			
			print_hashtable(hashtable, out_file);
			
			fclose(out_file);
		}
	}
	
	return 0;
}
