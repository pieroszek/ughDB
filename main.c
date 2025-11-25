#include "database.c"
#include <stdio.h>


#define MAX_INPUT 100

void print_prompt(){

	/* create col */
	if(create_column_flag == 3){
		printf("column_table> ");
	}
	if(create_column_flag == 2){
		printf("column_name> ");
	}
	if(create_column_flag == 1){
		printf("column_type> ");
	}
	
	/* create table */
	if(create_table_flag == 2){
		printf("table_name> ");
	}
	
	/* */
	if(create_table_flag == 0) {
		if(create_column_flag == 0){
			printf("db> ");
		}
	}
}


void handle_command(char * command){

	/* col */
	if(create_column_flag == 1){
		last_command = command; // last_command hold col type
		db_main(); // with the name and type we go to db_main
	}
	if(create_column_flag == 2){
		saved_command = command; // saved command holds col name
		create_column_flag = 1; //once we got the name we ask for type 
	}
	if(create_column_flag == 3){
		saved_command_2 = command; // holds table name
		// should add check if table name exists
		create_column_flag = 2;
	}
	if(strcmp(command, "create column") == 0) {
		create_column_flag = 3;
	}
	
	/* table */
	if(create_table_flag == 2){
		last_command = command; //holds table name
		create_table_flag = 1;
		db_main();
	}
	if(strcmp(command, "create table") == 0) {
		create_table_flag = 2; // get table name
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
