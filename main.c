#include <stdio.h>
#include "hashtable.h"

int main()
{
	char str[10] = "asdad";
	Hashtable* hashtable;

	hashtable = create_hashtable(hashtable, 2);

	
	
	add_word(hashtable, str);
	add_word(hashtable, "boss");
	add_word(hashtable, "sadad");
	add_word(hashtable, "xzzz");
	add_word(hashtable, "1122");

	printf("b0: ->");

	print_bucket(hashtable, 0);

	printf("b1: ->");
	print_bucket(hashtable, 1);


	clear_hashtable(hashtable);

	return 0;
}
