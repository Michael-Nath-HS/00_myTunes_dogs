#include "library.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// creating an alphabet array that stores all the lowercase letters in the alphabet
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
// All following library function documentations assumes that a library pointer is passed
// helper function to retreive the linked list of song_nodes depending on the artist.
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
    // use the insert_order function to add the song to the specific linked_list
    library->albums[get_index_from_author_name(song->artist)] = insert_order(cur_list, song->artist, song->title);
    return library;
};

// get_song: takes title and artist, and gets the desired song from the library
void get_song(struct library *library, char *title, char *artist)
{
    struct song_node *cur_list = get_library_slot(library, artist);
    struct song_node *retreived_song;
    retreived_song = find_song(cur_list, artist, title);
    if(retreived_song != NULL) {
        printf("Found song! Song: ");
        print_song(retreived_song);
    } else {
        printf("%s\n", "Could not find song :(");
    }
}

// get_first_song_by_artist: takes an artist's name and gets his or her lexocraphical first song in the library
void *get_first_song_by_artist(struct library *library, char *artist)
{
    struct song_node *cur_list = get_library_slot(library, artist);
    struct song_node *retreived_song;
    retreived_song = find_first_song(cur_list, artist);
    if(retreived_song != NULL) {
        printf("Found song! Song: ");
        print_song(retreived_song);
    } else {
        printf("%s\n", "Could not find song :(");
    }
}

// print_songs_by_letter: prints out all songs under a given album.
void print_songs_by_letter(struct library *library, char letter)
{
    // using a 1 byte char array in order to follow implementation of the get_index_from_author_name helper function
    char str_letter[1];
    str_letter[0] = letter;
    int index = get_index_from_author_name(str_letter);
    struct song_node *songs;
    songs = library->albums[index];
    print_list(songs);
}
// print_songs_by_artist: prints all of the songs by a given artist.
void print_songs_by_artist(struct library *library, char *artist)
{
    struct song_node *cur_list = get_library_slot(library, artist);
    if(find_first_song(cur_list, artist) == NULL) {
        printf("Could not find any song under that artist :(");
        return;
    };
    cur_list = find_first_song(cur_list, artist);
    while(strcmp(cur_list->artist, artist) == 0){
        print_song(cur_list);
        if(cur_list->next == NULL) return;
        cur_list = cur_list->next;
    }
}
// print_library: prints out all the songs in the library
void print_library(struct library *library)
{
    int i;
    for (i = 0; i < 27; i++)
    {
        if (i == 26)
        {
            printf("Misc: ");
        }
        else
        {
            printf("%c: ", alphabet[i]);
        }
        print_list(library->albums[i]);
        printf("\n");
    }
}

// shuffle_songs: takes a number of songs to be printed and shuffles all songs in a library and prints them.
void shuffle_songs(struct library *library, int num_songs)
{
    
    int total = 0;
    int i = 26;
    while(i >= 0){
        if((library->albums)[i] != NULL) total++;
        i--;
    }

    if(total == 0){
        printf("%s\n", "No songs to shuffle :(");
        return;
    }
    struct song_node **my_array = calloc(total, sizeof(void*));

    i = 26;
    int k = 0;
    while(i >= 0){
        if((library->albums)[i] != NULL) {
            my_array[k] = (library->albums)[i];
            k++;
        }
        i--;
    }

    int j = 0;
    for(j = 0; j < num_songs; j++){
        print_song((my_array[rand() % total]));
    }
    free(my_array);
}
// delete_song: deletes a song with specified title and artist from the library
struct library *delete_song(struct library *library, char *artist, char *title)
{
    struct song_node *song_list = get_library_slot(library, artist);
    library->albums[get_index_from_author_name(artist)] = remove_song(song_list, artist, title);
    return library;
}
// free_library: clears the music library, including its embedded song_node linked lists.
struct library *free_library(struct library *library)
{
    int i;
    struct song_node *song_list;
    for (i = 0; i < 27; i++)
    {
        song_list = (library->albums)[i];
        if(song_list == NULL) continue;
        free_songs(song_list);
    }
    free(library);
    return NULL;
}

struct library *create_library(){
    srand(time(NULL));
    struct library *library_out = malloc(sizeof(struct library));
    int i;
    for(i = 0; i < 27; i++){
        (library_out->albums)[i] = NULL;
    }
    return library_out;
}
