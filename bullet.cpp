#include "bullet.h"

bullet::bullet() {
    x = 0;
    y = 0;
    alive = false;
    bullet_bmp = NULL;
}

bullet::~bullet() {
    bullet_bmp = NULL;
}

void bullet::create_bullet_bitmap(ALLEGRO_DISPLAY* display) {
    bullet_bmp = al_create_bitmap(16, 16);
    if (!bullet_bmp)
        return;

    al_set_target_bitmap(bullet_bmp);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));

    // two primitives two colors
    al_draw_filled_circle(8, 8, 8, al_map_rgb(255, 50, 50));    // red circle
    al_draw_filled_circle(8, 5, 3, al_map_rgb(255, 255, 100));  // yellow highlight

    al_set_target_bitmap(al_get_backbuffer(display));
}

void bullet::fire(int start_x, int start_y) {
    x = start_x;
    y = start_y;
    alive = true;
}

int bullet::move_bullet(int width, int height) {
    if (!alive)
        return 0;

    y += 1;

    if (y > height) {
        alive = false;
        return 0;
    }
    return 1;
}

void bullet::draw_bullet() {
    if (alive && bullet_bmp)
        al_draw_bitmap(bullet_bmp, x, y, 0);
}

void bullet::erase_bullet() {
    alive = false;
}

bool bullet::get_status() {
    return alive;
}

int bullet::get_x() {
    return x;
}

int bullet::get_y() {
    return y;
}

void bullet::set_bitmap(ALLEGRO_BITMAP* bmp) {
    bullet_bmp = bmp;
}