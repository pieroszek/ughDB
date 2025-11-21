#include <string.h>
#include "database.h"
#include "file_io.c"

BTree_Root_List BTree_Ptr_List;

void init_fpl(FILE_PTR_LIST * fpl){
	fpl->counter = 0;
	fpl->len = 5;
	fpl->file_ptr_list = malloc(sizeof(FILE*) * fpl->len);
	return;
}

void init_btrl(BTree_Root_List * btrl){
	btrl->counter = 0;
	btrl->len = 5;
	btrl->List = malloc(sizeof(BTree_Node*) * btrl->len);
	return;
}

Column * init_col(char * id, int type, int size, int offset){
	Column * col = malloc(sizeof(Column*));
	col->column_size = size;
	col->column_type = type;
	col->column_offset = offset;
	col->column_name = malloc(sizeof(id));
	col->column_name = id;
	return col;
}
	

void init_table_schema(TableSchema * ts){
	Column * key_col = init_col("key", 0, sizeof(int), 0);
	ts->table_name = "new_table";
	ts->columns[0] = *key_col;
	return;
}

void create_table(){
	
	/* create table schema */
	TableSchema * newtable_ptr = malloc(sizeof(TableSchema*));
	init_table_schema(newtable_ptr);

	return;
}


int db_main(){
	return 0;
}

int db_init_main(){

	init_fpl(&TableSchema_File_Ptr_List);
	init_fpl(&TableData_File_Ptr_List);

	init_btrl(&BTree_Ptr_List);

	return 0;
}
