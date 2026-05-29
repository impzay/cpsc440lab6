#include "cat.h"

cat::cat() {
    speed = 1;
    x = 100;
    y = 100;
    direction = 1;
    score = 0;
    cat_bmp = NULL;
}

cat::~cat() {
    al_destroy_bitmap(cat_bmp);
}

void cat::create_cat_bitmap(ALLEGRO_DISPLAY* display) {
    cat_bmp = al_create_bitmap(64, 64); 
    if (!cat_bmp)
        return;

    al_set_target_bitmap(cat_bmp);
    al_clear_to_color(al_map_rgb(0, 0, 0)); 

    int rect_x = 0;
    int rect_y = 25;

    // body
    al_draw_filled_rectangle(rect_x, rect_y, rect_x + 60, rect_y + 60, al_map_rgb(255, 255, 255));

    // ears
    al_draw_filled_triangle(rect_x, rect_y, rect_x + 5, rect_y - 20, rect_x + 25, rect_y, al_map_rgb(255, 255, 255));
    al_draw_filled_triangle(rect_x + 60, rect_y, rect_x + 55, rect_y - 20, rect_x + 35, rect_y, al_map_rgb(255, 255, 255));

    // eyes
    al_draw_filled_rectangle(rect_x + 10, rect_y + 10, rect_x + 20, rect_y + 15, al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(rect_x + 40, rect_y + 10, rect_x + 50, rect_y + 15, al_map_rgb(0, 0, 0));

    //nose
    al_draw_filled_triangle(rect_x + 25, rect_y + 20, rect_x + 35, rect_y + 20, rect_x + 30, rect_y + 25, al_map_rgb(255, 192, 203));

    //mouth left curve
    float left[8] = { 20, 55,  15, 65,  25, 65,  30, 55 };
    al_draw_spline(left, al_map_rgb(0, 0, 0), 2.0);

    //mouth right curve
    float right_m[8] = { 30, 55,  35, 65,  45, 65,  40, 55 };
    al_draw_spline(right_m, al_map_rgb(0, 0, 0), 2.0);

    // restore backbuffer
    al_set_target_bitmap(al_get_backbuffer(display));
}

void cat::erase_cat() {
    al_draw_filled_rectangle(x, y, x + 64, y + 64, al_map_rgb(0, 0, 0));
}

void cat::move_cat(int width, int height) {
    switch (direction) {
    case 0: //up
        y -= speed;
        if (y < 0) y = 0;
        break;
    case 1: //left
        x -= speed;
        if (x < 0) x = 0;
        break;
    case 2: //right
        x += speed;
        if (x > width - 64) x = width - 64;
        break;
    case 3: //down
        y += speed;
        if (y > height - 64) y = height - 64;
        break;
    }
}

void cat::increase_speed() {
    if (speed < 3)
        speed++;
}


void cat::draw_cat() {
    if (cat_bmp)
        al_draw_bitmap(cat_bmp, x, y, 0);
}

int cat::get_direction() {
    return direction;
}

int cat::get_speed() {
    return speed;
}

int cat::get_x() {
    return x;
}

int cat::get_y() {
    return y;
}

void cat::up() {
    direction = 0;
    speed = 1;
}

void cat::down() {
    direction = 3;
    speed = 1;
}

void cat::right() {     
    direction = 2;
    speed = 1;
}

void cat::left() {
    direction = 1;
    speed = 1;
}