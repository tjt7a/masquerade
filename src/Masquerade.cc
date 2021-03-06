#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <glib.h>
#include <pbc.h>
#include <pbc_random.h>

#include "bswabe.h"
#include "../cpabe-0.11/common.h"

const char* usage ="Usage: \nFor existing keyset file: Masquerade -k <keyset file>\nTo create a new keyset file: Masquerade -n\n";

static char* keysetfile = "keyset.ks";

void
parse_args( int argc, char** argv )
{

	if(argc > 1){
		// 
		if(!strcmp(argv[1], "-k") && !strcmp(argv[1], "--keyset"))
		{
			if((!strcmp(argv[1], "-n") && !strcmp(argv[1], "--newkeyset")))
			{
				make_keyset();
				return;
			}
			
			printf("%s", usage);
			exit(0);
		}
		else{
			keysetfile = argv[2];
		}
	}
	else{
		printf("%s", usage);
		exit(0);
	}

}

int
make_keyset(){

	//char* 
	return 1;
}

int main(int argc, char** argv){

	parse_args(argc, argv);

	char* keyset = suck_file_str(keysetfile); // Read keysetfile

	printf("%s", keyset);

	return 0;
}
