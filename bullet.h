#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class bullet {
public:
    bullet();
    ~bullet();
    void create_bullet_bitmap(ALLEGRO_DISPLAY* display);
    void fire(int start_x, int start_y);
    int move_bullet(int width, int height);
    void draw_bullet();
    void erase_bullet();
    bool get_status();
    int get_x();
    int get_y();
    void set_bitmap(ALLEGRO_BITMAP* bmp);

private:
    int x, y;
    bool alive;
    ALLEGRO_BITMAP* bullet_bmp;
};