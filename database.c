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

int db_main(){
	return 0;
}

int db_init_main(){

	init_fpl(&TableSchema_File_Ptr_List);
	init_fpl(&TableData_File_Ptr_List);

	init_btrl(&BTree_Ptr_List);

	return 0;
}
