#include <string.h>
#include "database.h"
#include "file_io.c"
//echo "database.c" | entr -r sh -c 'clear && gcc -std=c99 -Wall -Werror --save-temps -fsanitize=address main.c -o ughDB && ./ughDB'
BTree_Root_List BTree_Ptr_List;
TableSchema_List TableSchema_Ptr_List;

void init_fpl(FILE_PTR_LIST * fpl){
	fpl->counter = 0;
	fpl->len = 5;
	fpl->file_ptr_list = malloc(sizeof(FILE*) * fpl->len);
	return;
}

void init_tsl(TableSchema_List * tsl){
	tsl->len = 5;
	tsl->counter = 0;
	tsl->List = malloc(sizeof(TableSchema*) * tsl->len);

}
void init_btrl(BTree_Root_List * btrl){
	btrl->counter = 0;
	btrl->len = 5;
	btrl->List = malloc(sizeof(BTree_Node*) * btrl->len); //cookie crumb
	return;
}


Column * init_col(char * id, col_type_enum type, int size, int offset){
	Column * col = malloc(sizeof(Column));
	col->column_size = size;
	col->column_type = type;
	col->column_offset = offset;
	col->column_name = malloc(sizeof(strlen(id)) + 1);
	strcpy(col->column_name, id);
	return col;
}


void init_table_schema(TableSchema * ts, char * table_name){
	ts->column_count = 1;
	ts->column_len = 5;
	Column * key_col = init_col("key", 0, sizeof(int), 0);
	ts->table_name = table_name;
	ts->columns = malloc(sizeof(Column*) * ts->column_len);
	ts->columns[ts->column_count] = key_col;
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

TableSchema* find_table_by_name(char * table_name, TableSchema_List * tsl){
	if(tsl->counter == 0){
		printf("no tables exist");
		return 0x0; 
	}
	if(tsl->counter == 1 && tsl->List[0]->table_name == table_name){
		return tsl->List[0];
	}
	for(int i = 0; i <= tsl->len; i++){
		if(tsl->List[i]->table_name == table_name){
			return tsl->List[i];
		}
	}
	return 0x0;
}

void show_table(char * table_name){
	TableSchema * table = find_table_by_name(table_name,&TableSchema_Ptr_List);
	printf("\n%s\n", table_name);
	for(int i = 0; i <= table->column_count; i++){
		printf("%s ||", table->columns[i]->column_name);
	}
	show_table_flag = 0;
	return;
}

void create_column(char * name, char * type, char * table_name){
	create_column_flag = 0;
	/* parse type */
	col_type_enum type_param = EMPTY;
	if(strcmp(type, "int") == 0){
		type_param = 0;
	}

	/* get table from table name */
	TableSchema * table = find_table_by_name(table_name, &TableSchema_Ptr_List);
	if(!table){ 
		return; //table not found
	}

	/* create column with the name */
	Column * new_col = init_col(name, type_param,  table->column_count , 0);
	if(!new_col){
		return;
	}
	
	/* modify table schema for the new column */
	if(table->column_count == (table->column_len - 1)){ //check for bounds
		return; // should add resize logic here 
	}
	table->column_count++;
	table->columns[table->column_count] = new_col;

	
	return;
}

void create_table(char * table_name){
	create_table_flag = 0;
	printf("creating table...\n");
	/* create table schema */
	TableSchema * newtable_ptr = malloc(sizeof(TableSchema));
	init_table_schema(newtable_ptr, last_command);
	newtable_ptr->root_node_offset = 0;

	/* create btree root node to start the tree */
	BTree_Node * new_root_node = create_btree_node(0);
	

	/* store btree on ptr list */ 
	BTree_Ptr_List.List[BTree_Ptr_List.counter] = new_root_node;
	newtable_ptr->btree_file_index = BTree_Ptr_List.counter;
	BTree_Ptr_List.counter++;

	/* create btree file to store btree */
	int err_check = create_btree_file();
	if(err_check){
		printf("\n file_create_err \n");
	}
	
	/* add btree node to file and store offset in ts*/
	long * root_offset = malloc(sizeof(long));
	save_node(new_root_node, TableData_File_Ptr_List.file_ptr_list[newtable_ptr->btree_file_index], root_offset, 1);
	newtable_ptr->root_node_offset = *root_offset;

	printf("table created\n");
	return;
}


int db_main(){
	if(create_table_flag){
		create_table(last_command);//last command hold table name from usr
	}
	if(create_column_flag){
		create_column(saved_command,last_command,saved_command_2);
		// params ( col name , col type , table to add col to ) 
	}
	if(show_table_flag){
		show_table(last_command); //last command holds table name from usr
	}
	return 0;
}

int db_init_main(){
	create_table_flag = 0; //0 is false, 1 is triggers create_table()	
	create_column_flag = 0; //0 is false, 2 and 1 are states
	show_table_flag = 0; // 0 false, 1 see table

	init_fpl(&TableSchema_File_Ptr_List);
	init_fpl(&TableData_File_Ptr_List);

	init_btrl(&BTree_Ptr_List);
	init_tsl(&TableSchema_Ptr_List);
	return 0;
}
