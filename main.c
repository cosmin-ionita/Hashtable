#include <stdio.h>
#include "hashtable.h"

int main()
{
	Hashtable* hashtable;

	hashtable = create_hashtable(hashtable, 10);

	char str[10] = "asdad";
	
	add_word(hashtable, str);
	add_word(hashtable, "boss");

	print_bucket(hashtable, 3);


	//clear_hashtable(hashtable);

	return 0;
}
