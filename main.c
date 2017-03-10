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

	print_hashtable(hashtable);

	hashtable = make_double(hashtable);


	print_hashtable(hashtable);
	


	clear_hashtable(hashtable);

	return 0;
}
