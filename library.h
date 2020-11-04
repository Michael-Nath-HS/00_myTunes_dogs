#include "songs.h"
struct library
{
    // defines an array of 27 alphabetically categorized albums,
    // which contain songs that are alphabetically categorized
    struct song_node *albums[27];
};

struct library *add_song(struct library *library, struct song_node *song);
struct library *create_library();
struct song_node *get_song(struct library *library, char *title, char *artist);
void print_songs_by_letter(struct library *library, char letter);
void print_songs_by_artist(struct library *library, char *artist);
struct song_node *get_first_song_by_artist(struct library *library, char *artist);