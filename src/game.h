#include "lib.h"

#define PADDLE_WIDTH (FRAME_WIDTH / 32)
#define PADDLE_HEIGHT (FRAME_HEIGHT / 4)
#define PADDLE_MAX_Y (FRAME_HEIGHT - PADDLE_HEIGHT - 1)
#define PADDLE_INITAL_Y ((FRAME_HEIGHT - BALL_SIZE) / 2)
#define PADDLE_1_X 0
#define PADDLE_2_X (PADDLE_WIDTH - PADDLE_WIDTH - 1)
#define PADDLE_SPEED (FRAME_HEIGHT / 100)

#define BALL_SPEED (PADDLE_WIDTH - 1)
#define BALL_SIZE PADDLE_WIDTH
#define BALL_MAX_Y (FRAME_HEIGHT - BALL_SIZE - 1)
#define BALL_MIN_X 0
#define BALL_MIN_Y 0
#define BALL_MAX_X (FRAME_WIDTH - BALL_SIZE - 1)
#define BALL_INITIAL_X ((FRAME_WIDTH - BALL_SIZE) / 2)
#define BALL_INITIAL_Y ((FRAME_HEIGHT - BALL_SIZE) / 2)

#define FP_INV_SQRT_2 0b11011
#define FP_COMMA_SIZE 5

#define COLOR_BG 0xff
#define COLOR_BALL 0b11100000
#define COLOR_PADDLE 0x00

struct GameState
{
    int ballX;
    int ballY;
    int ballDirX;
    int ballDirY;
    int paddle1Y;
    int paddle1DirY;
    int paddle2Y;
    int paddle2DirY;
};

void initGame();
void initState();
void gameLoop();
char gameResetRequired();
struct GameState getNextState();
void renderFull();
void renderDiff(struct GameState nextState);
void clearView();
char rectsCollide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void buttonPressed();

struct GameState state;

void initGame()
{
    initState();
    draw_rect(0, 0, FRAME_WIDTH, FRAME_HEIGHT, COLOR_BG);
    renderFull();
    setTimerInterrupt(1000000);
    enableButtonInterrupt();
}

void initState()
{
    state.ballDirX = 0;
    state.ballDirY = 0;
    state.ballX = BALL_INITIAL_X;
    state.ballY = BALL_INITIAL_Y;
    state.paddle1Y = PADDLE_INITAL_Y;
    state.paddle1DirY = 0;
    state.paddle2Y = PADDLE_INITAL_Y;
    state.paddle2DirY = 0;
}

void buttonInt() {
    int buttonState = getButtonState() >> 15;
    int paddle1Dir = 0;
    int paddle2Dir = 0;

    if (buttonState & 1 == 1) {
        paddle1Dir += -1;
    }
    if (buttonState & 2 == 2) {
        paddle1Dir += 1;
    }
    if (buttonState & 4 == 4) {
        paddle2Dir += -1;
    }
    if (buttonState & 8 == 8) {
        paddle2Dir += 1;
    }

    if (state.ballDirX == 0) {
        if (buttonState & 3 != 0) {
            state.ballDirX = BALL_SPEED;
        }
        if (buttonState & 12 != 0) {
            state.ballDirX = -BALL_SPEED;
        }   
    }

    state.paddle1DirY = PADDLE_SPEED * paddle1Dir;
    state.paddle2DirY = PADDLE_SPEED * paddle2Dir;
}

void timerInt()
{
    if (gameResetRequired() == 1)
    {
        initState();
        renderFull();
    }
    else
    {
        struct GameState nextState = getNextState();
        renderDiff(nextState);
        state.ballDirX = nextState.ballDirX;
        state.ballDirY = nextState.ballDirY;
        state.ballX = nextState.ballX;
        state.ballY = nextState.ballY;
        state.paddle1DirY = nextState.paddle1DirY;
        state.paddle1Y = nextState.paddle1Y;
        state.paddle2DirY = nextState.paddle2DirY;
        state.paddle2Y = nextState.paddle2Y;
    }
}

char gameResetRequired()
{
    if (state.ballX != BALL_MIN_X && state.ballX != BALL_MAX_X)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void clearView()
{
    draw_rect(state.ballX >> FP_COMMA_SIZE, state.ballY >> FP_COMMA_SIZE, BALL_SIZE, BALL_SIZE, COLOR_BG);
    draw_rect(PADDLE_1_X, state.paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_BG);
    draw_rect(PADDLE_2_X, state.paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_BG);
}

void renderFull()
{
    draw_rect(state.ballX >> FP_COMMA_SIZE, state.ballY >> FP_COMMA_SIZE, BALL_SIZE, BALL_SIZE, COLOR_BALL);
    draw_rect(PADDLE_1_X, state.paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_PADDLE);
    draw_rect(PADDLE_2_X, state.paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_PADDLE);
}

void renderDiff(struct GameState nextState)
{
    update_rect(state.ballX >> FP_COMMA_SIZE, state.ballY >> FP_COMMA_SIZE, nextState.ballX >> FP_COMMA_SIZE, nextState.ballY >> FP_COMMA_SIZE, BALL_SIZE, BALL_SIZE, COLOR_BALL, COLOR_BG);
    update_rect(PADDLE_1_X, state.paddle1Y, PADDLE_1_X, nextState.paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_PADDLE, COLOR_BG);
    update_rect(PADDLE_2_X, state.paddle2Y, PADDLE_2_X, nextState.paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_PADDLE, COLOR_BG);
}

struct GameState getNextState()
{
    struct GameState nextState;
    nextState.ballDirX = state.ballDirX;

    if (state.ballY == BALL_MAX_Y || state.ballY == BALL_MIN_Y)
    {
        nextState.ballDirY = -state.ballDirY;
    }
    else
    {
        nextState.ballDirY = state.ballDirY;
    }

    nextState.paddle1DirY = state.paddle1DirY;
    nextState.paddle2DirY = state.paddle2DirY;
    nextState.paddle1Y = minMax(0, state.paddle1Y + state.paddle1DirY, PADDLE_MAX_Y);
    nextState.paddle2Y = minMax(0, state.paddle2Y + state.paddle2DirY, PADDLE_MAX_Y);

    if (state.ballDirX != 0 && state.ballDirY != 0)
    {
        int ballMvX = ((state.ballDirX << FP_COMMA_SIZE) * FP_INV_SQRT_2) >> FP_COMMA_SIZE;
        int ballMvY = ((state.ballDirY << FP_COMMA_SIZE) * FP_INV_SQRT_2) >> FP_COMMA_SIZE;
        nextState.ballX = minMax(BALL_MIN_X, state.ballX + ballMvX, BALL_MAX_X);
        nextState.ballY = minMax(BALL_MIN_Y, state.ballX + ballMvY, BALL_MAX_Y);
    }
    else
    {
        nextState.ballX = minMax(BALL_MIN_X, state.ballX + state.ballDirX << FP_COMMA_SIZE, BALL_MAX_X);
        nextState.ballY = minMax(BALL_MIN_X, state.ballY + state.ballDirY << FP_COMMA_SIZE, BALL_MAX_X);
    }

    if (rectsCollide(nextState.ballDirX, nextState.ballDirY, BALL_SIZE, BALL_SIZE, PADDLE_1_X, nextState.paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT)) {
        nextState.ballDirX = -nextState.ballDirX;
        nextState.ballX = PADDLE_1_X + PADDLE_WIDTH;

        if (state.paddle1DirY > 0) {
            nextState.ballDirY = BALL_SPEED;
        }
        else {
            nextState.ballDirY = -BALL_SPEED;
        }
    }
    if (rectsCollide(nextState.ballDirX, nextState.ballDirY, BALL_SIZE, BALL_SIZE, PADDLE_2_X, nextState.paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT)) {
        nextState.ballDirX = -nextState.ballDirX;
        nextState.ballX = PADDLE_2_X - BALL_SIZE;

        if (state.paddle2DirY > 0) {
            nextState.ballDirY = BALL_SPEED;
        }
        else {
            nextState.ballDirY = -BALL_SPEED;
        }
    }

    return nextState;
}

char rectsCollide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if (x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
