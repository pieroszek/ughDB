#include <string.h>
#include "database.h"

BTree_Node * create_btree_node(){ 
	BTree_Node * new_node = malloc(sizeof(BTree_Node));
	return new_node;
}

TableSchema * create_table(){
	TableSchema * newtable = malloc(sizeof(newtable));
	newtable->table_name = "table";
	newtable->root_node_offset = 0x0;
	newtable->column_count = 0;
	return newtable;
}


int db_main () {
	create_table_flag = 0;

	if(create_table_flag){
		create_table_flag = 0;
		create_table();
	}
	return 0;
}

