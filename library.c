#include "library.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
// get_index_from_author_name: helper function that gets the slot in the library corresponding to the first letter of the artist's name
int get_index_from_author_name(char *artist)
{
    // convert uppercase letters to lowercase
    char first_letter = tolower(artist[0]);
    // init an array of size 27 (26+ 1 for terminating '\0')
    int i;
    char is_alpha = 0;
    // run a for loop to check where this thingy is
    for (i = 0; i < 26; i++)
    {
        if (alphabet[i] == first_letter)
        {
            return i;
        }
    }
    return 26;
}

struct song_node *get_library_slot(struct library *library, char *artist)
{
    int index;
    // get slot of the incoming song
    index = get_index_from_author_name(artist);
    // retreive the linked list corresponding to that slot
    struct song_node *cur_list;
    cur_list = library->albums[index];
    return cur_list;
};

// add_song: takes a pointer to a song and appropriately adds it to the music library
struct library *add_song(struct library *library, struct song_node *song)
{
    struct song_node *cur_list = get_library_slot(library, song->artist);
    struct song_node *retreived_song;
    // use the insert_order function to add the song to the specific linked_list
    insert_order(cur_list, song->title, song->artist);
    return library;
};

struct song_node *get_song(struct library *library, char *title, char *artist)
{
    struct song_node *cur_list = get_library_slot(library, artist);
    struct song_node *retreived_song;
    retreived_song = find_song(cur_list, artist, title);
    return retreived_song;
}

struct song_node *get_first_song_by_artist(struct library *library, char *artist)
{
    struct song_node *cur_list = get_library_slot(library, artist);
    struct song_node *retreived_song;
    retreived_song = find_first_song(cur_list, artist);
    return retreived_song;
}

void print_songs_by_letter(struct library *library, char letter)
{
    char str_letter[1];
    str_letter[0] = letter;
    int index = get_index_from_author_name(str_letter);
    struct song_node *songs;
    songs = library->albums[index];
    print_list(songs);
}

void print_songs_by_artist(struct library *library, char *artist)
{
    struct song_node *cur_list = get_library_slot(library, artist);
    while (cur_list)
    {
        cur_list = find_first_song(cur_list, artist);
        if (cur_list)
        {
            print_song(cur_list);
        }
    }
}

void print_library(struct library *library)
{
    int i;
    for (i = 0; i < 27; i++)
    {
        if (i == 26)
        {
            printf("Misc:\n\n");
        }
        else
        {
            printf("%c:\n\n", alphabet[i]);
        }
        print_list(library->albums[i]);
    }
}

void shuffle_songs(struct library *library)
{
}