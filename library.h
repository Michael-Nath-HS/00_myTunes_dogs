#include "songs.h"
struct library
{
    // defines an array of 27 alphabetically categorized albums,
    // which contain songs that are alphabetically categorized
    struct song_node* albums[27];
};

struct library * add_song(struct library * library, struct song_node * song);
struct library * create_library();