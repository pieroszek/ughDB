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
	btrl->List = malloc(sizeof(BTree_Node*) * btrl->len); //cookie crumb
	return;
}


Column * init_col(char * id, int type, int size, int offset){
	Column * col = malloc(sizeof(Column));
	col->column_size = size;
	col->column_type = type;
	col->column_offset = offset;
	col->column_name = malloc(sizeof(strlen(id)) + 1);
	col->column_name = id;
	return col;
}
	

void init_table_schema(TableSchema * ts){
	Column * key_col = init_col("key", 0, sizeof(int), 0);
	ts->table_name = "new_table";
	ts->columns = malloc(sizeof(Column)); // <<------ fml
	ts->columns = key_col;
	return;
}

BTree_Node * create_btree_node(int is_leaf){
	BTree_Node * node = malloc(sizeof(BTree_Node));
	node->key_i = -1; // -1 for empty
	node->is_leaf = is_leaf; // 0 for false, 1 for true
	return node;
}

void add_to_fpl(FILE_PTR_LIST * fpl, FILE * file_ptr){
	/* size check */
	if( (fpl->counter + 1) == (fpl->len) ) {
		return;
	}
	
	/* */
	fpl->file_ptr_list[fpl->counter] = file_ptr;
	fpl->counter++;	
	return;
}

void create_table(){
	printf("creating table...\n");
	/* create table schema */
	TableSchema * newtable_ptr = malloc(sizeof(TableSchema));
	init_table_schema(newtable_ptr);
	newtable_ptr->root_node_offset = 0;

	/* create btree root node to start the tree */
	BTree_Node * new_root_node = create_btree_node(0);
	

	/* store btree on ptr list */ 
	BTree_Ptr_List.List[BTree_Ptr_List.counter++] = new_root_node;
	BTree_Ptr_List.counter++;

	/* create btree file to store btree */
	int err_check = create_btree_file();
	if(err_check){
		printf("\n file_create_err \n");
	}
	
	/* add btree node to file and store offset in ts*/
	

	printf("table created\n");
	return;
}


int db_main(){
	if(create_table_flag){
		create_table();
	}
	return 0;
}

int db_init_main(){
	create_table_flag = 0; //0 is false, 1 is triggers create_table()	

	init_fpl(&TableSchema_File_Ptr_List);
	init_fpl(&TableData_File_Ptr_List);

	init_btrl(&BTree_Ptr_List);

	return 0;
}
