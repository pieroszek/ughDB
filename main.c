#include "database.c"
#include <stdio.h>


#define MAX_INPUT 100

void print_prompt(){

	if(create_column_flag == 1){
			printf("column_name> ");
	}
	else {
		printf("db> ");
	}
}


void handle_command(char * command){
	last_command = command; //for use to name obj's
	if(create_column_flag){
		db_main();
	}
	if(strcmp(command, "create table") == 0) {
	
		create_table_flag = 1;
		db_main();
	}
	if(strcmp(command, "create column") == 0) {
	
		create_column_flag = 1;
	}
	

	return;
}



int main(int argc, char *argv[]){
	db_init_main();

	char input[MAX_INPUT];

	
	if(1){ //only for compile
	while (1) {

		print_prompt();
	
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
	
	return 0;
}
