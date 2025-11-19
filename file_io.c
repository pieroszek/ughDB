#include "file_io.h"
#include "database.h"
// list to keep track of file pointers
FILE_PTR_LIST TableSchema_File_Ptr_List;
FILE_PTR_LIST TableData_File_Ptr_List;
// "./data" where files stored

void check_data_dir(){
        system("mkdir -p data");
}

int create_btree_file(){
        FILE * file = fopen("data/btree_file.data","ab+");     
        add_to_fpl(&TableData_File_Ptr_List, file);
       
        if(!file) {
                return 1;
        }
        return 0;
}

int create_ts_file(){
        FILE * file = fopen("data/tableschema_file.data","ab+");
        add_to_fpl(&TableSchema_File_Ptr_List, file);
        if(!file) {
                return 1;
        }
        return 0;
}

      
void save_schema(TableSchema* schema, FILE* file) {
    // 1. Write the fixed-size struct first
    fwrite(schema, sizeof(TableSchema), 1, file);
    
    // 2. Then write variable-length data (strings, etc.)
    // Example: if table_name is dynamic, write its length + string
    int name_len = strlen(schema->table_name);
    fwrite(&name_len, sizeof(int), 1, file);
    fwrite(schema->table_name, 1, name_len, file);
    
    // 3. Write column definitions
    for(int i = 0; i < schema->column_count; i++) {
        fwrite(&schema->columns[i], sizeof(Column), 1, file);
    }
}

void load_schema(TableSchema* schema, FILE* file) {
    // 1. Read fixed-size struct first
    fread(schema, sizeof(TableSchema), 1, file);
    
    // 2. Read variable-length data in same order
    int name_len;
    fread(&name_len, sizeof(int), 1, file);
    schema->table_name = malloc(name_len + 1);
    fread(schema->table_name, 1, name_len, file);
    schema->table_name[name_len] = '\0';
    
    // 3. Read columns
    for(int i = 0; i < schema->column_count; i++) {
        fread(&schema->columns[i], sizeof(Column), 1, file);
    }
}

