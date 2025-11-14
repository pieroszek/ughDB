#include <stdlib.h>
#define ORDER 200
//4kb == 4096

size_t create_table_flag;
size_t name_table_flag;

typedef struct {
    char column_name[50];
    int column_type;    // INT, VARCHAR, FLOAT, etc.
    int column_size;
    int column_offset;  // Where this column is within the row
} Column;

typedef struct {
    char * table_name;
    Column columns[20];
    long root_node_offset;  // Where the B-Tree root lives
    int column_count;
} TableSchema;

typedef struct {
	int keys[2 * ORDER - 1];
	long data_pointers[2 * ORDER -1];
	long child_pointers[2 * ORDER];
	int key_i;
	int is_leaf;
} BTree_Node;


typedef struct {
	BTree_node ** List;
	int root_list_counter;
	int root_list_length; 
} BTree_Root_List;

typedef struct {
	TableSchema ** List;
	int table_list_counter;
	int table_list_length;
} TableSchema_List;




BTree_Node * create_btree_node();
TableSchema * create_table();


int db_main ();

#endif
