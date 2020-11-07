struct song_node {
    char title[100];
    char artist[100];
    struct song_node *next;
};

struct song_node *new_node(char *artist, char *title);
void print_song(struct song_node *x);
void print_list(struct song_node *p);
struct song_node *insert_front(struct song_node *p, char *artist, char *title);
struct song_node *insert_order(struct song_node *p, char *artist, char *title);
struct song_node *find_song(struct song_node *p, char *artist, char *title);
struct song_node *find_first_song(struct song_node *p, char *artist);
struct song_node *random_song(struct song_node *p);
struct song_node *remove_song(struct song_node *p, char *artist, char* title);
struct song_node *free_songs(struct song_node *p);
