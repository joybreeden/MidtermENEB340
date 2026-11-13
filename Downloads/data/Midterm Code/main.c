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
