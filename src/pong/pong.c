#include "pong.h"

extern Keyboard keyboard;

static u_64t time_diff(u_64t old, u_64t new) {
    if (new >= old) {
        return new - old;
    } else {
        return (0xFFFFFFFF - old + 1 + new);
    }
}

static void reset_positions(Pong* game) {
    game->ball.x = SCREEN_WIDTH / 2;
    game->ball.y = SCREEN_HEIGHT / 2;
    game->ball_v.x = BALL_VX_0;
    game->ball_v.y = BALL_VY_0;

    game->p1_paddle.x = P1_PADDLE_X;
    game->p2_paddle.x = P2_PADDLE_X;
    game->p1_paddle.y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    game->p2_paddle.y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    game->ticks = timer_get();
}

static void reset_scores(Pong* game) {
    game->p1_score = 0;
    game->p2_score = 0;
}

static void reset(Pong* game) {
    reset_scores(game);
    game->state = PLAYING;
    reset_positions(game);
}

static void update_ball(Pong* game, u_64t dt) {
    game->ball.x += game->ball_v.x * dt;
    game->ball.y += game->ball_v.y * dt;
    /* collision with bottom */
    if (game->ball.y + BALL_RAD >= SCREEN_HEIGHT) {
        game->ball_v.y *= -1;
        game->ball.y = (SCREEN_HEIGHT - BALL_RAD) -
                       (game->ball.y - (SCREEN_HEIGHT - BALL_RAD));
    }

    /* collision with top */
    if (game->ball.y <= BALL_RAD) {
        game->ball_v.y *= -1;
        game->ball.y = BALL_RAD + (BALL_RAD - game->ball.y);
    }

    /* collision with left */
    if (game->ball.x <= P1_COLL_X) {
        game->ball_v.x *= -1;
        game->ball.x = P1_COLL_X + (P1_COLL_X - game->ball.x);
    }

    /* collision with right */
    if (game->ball.x >= P2_COLL_X) {
        game->ball_v.x *= -1;
        game->ball.x = P2_COLL_X - (game->ball.x - P2_COLL_X);
    }
}

static void update_game(Pong* game, u_64t ticks) {
    /* get time difference */
    u_64t dt = time_diff(game->ticks, ticks);
    /* update time */
    game->ticks = ticks;

    /* update ball velocity */
    update_ball(game, dt);
}

static void render(Pong* game) {
    // /* draw scores */
    draw_dec(SCREEN_WIDTH / 3, 10, game->p1_score, WHITE);
    draw_dec(2 * SCREEN_WIDTH / 3, 10, game->p2_score, WHITE);
    /* draw ball */
    draw_circle(game->ball.x, game->ball.y, BALL_RAD, WHITE);

    /* draw paddles */
    draw_rectangle(game->p1_paddle.x, game->p1_paddle.y, PADDLE_WIDTH,
                   PADDLE_HEIGHT, WHITE);
    draw_rectangle(game->p2_paddle.x, game->p2_paddle.y, PADDLE_WIDTH,
                   PADDLE_HEIGHT, WHITE);

    draw();
}

void create_game(Pong* game) {
    reset_positions(game);
    reset_scores(game);
    game->state = START_SCREEN;
}

void event_loop(Pong* game) {
    while (game->state != ENDED) {
        update_game(game, timer_get());
        render(game);
    }
}

// for (;;) {
//     if (keyboard.keys[KEY_DOWN]) draw_string(50, 60, "DOWN", WHITE);
//     if (keyboard.keys[KEY_UP]) draw_string(50, 50, "UP", WHITE);
//     if (keyboard.keys[KEY_W]) draw_string(30, 50, "W", WHITE);
//     if (keyboard.keys[KEY_S]) draw_string(30, 60, "S", WHITE);
//     if (keyboard.keys[KEY_ESC]) draw_string(60, 60, "ESC", WHITE);
//     if (keyboard.keys[KEY_R]) draw_string(60, 50, "R", WHITE);

//     draw_hex(10, 10, (u_32t)timer_get(), timer_get() % 256);

//     draw();
// }