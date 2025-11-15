#include "database.c"
#include <stdio.h>


#define MAX_INPUT 100

void print_prompt(){
	printf("db> ");
}


void handle_command(char * command){
	if(strcmp(command, "create table") == 0) {
	
		create_table_flag = 1;
		db_main();
	}
	return;
}



int main(int argc, char *argv[]){
	db_init_main();

	//char input[MAX_INPUT];
	create_table_flag = 1;
	db_main();
	/*
	if(1){ //only for compile
	while (1) {
		print_prompt();

		// This BLOCKS until user presses Enter - which is FINE!
		if (fgets(input, sizeof(input), stdin)) {
			// Remove newline
			input[strcspn(input, "\n")] = 0;

			// Handle empty input
			if (strlen(input) == 0) {
				continue;
			}

			handle_command(input);
		}
	}
	}
	*/
	return 0;
}
