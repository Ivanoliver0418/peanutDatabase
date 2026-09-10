#define MAX_GAMES 100
#define MAX_MOVES 10000

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

typedef enum {
    PLAYER_WHITE,
    PLAYER_BLACK,
} Player;

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


