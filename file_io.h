#define FILE_IO_H
#ifndef FILE_IO_H

#include <stdio.h>

//check for ./data
void check_data_dir();

// create if not created file
int create_btree_file();
int create_ts_file();

//
void save_schema(TableSchema* schema, FILE* file);


#endif
