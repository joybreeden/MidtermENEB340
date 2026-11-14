#include "musicdb.h"
#include <string.h>
#include <stdlib.h>

#define debug 1
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
    size_t maxSongs;
    size_t maxArtists;
};

MusicDB *db_create(void){
    MusicDB *db =  malloc(sizeof(MusicDB));
    if(db == NULL){
            return NULL;
        }
    db->maxArtists = 10;
    db->maxSongs = 100;
    db->numArtists = 0;
    db->numSongs = 0;
    db->artists = malloc(db->maxArtists * __SIZEOF_POINTER__);
    db->songs = malloc(db->maxSongs * __SIZEOF_POINTER__);
    if(db->songs == NULL){
            return NULL;
        }
    if(db->artists == NULL){
            return NULL;
        }
    return db;
}
void db_destroy(MusicDB *db){//unassigns and removes all pointers allowing memory to be reused TODO: Test
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
    //FILE *songs
}
size_t db_song_count(const MusicDB *db){// returns the number of songs in the database DONE
    return db->numSongs;
}
size_t db_artist_count(const MusicDB *db){//returns the number of songs in the database DONE
    return db->numArtists;
}
const Song  *db_get(const MusicDB *db, size_t i){//returns the song at position i if it exists otherwise returns null DONE
    if(i < db->numSongs){
        return db->songs[i];
    }
    return NULL;
}
int db_push(MusicDB *db, const char *title, const char *artist, double rating, int year, unsigned long num_rated){//  DONE adds a song to the last position of the database
    if(debug)printf("#artists %d\n", db->numArtists);
    if(db == NULL || title == NULL || artist == NULL){
        return -1;
    }
    if(db->numSongs == db->maxSongs){
        Song ** temp = db->songs;
        db->songs = malloc((db->maxSongs + 100)* __SIZEOF_POINTER__);
        if(db->songs == NULL){
            db->songs = temp;
            return -1;
        }
        for(int i = 0; i < db->maxSongs; i++){
            db->songs[i] = temp[i];
        }
        db->maxSongs += 100;
        free(temp);
        temp == NULL;
    }
    if(db->numArtists == db-> maxArtists){
        Artist ** temp = db->artists;
        db->artists = malloc((db->maxArtists + 10)* __SIZEOF_POINTER__);
        if(db->artists==NULL){
            db->artists = temp;
            return -1;
        }
        for(int i = 0; i < db->maxArtists; i++){
            db->artists[i] = temp[i];
        }
        db->maxArtists += 10;
        free(temp);
        temp == NULL;
    }
    Song *song = malloc(sizeof(Song));
         if(song == NULL){
            return -1;
        }
            song->rating = rating;
            song->year = year;
            song->num_rated = num_rated;
            song->id = db->numSongs;
  
    song->title = malloc(strlen(title)+1);
    if(song->title == NULL){
            return -1;
        }
    strcpy(song->title, title);
    if(debug)printf("song created successfully\n");
    int duplicate = 0;
    printf("#artists: %d\n", db->numArtists);
    for(int i = 0; i< db->numArtists; i++){
        if(debug)printf("0, ");
        if(!strcmp(db->artists[i]->name, artist) ){
            if(debug)printf("1, ");
            db->artists[i]->songs[db->artists[i]->n_songs] =song;
            if(debug)printf("2, ");
            db->artists[i]->n_songs++;
            if(debug)printf("3, ");
            song->artist = db-> artists[i];
            if(debug)printf("4,\n");
            duplicate = 1;
            if(debug)printf("created artist\n");
        }
    }
    if(debug)printf("checked for duplicates\n");
    if(!duplicate){
        if(debug)printf("0, ");
        Artist * art = malloc(sizeof(Artist));
        if(debug)printf("1, ");
        if(art == NULL){
            return -1;
        }
        if(debug)printf("2, ");
        art->name =malloc(strlen(artist)+1);
        strcpy( art->name , artist);
        if(debug)printf("3, ");
        art->n_songs = 0;
        if(debug)printf("4, ");
        art->cap = 10;
        if(debug)printf("5, ");
        art->songs = malloc(art->cap*sizeof(Song));
        if(debug)printf("6, ");
        if(art->songs == NULL){
        return -1;
        }
        if(debug)printf("7, ");
        art->songs[art->n_songs] = song;
        if(debug)printf("8, ");
        art->n_songs++;
        if(debug)printf("9, ");
        song->artist = art;
        if(debug)printf("10, ");
        db->artists[db->numArtists] = art;
        if(debug)printf("11,\n");
        db->numArtists++;
        if(debug)printf("created artist\n");
    }
    db->songs[db->numSongs] = song;
    db->numSongs++;
    return 0;
}
void db_disp(const MusicDB *db, FILE *out, size_t lim){//DONE
    if(out == NULL){
        if(debug)printf("null file\n");
        return;
    }
    fprintf(out,"%-35s %-25s %-5s %-8s %s\n","Song Title", "Artist", "Year", "Rating", "People Rated" );
    if(debug)printf("printed header\n");
    if(lim == 0){
        for(int i = 0; i< db->numSongs; i++){
            if(debug)printf("1 title %s\n",db->songs[i]->title);
            fprintf(out,"%-35.35s %-25.25s %-5d %-8.2f %lu\n",db->songs[i]->title,db->songs[i]->artist->name,db->songs[i]->year,db->songs[i]->rating,db->songs[i]->num_rated);
            
        }
    }else{

        for(int i = 0;( i< db->numSongs) &&(i< lim); i++){
            if(debug)printf("2 title %s\n",db->songs[i]->title);
            fprintf(out,"%-35.35s %-25.25s %-5d %-8.2f %lu\n",*db->songs[i]->title,db->songs[i]->artist->name,db->songs[i]->year,db->songs[i]->rating,db->songs[i]->num_rated);
        }
    }
}
size_t db_search(const MusicDB *db, song_pred pred, const void *key, const Song ***out){//determines which songs match key based on function pred which is defined by someone else TODO: program
    
}
void db_sort(MusicDB *db, int card){//  TODO: Program
    switch(card){
        case 0://rating descending, then num_rated descending then id accending
             
        break;
        case 1://year ascending, then title ascending (strcmp byte order) then id ascending 

        break;
        case 2://artist name ascending (strcmp), then year descending then id ascending

        break;
        case 3://num_rated descending, then rating descending then id ascending 

        break;
        default: return;
    }


}

/* PTR-ONLY */
size_t db_count_decade(const MusicDB *db, int start, const Song **best){// now ptr only DONE
    size_t count = 0;
    double rating = -10;
    Song **song = db->songs;
    Song **lastSong = db->songs + db->numSongs;
    while(song < lastSong){
        if((*song)->year >= start && (*song)->year <= start + 9){
            if(debug)printf("year: %d, \n",(*song)->year);
            count++;
            if(debug)printf("count: %d,\n",count);
            if(best != NULL && (*song)->rating > rating){
                *best = (*song);
                rating = (*song)->rating;
            }
        }
        song++;
    }
    
    return count;
}
/* PTR-ONLY */
const Artist *db_top_artist(const MusicDB *db){//returns NULL if db is empty otherwise returns artist with most songs DONE
    if(db == NULL || db->numArtists == 0){
        return NULL;
    }
    if(debug)printf("1, ");
    Artist **artist = db->artists;
    if(debug)printf("2, ");
    Artist **lastArtist = db->artists + db->numArtists;
    if(debug)printf("3, ");
    int songs = 0;
    Artist *best = malloc(sizeof(Artist));
    if(debug)printf("4, ");
    while(artist < lastArtist){
        if(debug)printf("5, ");
        if((*artist)->n_songs > songs){
            if(debug)printf("6, ");
            best = (*artist);
            if(debug)printf("7, ");
            songs = (*artist)->n_songs;
        }
        artist++;
    }
    if(debug)printf("%s, %d\n",best->name, best->n_songs);
    return best;
}

/*void test_db_get(const MusicDB *db, size_t i){
    Song *song = db_get(db, i);
    printf("Song Title: %s, Rating: %f, num_rated: %d", song->title,song->rating, song->num_rated);
}*/
/*void test_top_artist(const MusicDB *db){
    Artist *artist = db_top_artist(db);
    printf("Name: %s, nSongs: %d",artist->name,artist->n_songs);
}*/