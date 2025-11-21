#include "file_io.h"
#include "database.h"
// list to keep track of file pointers
FILE_PTR_LIST TableSchema_File_Ptr_List;
FILE_PTR_LIST TableData_File_Ptr_List;
// "./data" where files stored

void check_data_dir(){
        system("mkdir -p data");
}

/*
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
*/
