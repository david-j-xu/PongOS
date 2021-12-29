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
        if (between(game->ball.y, game->p1_paddle.y,
                    game->p1_paddle.y + PADDLE_HEIGHT)) {
            game->ball_v.x *= -1;
            game->ball.x = P1_COLL_X + (P1_COLL_X - game->ball.x);
        } else {
            if (++game->p2_score >= THRESHOLD_SCORE) {
                game->state = P2_WIN;
            } else {
                reset_positions(game);
            }
        }
    }

    /* collision with right */
    if (game->ball.x >= P2_COLL_X) {
        if (between(game->ball.y, game->p2_paddle.y,
                    game->p2_paddle.y + PADDLE_HEIGHT)) {
            game->ball_v.x *= -1;
            game->ball.x = P2_COLL_X - (game->ball.x - P2_COLL_X);
        } else {
            if (++game->p1_score >= THRESHOLD_SCORE) {
                game->state = P1_WIN;
            }
            reset_positions(game);
        }
    }
}

static void update_paddles(Pong* game, u_64t dt) {
    int p1_vel = 0;
    int p2_vel = 0;

    if (check_key(KEY_DOWN)) p2_vel += PADDLE_VEL;
    if (check_key(KEY_UP)) p2_vel -= PADDLE_VEL;
    if (check_key(KEY_W)) p1_vel -= PADDLE_VEL;
    if (check_key(KEY_S)) p1_vel += PADDLE_VEL;

    game->p1_paddle.y =
        clamp(game->p1_paddle.y + p1_vel * dt, PADDLE_MIN_Y, PADDLE_MAX_Y);
    game->p2_paddle.y =
        clamp(game->p2_paddle.y + p2_vel * dt, PADDLE_MIN_Y, PADDLE_MAX_Y);
}

static void update_game(Pong* game, u_64t ticks) {
    /* get time difference */
    u_64t dt = time_diff(game->ticks, ticks);
    /* update time */
    game->ticks = ticks;
    if (game->state == PLAYING) {
        /* update paddles */
        update_paddles(game, dt);
        /* update ball velocity */
        update_ball(game, dt);

        if (check_and_reset_key(KEY_R)) reset(game);
        if (check_and_reset_key(KEY_ESC)) game->state = ENDED;
        if (check_and_reset_key(KEY_P)) game->state = PAUSED;
    } else if (game->state == START_SCREEN) {
        if (check_and_reset_key(KEY_I)) {
            game->state = INSTRUCTIONS;
            return;
        }
        for (int i = 0; i < 128; i++) {
            /* press any key to start playing */
            if (check_and_reset_key(i)) {
                /* begins playing */
                reset(game);
            }
        }
    } else if (game->state == INSTRUCTIONS) {
        if (check_and_reset_key(KEY_ESC)) game->state = START_SCREEN;
    } else if (game->state == PAUSED) {
        if (check_and_reset_key(KEY_R)) reset(game);
        if (check_and_reset_key(KEY_ESC)) game->state = ENDED;
        if (check_and_reset_key(KEY_P)) game->state = PLAYING;
    } else {
        /* either player has won */
        if (check_and_reset_key(KEY_R)) reset(game);
        if (check_and_reset_key(KEY_ESC)) game->state = ENDED;
    }
}

static void render(Pong* game) {
    if (game->state == START_SCREEN) {
        draw_big_string_cr(50, "Pong", 4);
        draw_big_string_c(100, "Press [I] for instructions", WHITE, 1);
        draw_big_string_c(110, "or any other key to play!", WHITE, 1);
    } else if (game->state == PLAYING || game->state == PAUSED) {
        if (game->state == PAUSED) {
            draw_big_string_cr(80, "Paused", 2);
        }
        /* draw scores */
        draw_big_dec_r(SCREEN_WIDTH / 3, 10, game->p1_score, 2);
        draw_big_dec_r(2 * SCREEN_WIDTH / 3, 10, game->p2_score, 2);
        /* draw ball */
        draw_circle(game->ball.x, game->ball.y, BALL_RAD, COLOR(7, 7, 2));

        /* draw paddles */
        draw_rectangle(game->p1_paddle.x, game->p1_paddle.y, PADDLE_WIDTH,
                       PADDLE_HEIGHT, WHITE);
        draw_rectangle(game->p2_paddle.x, game->p2_paddle.y, PADDLE_WIDTH,
                       PADDLE_HEIGHT, WHITE);
    } else if (game->state == P1_WIN) {
        draw_big_string_cr(50, "P1 Wins!", 4);
        draw_big_string_c(100, "[ESC] to exit or", WHITE, 1);
        draw_big_string_c(110, "[R] to play again!", WHITE, 1);
    } else if (game->state == P2_WIN) {
        draw_big_string_cr(50, "P2 Wins!", 4);
        draw_big_string_c(100, "[ESC] to exit or", WHITE, 1);
        draw_big_string_c(110, "[R] to play again!", WHITE, 1);

    } else if (game->state == INSTRUCTIONS) {
        draw_big_string_cr(15, "Instructions", 2);
        draw_big_string(10, 40, "[W] and [S] to move paddle 1", WHITE, 1);
        draw_big_string(10, 50, "[UP] and [DOWN] to move paddle 2", WHITE, 1);
        draw_big_string(10, 60, "[R] to reset, [ESC] to end", WHITE, 1);
        draw_big_string(10, 70, "[P] to pause and unpause", WHITE, 1);

        draw_big_string(10, 90, "First to 5 wins!", WHITE, 1);

        draw_big_string(10, 180, "[ESC] to return to the main menu", WHITE, 1);
    }

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

    clear_screen(BLACK);
    draw_big_string_cr(50, "Game Over!", 3);
    draw_big_string_c(150, "PongOS has halted.", WHITE, 1);

    draw();
}