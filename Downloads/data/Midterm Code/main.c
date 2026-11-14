#include "musicdb.h"


int main(){
    FILE *file = fopen("test.txt","w");
    if(file == NULL){
        printf("File failed to open");
        return 1;
    }


    MusicDB *testDB = db_create();
    printf("db Created successfully\n");
    db_push(testDB, "Twinkle Twinkle", "Unknown", 3.65, 2008, 2493);
    if(!db_push(testDB, "ABCs", "Unknown", 4.89, 1999, 20930493)){
        printf("push succeeded\n");
        db_disp(testDB,file,0 );
        printf("printed to file");
    }else{
        printf("push failed");
    }
    fclose(file);

}