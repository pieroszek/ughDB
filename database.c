#include <string.h>
#include "database.h"
#include "file_io.c"

int create_table_flag = 0; //making ure it starts at 0



BTree_Root_List Root_Node_List;
TableSchema_List Table_Schema_List;


BTree_Node * create_btree_node(){ 
	BTree_Node * new_node = malloc(sizeof(BTree_Node));
	return new_node;
}

void init_btrl(BTree_Root_List * btrl){
	btrl->len = 5;
	btrl->List = malloc(sizeof(BTree_Node) * btrl->len);
	btrl->counter = 0;
}


void add_to_btrl(BTree_Root_List * btrl, BTree_Node * node){
	if(btrl->counter >= (btrl->len - 1)){
		btrl->len += 2;
		btrl->List = realloc(btrl->List, sizeof(BTree_Node) * btrl->len);
	}
	btrl->List[btrl->counter] = node;
	btrl->counter++;
}

void init_fpl(FILE_PTR_LIST * fpl){
	fpl->file_ptr_list = malloc(sizeof(FILE) * 10);
	fpl->counter = 0;
	fpl->len = 10;
}

void add_to_fpl(FILE_PTR_LIST * fpl, FILE * file_ptr){
	if(fpl->counter == fpl->len - 2){
		fpl->len += 2;
		fpl->file_ptr_list = realloc(fpl->file_ptr_list, sizeof(FILE*) * fpl->len);
	}

	fpl->file_ptr_list[fpl->counter] = file_ptr;
	fpl->counter++;
}

void init_tsl(TableSchema_List * tsl){
	tsl->len = 5;
	tsl->List = malloc(sizeof(TableSchema) * tsl->len);
	tsl->counter = 0;

}

void add_to_tsl(TableSchema_List * tsl, TableSchema * table_schema){
	if(tsl->counter >= (tsl->len -1)){
		tsl->len += 2;
		tsl->List = realloc(tsl->List, sizeof(TableSchema) * tsl->len);
	}
	tsl->List[tsl->counter] = table_schema;
	tsl->counter++;
}

void create_table(){
	//im creating a new root node and adding it to the list,
	//the table schema should have the same index as the root node
	BTree_Node * new_root_node = create_btree_node();
	create_btree_file();
	add_to_btrl(&Root_Node_List, new_root_node);
	
	TableSchema * newtable = malloc(sizeof(*newtable));
	newtable->table_name = "table";
	newtable->root_node_offset = 0x0; //todo when file read write is implemented
	newtable->column_count = 0x0;
	add_to_tsl(&Table_Schema_List, newtable);
	
	printf("creating table...\n");
	
}


int db_init_main() {
	//list to keep track of files where data is saved	
	init_fpl(&TableSchema_File_Ptr_List);
	init_fpl(&TableData_File_Ptr_List);

	//list to keep track of live tables and data
	init_btrl(&Root_Node_List);
	init_tsl(&Table_Schema_List);
	

	create_table_flag = 0;
	return 0;

}
int db_main () {

	if(create_table_flag){
		create_table_flag = 0;
		create_table();
	}
	return 0;
}

