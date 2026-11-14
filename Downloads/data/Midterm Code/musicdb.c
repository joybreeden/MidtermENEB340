#include "musicdb.h"
#include <string.h>
#include <stdlib.h>

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
    return malloc(sizeof(MusicDB));//creates new MusicDB object and returns a poihnter to it
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
int db_load(MusicDB *db, const char *dir){//Reads songs.txt, artists.txt, year.txt, ratings.txt and people_rated.txt TODO: program

}
size_t        db_song_count(const MusicDB *db){// returns the number of songs in the database TODO: Test
    return db->numSongs;
}
size_t        db_artist_count(const MusicDB *db){//returns the number of songs in the database TODO: Test
    return db->numArtists;
}
const Song  *db_get(const MusicDB *db, size_t i){//returns the song at position i if it exists otherwise returns null TODO: test
    if(i < db->numSongs){
        return db->songs[i];
    }
    return NULL;
}
int db_push(MusicDB *db, const char *title, const char *artist, double rating, int year, unsigned long num_rated){// adds a song to the last position of the database TODO: finish programing
    if(db == NULL || title == NULL || artist == NULL){
        return -1;
    }
    Song song = {
            .rating = rating,
            .year = year,
            .num_rated = num_rated,
            .id = db->numSongs  
        };
    song.title = malloc(sizeof(artist));
    strcpy(song.title, artist);
    int duplicate = 0;
    for(int i = 0; i< db->numArtists; i++){
        if(!strcmp(db->artists[i]->name, artist) ){
            db->artists[i]->songs[db->artists[i]->n_songs] =&song;
            db->artists[i]->n_songs++;
            song.artist = db-> artists[i];
            duplicate = 1;
        }
    }
    if(!duplicate){
        Artist art = {
            .name = artist,
            .n_songs = 0,
            .cap = 5,
            .songs = malloc(art.cap*sizeof(Song))
        };
        db->artists[db->numArtists] = &art;
    }
    db->songs[db->numSongs] = &song;
    db->numSongs++;
    return 0;
}
void db_disp(const MusicDB *db, FILE *out, size_t lim){// prints to file Each row: "%-35.35s %-25.25s %-5d %-8.2f %lu\n" (title, artist name, year, rating, number of raters). TODO:program 
    if(out == NULL){
        return;
    }
    fprintf(out,"%-35s %-25s %-5s %-8s %s\n","Song Title", "Artist", "Year", "Rating", "People Rated" );
    if(lim == 0){
        for(int i = 0; i< db->numSongs; i++){
            fprintf(out,"%-35.35s %-25.25s %-5d %-8.2f %lu\n",db->songs[i]->title,db->songs[i]->artist->name,db->songs[i]->year,db->songs[i]->rating,db->songs[i]->num_rated);

        }
    }else{
        for(int i = 0;( i< db->numSongs) &&(i< lim); i++){
            fprintf(out,"%-35.35s %-25.25s %-5d %-8.2f %lu\n",db->songs[i]->title,db->songs[i]->artist->name,db->songs[i]->year,db->songs[i]->rating,db->songs[i]->num_rated);
        }
    }
}
size_t db_search(const MusicDB *db, song_pred pred, const void *key, const Song ***out){//determines which songs match key based on function pred which is defined by someone else TODO: program

}
void db_sort(MusicDB *db, int card){// sort by num_rated decending then rating decending then id acending TODO: Program

}
/* PTR-ONLY */
size_t db_count_decade(const MusicDB *db, int start, const Song **best){//count the number of songs made from 1960 to 1969. if best isnt null have it point to song with highest rating 

}
/* PTR-ONLY */
const Artist *db_top_artist(const MusicDB *db){//returns NULL if db is empty otherwise returns artist with most songs 

}

