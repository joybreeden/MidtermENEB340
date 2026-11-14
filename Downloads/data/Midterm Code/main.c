#include "musicdb.h"


int main(){
    


    MusicDB *testDB = db_create();
    printf("db Created successfully\n");
    if(!db_load(testDB, "data")){
        printf("data loaded succesfully\n");
    }else{
        printf("data failed to load");
    }
    
    db_push(testDB, "Tmary had a little lamb", "Folk", 3.65, 2009, 2493);
    db_push(testDB, "Twinkle Twinkle", "Unknown", 3.65, 2009, 2493);
    if(!db_push(testDB, "ABCs", "Unknown", 4.89, 2000, 20930493)){
        printf("push succeeded\n");
        FILE *file = fopen("test.txt","w");
        if(file == NULL){
            printf("File failed to open");
            return 1;
        }   
        db_sort(testDB, 3);
        db_disp(testDB,file,0 );
        printf("printed to file\n");
        fclose(file);
    }else{
        printf("push failed\n");
    }
    
    printf("Num Songs %d, Num Artitists %d\n",db_song_count(testDB),db_artist_count(testDB));
    printf("Num between 2000 and 2009: %d\n",db_count_decade(testDB,2000,NULL));
    //test_db_get(testDB, 0);
    //test_top_artist(testDB);
}