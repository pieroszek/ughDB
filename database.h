#ifndef UGH_H
#define UGH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ORDER 200
//4kb == 4096

/* enums */

typedef enum {
	INT = 0,
	FLOAT = 1,
	CHAR = 2,
	STRING = 3,
	EMPTY
} col_type_enum;

/* structts */

typedef struct {
	FILE ** file_ptr_list;
	int counter;
	int len;
} FILE_PTR_LIST; //for keeping track of files

typedef struct {
    char * column_name;
    col_type_enum column_type;    // INT, VARCHAR, FLOAT, etc.
    int column_size;
    int column_offset;  // Where this column is within the row
} Column;

typedef struct {
	char data[256]; //generic ahh blob of data
} row; 

typedef struct {
    char * table_name;
    Column * columns;
    long root_node_offset;  // Where the B-Tree root lives
    int column_count;
    int btree_file_index;
    int schema_file_index;
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
int create_column_flag;
size_t name_table_flag;
char * last_command; //last input from user
char * saved_command; //saved input from user
char * saved_command_2; //second saved input from user

void add_to_fpl(FILE_PTR_LIST * fpl, FILE * file_ptr);
void init_fpl(FILE_PTR_LIST * fpl);

void init_btrl(BTree_Root_List * btrl);
void add_to_btrl(BTree_Root_List * btrl, BTree_Node * node);

void init_tsl(TableSchema_List * tsl);
void add_to_tsl(TableSchema_List * tsl, TableSchema * table_schema); 

BTree_Node * create_btree_node(int is_leaf);

void create_table();
void create_column(char * name, char * type,char * table_name);
void init_table_schema(TableSchema * ts, char * table_name);


void create_row(TableSchema* schema, void* input_data, row* row);

Column * init_col(char * id, col_type_enum type, int size, int offset);

int db_main ();
int db_init_main();

#
