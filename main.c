#include <stdio.h>
#include "hashtable.h"

int main(int argc, char** argv)
{
	Hashtable* hashtable;

	hashtable = create_hashtable(hashtable, 10);
	
	clear_hashtable(hashtable);

	return 0;
}
