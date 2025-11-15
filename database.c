#include <string.h>
#include "database.h"

int create_table_flag = 0; //making ure it starts at 0

FILE_PTR_LIST TableSchema_File_Ptr_List;
FILE_PTR_LIST TableData_File_Ptre_List;

BTree_Root_List Root_Node_List;
TableSchema_List Table_Schema_List;


BTree_Node * create_btree_node(){ 
	BTree_Node * new_node = malloc(sizeof(BTree_Node));
	return new_node;
}

void init_btrl(BTree_Root_List btrl){
	btrl.len = 5;
	btrl.List = malloc(sizeof(BTree_Node) * btrl.len);
	btrl.counter = 0;
}


void add_to_btrl(BTree_Root_List * btrl, BTree_Node * node);

void init_fpl(FILE_PTR_LIST fpl){
	fpl.file_ptr_list = malloc(sizeof(FILE*) * 10);
	fpl.counter = 0;
	fpl.len = 10;
}

void add_to_fpl(FILE_PTR_LIST fpl, FILE * file_ptr){
	if(fpl.counter == fpl.len - 1){
		fpl.len += 2;
		fpl.file_ptr_list = realloc(fpl.file_ptr_list, sizeof(FILE*) * fpl.len);
	}
	fpl.counter++;
	fpl.file_ptr_list[fpl.counter] = file_ptr;
}

void init_tsl(TableSchema_List tsl){
	tsl.len = 5;
	tsl.List = malloc(sizeof(TableSchema) * tsl.len);
	tsl.counter = 0;

}

void add_to_tsl(TableSchema_List * tsl, TableSchema * table_schema); 

TableSchema * create_table(){
	//im creating a new root node and adding it to the list,
	//the table schema should have the same index as the root node
	

	TableSchema * newtable = malloc(sizeof(newtable));
	newtable->table_name = "table";
	newtable->root_node_offset = 0x0; //todo when file read write is implemented
	newtable->column_count = 0;
	return newtable;
}



int db_main () {
	//list to keep track of files where data is saved	
	init_fpl(TableSchema_File_Ptr_List);
	init_fpl(TableData_File_Ptre_List);

	//list to keep track of live tables and data
	init_btrl(Root_Node_List);
	init_tsl(Table_Schema_List);
	

	create_table_flag = 0;

	if(create_table_flag){
		create_table_flag = 0;
		create_table();
	}
	return 0;
}

