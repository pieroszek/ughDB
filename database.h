#ifndef UGH_H
#define UGH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ORDER 200
//4kb == 4096


/* structts */

typedef struct {
	FILE ** file_ptr_list;
	int counter;
	int len;
} FILE_PTR_LIST; //for keeping track of files

typedef struct {
    char column_name[50];
    int column_type;    // INT, VARCHAR, FLOAT, etc.
    int column_size;
    int column_offset;  // Where this column is within the row
} Column;

typedef struct {
	char data[256]; //generic ahh blob of data
} row; 
typedef struct {
    char * table_name;
    Column columns[20];
    long root_node_offset;  // Where the B-Tree root lives
    int column_count;
} TableSchema; //table meta data

typedef struct {
	int keys[2 * ORDER - 1];
	long data_pointers[2 * ORDER -1];
	long child_pointers[2 * ORDER];
	int key_i;
	int is_leaf;
} BTree_Node;

typedef struct {
	BTree_Node ** List;
	int counter;
	int len;
} BTree_Root_List; //keep track of btree's with root nodes




typedef struct {
	TableSchema ** List;
	int counter;
	int len;
} TableSchema_List;


/**/

/**/ 
int create_table_flag;
size_t name_table_flag;

void add_to_fpl(FILE_PTR_LIST * fpl, FILE * file_ptr);
void init_fpl(FILE_PTR_LIST * fpl);

void init_btrl(BTree_Root_List * btrl);
void add_to_btrl(BTree_Root_List * btrl, BTree_Node * node);

void create_row(TableSchema* schema, void* input_data, row* row);

void init_tsl(TableSchema_List * tsl);
void add_to_tsl(TableSchema_List * tsl, TableSchema * table_schema); 

BTree_Node * create_btree_node();
void create_table();

int db_main ();
int db_init_main();

#endif
