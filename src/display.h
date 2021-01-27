#define FRAME_WIDTH 640
#define FRAME_HEIGHT 300
#define FRAME_H_START 90

#define FRAME_COL_FIRST 144
#define FRAME_COL_LAST 784

#define FRAME_ROW_FIRST 125
#define FRAME_ROW_LAST 425

char volatile *p_vga_buffer_start;

void initDisplay();
char volatile *get_pixel_pointer(int x, int y);
void draw_rect(int x, int y, int w, int h, char pixel);
void fill_rect_diff(int x0, int y0, int x1, int y1, int w, int h, char fill);
void set_pixel(int x, int y, char pixel);
void update_rect(int oldX, int oldY, int newX, int newY, int w, int h, char fill, char clear);

void initDisplay()
{
    p_vga_buffer_start = (char volatile*)0x1C010000;
}

char volatile *get_pixel_pointer(int x, int y)
{
    // return p_vga_buffer_start + x + FRAME_COL_FIRST + FRAME_COL_LAST * (y + FRAME_ROW_FIRST);
    return p_vga_buffer_start + x + FRAME_WIDTH * y;
}

void set_pixel(int x, int y, char pixel)
{
    char volatile *pixel_addr = get_pixel_pointer(x, y);
    *pixel_addr = pixel;
}

void fill_rect_diff(int x0, int y0, int x1, int y1, int w, int h, char fill) {
    int xDiff = x1 - x0;
    int yDiff = y1 - y0;

    if (x0 <= x1) {
        draw_rect(x0, y0, xDiff, h, fill);
        if (y0 <= y1) {
            draw_rect(x0 + xDiff, y0 + yDiff, w - xDiff, yDiff, fill);
        }
        else {  
            draw_rect(x0 + xDiff, y0, w - xDiff, -yDiff, fill);
        }
    }
    else {
        draw_rect(x0 - xDiff, y0, -xDiff, h, fill);
        if (y0 <= y1) {
            draw_rect(x0, y0 + yDiff, w + xDiff, yDiff, fill);
        }
        else {
            draw_rect(x0, y0, w + xDiff, -yDiff, fill);
        }
    }
}

void update_rect(int oldX, int oldY, int newX, int newY, int w, int h, char fill, char clear) {
    fill_rect_diff(oldX, oldY, newX, newY, w, h, clear);
    fill_rect_diff(newX, newY, oldX, oldY, w, h, fill);
}

void draw_rect(int x, int y, int w, int h, char pixel)
{
    for (int xo = 0; xo < w; xo++)
    {
        for (int yo = 0; yo < h; yo++)
        {
            char volatile *pixel_addr = get_pixel_pointer(x + xo, y + yo);
            *pixel_addr = pixel;
        }
    }
}