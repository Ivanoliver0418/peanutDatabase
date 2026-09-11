#include <stdio.h>
#include <string.h>

#define MAX_GAMES 100
#define MAX_MOVES 10000
#define MAX_NOTATION_LENGTH 15

typedef enum {
    PLAYER_WHITE,
    PLAYER_BLACK
} Player;

typedef enum {
    GAME_ACTIVE,
    GAME_COMPLETED
} GameStatus;

typedef struct {
    int id;

    long initial_clock_ms;
    long increment_ms;

    GameStatus status;

    char result[8];
} Game;

typedef struct {
    int game_id;

    int ply;

    Player player;

    char notation[16];

    long white_clock_ms;
    long black_clock_ms;

    long press_elapsed_ms;
} Move;

typedef struct {
    Game games[MAX_GAMES];
    
    size_t game_count;

    Move moves[MAX_MOVES];

    size_t move_count;

    int active_game_id;
} Database;

/* Prints the peanutDatabase prompt. */
 static void print_prompt(void) {
     printf("peanutDB> ");
     fflush(stdout);
 }

/* Converts a player enum to text. */

static const char *player_name(Player player) {
    
    return player == PLAYER_WHITE ? "White" : "Black";

}

/* Converts text into a player enum. */
static int parse_player(const char *text, Player player) {
    
    if (strcmp(text, "white") == 0) {
        
        *player = PLAYER_WHITE;
        
        return 0;
    }

    if (strcmp(text, "black") == 0) {
        
        *player = PLAYER_BLACK;
        
        return 0;
    }

    return -1
}

/* Prints milliseconds as MM:SS:mmm. */

static void print_clock(long milliseconds) {

    long minutes;
    long seconds;
    long millis;

    minutes = milliseconds / 60000;

    seconds = (milliseconds / 1000) % 60;

    millis = milliseconds % 1000;

    printf("%02ld:%02ld.%03ld", minutes, seconds, millis);
}

static Game *find_game(Database *db, int game_id) {

    size_t i;

    for (i = 0; i < db->game_count; i++) {

        if (db->games[i].id == game_id) {

            return &db->games[i];
        }
    }

    return NULL;
}

int main(void) {
    
    return 0;
}
