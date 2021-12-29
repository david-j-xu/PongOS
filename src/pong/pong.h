/*
 *  Pong Game
 */

#pragma once

#include "../drivers/font.h"
#include "../drivers/keyboard.h"
#include "../drivers/pit.h"
#include "../drivers/screen.h"
#include "../drivers/utils.h"
#include "../kernel/kernel.h"

#define START_SCREEN 0
#define PLAYING 1
#define ENDED 2
#define PAUSED 5
#define P1_WIN 3
#define P2_WIN 4
#define INSTRUCTIONS 6
#define THRESHOLD_SCORE 5

#define PADDLE_WIDTH 2
#define PADDLE_HEIGHT 40
#define BALL_RAD 4
#define P1_PADDLE_X 3
#define P2_PADDLE_X (SCREEN_WIDTH - 5)
#define PADDLE_MIN_Y (0)
#define PADDLE_MAX_Y (SCREEN_HEIGHT - PADDLE_HEIGHT)
#define PADDLE_VEL 5
#define P1_COLL_X (P1_PADDLE_X + 2)
#define P2_COLL_X (P2_PADDLE_X)

#define BALL_VX_0 -4
#define BALL_VY_0 4

#define G_ENDED(x) ((x) >= 2)

typedef struct Pos {
    int x;
    int y;
} Pos;

typedef struct Pong {
    u_8t state;
    u_64t ticks;
    u_8t p1_score;
    u_8t p2_score;
    Pos ball;
    Pos ball_v;
    Pos p1_paddle;
    Pos p2_paddle;
} Pong;

/*
 * Create a game
 */
void create_game(Pong* game);

/*
 *  Start a pong event loop
 */
void event_loop(Pong* game);