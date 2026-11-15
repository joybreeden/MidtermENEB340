#include "musicdb.h"
#include <stdlib.h>
 int pred(const Song *s, const void *key){

        if(s->rating >= 3.70 && s->num_rated >=1000000){
            return 1;
        }else{
            return 0;
        }
        (void)key;
    }
int main(int arg, char*args[]){
    if(arg != 3){
        printf("./musicdb_report data 'student id'");
        return 1;
    }
    printf("ENEB 340 Report\n");
    const char* dir = args[1];
    const int id= atoi(args[2]);
    int b = id % 10;
    int a = (id / 10) % 10;
    int L = (a + b) % 4;
    int D =a % 5;
    int T = b % 5;
    int S = (a + 2 *b) % 4;
    printf("card: L=%d D=%d T=%d S=%d\n",L,D,T,S);
    MusicDB *db = db_create();
    db_load(db, dir);
    Song test;
    size_t size = 0;
    if(size < offsetof(Song, title)+ sizeof(test.title))size = offsetof(Song, title)+ sizeof(test.title);
    if(size < offsetof(Song, artist)+ sizeof(test.artist))size = offsetof(Song, artist)+ sizeof(test.artist);
    if(size < offsetof(Song, year)+ sizeof(test.year))size =offsetof(Song, year)+ sizeof(test.year);
    if(size < offsetof(Song, rating)+ sizeof(test.rating))size = offsetof(Song, rating)+ sizeof(test.rating);
    if(size < offsetof(Song, num_rated)+ sizeof(test.num_rated))size = offsetof(Song, num_rated)+ sizeof(test.num_rated);
    if(size < offsetof(Song, id)+ sizeof(test.id)) size = offsetof(Song, id)+ sizeof(test.id);
    printf("[A] sizeof(Song)=%zu tail_padding=%zu\n",sizeof(Song),sizeof(Song)-size);//Long is only 4 bytes on my system.
    printf("[A] offsets title =%zu artist=%zu year =%zu rating=%zu num_rated=%zu id =%zu\n",offsetof(Song, title), offsetof(Song, artist),offsetof(Song, year),offsetof(Song, rating),offsetof(Song, num_rated),offsetof(Song, id));
    printf("[B] songs=%zu artists=%zu\n",db_song_count(db),db_artist_count(db));
    const Song *s = db_get(db, 0);
    printf("[B] song[0]: %s | %s | %d | %.2f | %lu\n",s->title,s->artist->name,s->year,s->rating,s->num_rated);
    const Artist *art = db_top_artist(db);
    printf("[B] top_artist: %s (%zu songs)\n",art->name,art->n_songs);
    db_push(db,"Exam Song <ID4>","Exam Artist <ID4>",4.10,1985,1250000);
    printf("[C] push1 -> songs=%zu artists=%zu\n",db_song_count(db),db_artist_count(db) );
    db_push(db,"Exam Song <ID4> (Reprise)","The Beatles",3.70,1985,1250000);
    printf("[C] push2 -> songs=%zu artists=%zu\n",db_song_count(db),db_artist_count(db) );
    size_t count = db_count_decade(db,1960,&s);
    printf("[D] Q1 decade=%d count=%zu best_id=%u best_title=%s\n",1960,count,s->id,s->title);
    const Song **ss = NULL;
    int i = db_search(db,pred,&i,&ss);
    printf("[D] Q2 rating>=4.50 rated>=1400000 count=%d first_id=%u last_id=%u\n",i,ss[0]->id,ss[i-1]->id);
    free((void *)ss);
    ss=NULL;
    db_sort(db, S);
    printf("[D] sort card %d top5 ids: %u %u %u %u %u\n", S,db_get(db,0)->id,db_get(db,1)->id,db_get(db,2)->id,db_get(db,3)->id,db_get(db,4)->id);
    db_disp(db,stdout, 3);
    db_destroy(db);
}