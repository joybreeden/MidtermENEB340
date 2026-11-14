#include "musicdb.h"


int main(){
    FILE *file = fopen("test.txt","w");
    if(file == NULL){
        printf("File failed to open");
        return 1;
    }


    MusicDB *testDB = db_create();
    printf("db Created successfully\n");
    db_push(testDB, "Twinkle Twinkle", "Unknown", 3.65, 2009, 2493);
    if(!db_push(testDB, "ABCs", "Unknown", 4.89, 2000, 20930493)){
        printf("push succeeded\n");
        db_disp(testDB,file,0 );
        printf("printed to file\n");
    }else{
        printf("push failed\n");
    }
    fclose(file);
    printf("Num Songs %d, Num Artitists %d\n",db_song_count(testDB),db_artist_count(testDB));
    printf("Num between 2000 and 2009: %d",db_count_decade(testDB,2000,NULL));
}