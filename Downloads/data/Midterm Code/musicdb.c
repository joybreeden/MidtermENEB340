#include "musicdb.h"

struct Song {                  
    float          rating;       
    const Artist  *artist;          
    int            year;            
    char          *title;           
    unsigned long  num_rated;     
    unsigned int   id;              
};  

struct Artist {
    char    *name;      /* owned copy of the name; unique within one MusicDB   */
    size_t   n_songs;   /* number of songs by this artist                      */
    size_t   cap;       /* capacity of the songs array                         */
    Song   **songs;     /* owned array of (non-owning) pointers to the songs   */
};
struct MusicDB{
    Song **songs;
    Artist **artists;
    size_t numSongs;
    size_t numArtists;
};
MusicDB *db_create(void){
    return malloc(1, sizeof(MusicDB));//creates new MusicDB object and returns a poihnter to it
}
void db_destroy(MusicDB *db){//unassigns and removes all pointers allowing memory to be reused 
    if(db == NULL){
        return;
    }if(db->songs != NULL){
        for(int i = 0; i < db->numSongs; i++){
            db->songs[i]->title = NULL;
            db->songs[i]->artist = NULL;
            free(db->songs[i]);
            db->songs[i] = NULL;
        }
        db->songs = NULL;
    }if(db->artists != NULL){
        for(int i = 0; i < db->numArtists; i++){
            db->artists[i]->name = NULL;
            for(int j = 0; j < db->artists[i]->n_songs; j++){
                db->artists[i]->songs[j] = NULL;
            }
            free(db->artists[i]);
            db->artists[i] = NULL;
        }
        db->artists = NULL;
    } 
    db = NULL;
    return;
}
int db_load(MusicDB *db, const char *dir){//Reads songs.txt, artists.txt, year.txt, ratings.txt and people_rated.txt TODO:

}
size_t        db_song_count(const MusicDB *db){// returns the number of songs in the database
    return db->numSongs;
}
size_t        db_artist_count(const MusicDB *db){//returns the number of songs in the database
    return db->numArtists;
}
const Song  *db_get(const MusicDB *db, size_t i){//returns the song at position i if it exists otherwise returns null
    if(i < db->numSongs){
        return db->songs[i];
    }
    return NULL;
}
int db_push(MusicDB *db, const char *title, const char *artist, double rating, int year, unsigned long num_rated){// adds a song to the last position of the database TODO: 
    for(int i = 0; i< db->numArtists; i++){
        Song song = {
            .rating = rating,
            .year = year,
            .num_rated = num_rated,
            .id = db->numSongs  
        };
        song.title = malloc(sizeof(artist));
        strcpy(song.title, artist);
        if(!strcmp(db->artists[i]->name, artist) ){
            db->artists[i]->songs[db->artists[i]->n_songs] ;
        }
    }
}
void db_disp(const MusicDB *db, FILE *out, size_t lim){// prints to file "%-35s %-25s %-5s %-8s %s\n" with the texts Song Title, Artist, Year, Rating, People Rated. Each row: "%-35.35s %-25.25s %-5d %-8.2f %lu\n" (title, artist name, year, rating, number of raters). TODO:


}
size_t db_search(const MusicDB *db, song_pred pred, const void *key, const Song ***out){

}
void db_sort(MusicDB *db, int card){

}
size_t db_count_decade(const MusicDB *db, int start, const Song **best){

}
const Artist *db_top_artist(const MusicDB *db){

}
