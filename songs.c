#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "songs.h"

struct song_node *new_node(char *artist, char *title) {

    struct song_node *new;

    new = malloc( sizeof(struct song_node) );
    strncpy(new->title, title, sizeof(new->title)-1);
    strncpy(new->artist, artist, sizeof(new->artist)-1);
    new->next = NULL;
    return new;
}

void print_song(struct song_node *x) {
    printf("[%s: %s] ", x -> artist, x -> title);
    return;
}

// insert nodes at the front
struct song_node *insert_front(struct song_node *p, char *artist, char *title) {
    struct song_node *front = new_node(artist, title);
    front -> next = p;
    return front;
}

struct song_node *insert_order(struct song_node *p, char *artist, char *title) {
    struct song_node *new = new_node(artist, title);
    if (p == NULL) {
        return new;
    }
    else if (strcmp(p -> artist, artist) > 0) {
        new -> next = p;
        return new;
    }
    else if (strcmp(p -> artist, artist) == 0 && strcmp(p -> title, title) > 0) {
        new -> next = p;
        return new;
    }
    
    p -> next = insert_order(p -> next, artist, title);
    return p;
}

// print the entire list
void print_list(struct song_node *p) {
    if (p == NULL) {
        printf("No songs :(");
        return;
    }
    struct song_node *curr = p;
    while (curr != NULL) {
        print_song(curr);
        curr = curr -> next;
    }
    return;
}

// find and return a pointer to a node based on artist and song name
struct song_node *find_song(struct song_node *p, char *artist, char *title) {
    if (p == NULL) {
        return NULL;
    }
    while (p != NULL) {
        if (!strcmp(p -> artist, artist) && !strcmp(p -> title, title)) {
            return p;
        }
        p = p -> next;
    }
    return NULL;
}

// find and return a pointer to the first song of an artist based on artist name
struct song_node *find_first_song(struct song_node *p, char *artist) {
    if (p == NULL) {
        return NULL;
    }
    while (p != NULL) {
        if (!strcmp(p -> artist, artist)) {
            return p;
        }
        p = p -> next;
    }
    return NULL;
}


// Return a pointer to random element in the list.
struct song_node *random_song(struct song_node *p) {
    struct song_node *res = p;
    int n = 1;
    for (n = 2; p != NULL; n++) {

        if (rand() % n == 0) {
            res = p;
        }
        p = p -> next;
    }
    return res;
}

// remove a single specified node from the list
struct song_node *remove_song(struct song_node *p, char *artist, char* title) {
    if (p == NULL) {
        return NULL;
    }
    else if (!strcmp(p -> artist, artist) && !strcmp(p -> title, title)) {
        struct song_node *save = p -> next;
        free(p);
        return p -> next;
    }
    p -> next = remove_song(p -> next, artist, title);
    return p;
}

// free the entire list
struct song_node *free_songs(struct song_node *p) {
    if (p -> next != NULL) {
        free_songs(p -> next);
    }
    free(p);
    return NULL;
}
