#include "songs.h"
struct library
{
    // defines an array of 27 alphabetically categorized albums,
    // which contain songs that are alphabetically categorized
    struct song_node *albums[27];
};

struct library *add_song(struct library *library, struct song_node *song);
struct library *create_library();
void get_song(struct library *library, char *title, char *artist);
void print_songs_by_letter(struct library *library, char letter);
void print_songs_by_artist(struct library *library, char *artist);
struct song_node *get_first_song_by_artist(struct library *library, char *artist);
struct library *free_library(struct library *library);
struct library *delete_song(struct library *library, char *artist, char *title);
void shuffle_songs(struct library *library, int num_songs);
void print_library(struct library *library);
