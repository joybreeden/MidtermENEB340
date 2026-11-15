#include <stddef.h>
#include <stdio.h>
 #ifndef MUSICDB_H
#define MUSICDB_H

typedef struct Song    Song;
typedef struct Artist  Artist;
typedef struct MusicDB MusicDB;          /* you define this one, in musicdb.c */
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
typedef int (*song_pred)(const Song *s, const void *key);  /* non-zero = match */
 
//void test_top_artist(const MusicDB *db);
//void test_db_get(const MusicDB *db, size_t i);
MusicDB      *db_create(void);
void          db_destroy(MusicDB *db);
int           db_load(MusicDB *db, const char *dir);
size_t        db_song_count(const MusicDB *db);
size_t        db_artist_count(const MusicDB *db);
const Song   *db_get(const MusicDB *db, size_t i);
int           db_push(MusicDB *db, const char *title, const char *artist,
                      double rating, int year, unsigned long num_rated);
void          db_disp(const MusicDB *db, FILE *out, size_t lim);
size_t        db_search(const MusicDB *db, song_pred pred, const void *key,
                        const Song ***out);
void          db_sort(MusicDB *db, int card);
size_t        db_count_decade(const MusicDB *db, int start, const Song **best);
const Artist *db_top_artist(const MusicDB *db);
#endif