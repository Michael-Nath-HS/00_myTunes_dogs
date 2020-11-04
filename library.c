#include "library.h"
#include <ctype.h>
char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
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
    if (!is_alpha)
    {
        return 26;
    }
}

// add_song: takes a pointer to a song and appropriately adds it to the music library
struct library *add_song(struct library *library, struct song_node *song)
{
    int index;
    // get slot of the incoming song 
    index = get_index_from_author_name(song->artist);
    // retreive the linked list corresponding to that slot
    struct song_node *cur_list;
    cur_list = library->albums[index];
    // use the insert_order function to add the song to the specific linked_list
    insert_order(cur_list, song->title, song->artist);
};