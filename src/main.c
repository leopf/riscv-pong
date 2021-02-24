#include "lib.h"

#define PADDLE_HEIGHT (FRAME_HEIGHT / 4)
#define PADDLE_WIDTH 21
#define PADDLE_X2 (FRAME_WIDTH - PADDLE_WIDTH - 5)
#define BALL_X0 (((FRAME_WIDTH) - 20) / 2)
#define BALL_Y0 (((FRAME_HEIGHT) - 20) / 2)

int ballColor = 0;

int posX = 0;
int posY = 0;

int ballSpeedY = 0;
int ballSpeedX = 0;

int speedYPaddle1 = 0;
int speedYPaddle2 = 0;

int paddle1Y = 0;
int paddle2Y = 0;

int ledCount = 0;

void resetBall() {
    posX = BALL_X0;
    posY = BALL_Y0;
    ballSpeedX = 0;
    ballSpeedY = 0;
}

void update_rect(int oldX, int oldY, int newX, int newY, int w, int h, char fill, char clear) {
    fill_rect_diff(oldX, oldY, newX, newY, w, h, clear);
    fill_rect_diff(newX, newY, oldX, oldY, w, h, fill);
}

void main()
{
    resetBall();
    clear_window(0xff);
    // fill_rect_diff(0, 200, 10, 210, 20, 20, 0x0f);
    // fill_rect_diff(10, 210, 0, 200, 20, 20, 0xf0);
// 1c0089d0:	0f000813          	li	a6,240
// 1c0089d4:	01400793          	li	a5,20
// 1c0089d8:	01400713          	li	a4,20
// 1c0089dc:	0be00693          	li	a3,190
// 1c0089e0:	03200613          	li	a2,50
// 1c0089e4:	0c800593          	li	a1,200
// 1c0089e8:	02800513          	li	a0,40
    // update_rect(40, 200, 50, 190, 20, 20, 0xf0, 0x0f);
//   fill_rect_diff(40, 200,50, 190, 20, 20, 0xf0);
//     fill_rect_diff(50, 190, 40, 200, 20, 20, 0x0f);

    enableButtonInterrupt();
    setTimerInterrupt(2000000);
    // fill_rect_diff(40, 200, 50, 190, 20, 20, 0x0f);
    // fill_rect_diff(50, 190, 40, 200, 20, 20, 0xf0);
    
    while(1);
}

int abs(int num) {
    if (num < 0) {
        return -num;
    }
    return num;
}

void buttonInt() {
    int state = getButtonState() >> 15;
    setLedStatus(state);

    if (state == 1) {
        speedYPaddle1 = 15;
    }
    if (state == 2) {
        speedYPaddle1 = -15;
    } 

    if (state == 4) {
        speedYPaddle2 = 15;
    }
    if (state == 8) {
        speedYPaddle2 = -15;
    } 

    if (state != 0 && ballSpeedX == 0) {
        ballSpeedX = 20;
    }
}

void timerInt() {
    setLedStatus(1 << ledCount);
    ledCount++;
    if (ledCount == 4) {
        ledCount = 0;
    }

    draw_rect(0, paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT, 0xff);
    paddle1Y += speedYPaddle1;
    draw_rect(0, paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT, 0x00);

    draw_rect(PADDLE_X2, paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT, 0xff);
    paddle2Y += speedYPaddle2;
    draw_rect(PADDLE_X2, paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT, 0x00);

    draw_rect(posX, posY, 20, 20, 0xff);
    posX += ballSpeedX;
    posY += ballSpeedY;
    draw_rect(posX, posY, 20, 20, 0x0f);

    if (paddle1Y < 0) {
        speedYPaddle1 = abs(speedYPaddle1);
    }
    if (paddle1Y > FRAME_HEIGHT - PADDLE_HEIGHT) {
        speedYPaddle1 = -abs(speedYPaddle1);
    }

    if (paddle2Y < 0) {
        speedYPaddle2 = abs(speedYPaddle2);
    }
    if (paddle2Y > FRAME_HEIGHT - PADDLE_HEIGHT) {
        speedYPaddle2 = -abs(speedYPaddle2);
    }

    // if (rectsCollide(posX, posY, 20, 20, 0, paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT) == 1) {
    //     ballSpeedX = abs(ballSpeedX);
    //     ballSpeedY = speedYPaddle1 * 2;
    // }
    // if (posX < 0) {
    //     draw_rect(posX, posY, 20, 20, 0xff);
    //     resetBall();
    // }
    // if (rectsCollide(posX, posY, 20, 20, PADDLE_X2, paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT) == 1) {
    //     ballSpeedX = -abs(ballSpeedX);
    //     ballSpeedY = speedYPaddle2 * 2;
    // }
    // if (posX > FRAME_WIDTH - 20) {
    //     draw_rect(posX, posY, 20, 20, 0xff);
    //     resetBall();
    // }
    // if (posY < 0) {
    //     ballSpeedY = abs(ballSpeedY);
    // }
    // if (posY > FRAME_HEIGHT - 20) {
    //     ballSpeedY = -abs(ballSpeedY);
    // }

    // posX = posX % FRAME_WIDTH;
    // posY = posY % FRAME_HEIGHT;
}
