#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <stdlib.h>
#include "cat.h"
#include "bullet.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

int main() {
    int width = 1920;
    int height = 1080;
    bool done = false;
    int score = 0;

    if (!al_init()) {
        return -1;
    }
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY* display = al_create_display(width, height);
    if (!display) {
        return -1;
    }

    ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);

    cat my_cat;
    my_cat.create_cat_bitmap(display);
    al_set_target_bitmap(al_get_backbuffer(display));
    ALLEGRO_BITMAP* shared_bullet_bmp = al_create_bitmap(16, 16);
    if (!shared_bullet_bmp) {
        return -1;
    }
    al_set_target_bitmap(shared_bullet_bmp);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_filled_circle(8, 8, 8, al_map_rgb(255, 50, 50));
    al_draw_filled_circle(8, 5, 3, al_map_rgb(255, 255, 100));
    al_set_target_bitmap(al_get_backbuffer(display));

    //spawn timer for the bullets, 
    ALLEGRO_TIMER* spawn_timer = al_create_timer(1.0);
    ALLEGRO_TIMER* countdown_timer = al_create_timer(1.0);
    int countdown = 30;
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(spawn_timer));
    al_start_timer(spawn_timer);
    al_register_event_source(event_queue, al_get_timer_event_source(countdown_timer));
    al_start_timer(countdown_timer);

    vector<bullet> bullets;
    //i chose to use a vector to be able to manipulate more than one bullet at a time

    //first wave of bulelts fired
    for (int i = 0; i < 10; i++) {
        bullet b;
        b.set_bitmap(shared_bullet_bmp);
        b.fire(rand() % (width - 16), 0);
        bullets.push_back(b);
    }

    al_clear_to_color(black);
    al_flip_display();
   // ALLEGRO_FONT* font = al_load_font("Marlboro.ttf", 64, 0);
    int bar_width = (countdown / 30.0) * width;


    while (!done) {
        ALLEGRO_EVENT ev;
        while (al_get_next_event(event_queue, &ev)) {
            if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                case ALLEGRO_KEY_UP:
                    if (my_cat.get_direction() == 0) my_cat.increase_speed();
                    else my_cat.up();
                    break;
                case ALLEGRO_KEY_DOWN:
                    if (my_cat.get_direction() == 3) my_cat.increase_speed();
                    else my_cat.down();
                    break;
                case ALLEGRO_KEY_LEFT:
                    if (my_cat.get_direction() == 1) my_cat.increase_speed();
                    else my_cat.left();
                    break;
                case ALLEGRO_KEY_RIGHT:
                    if (my_cat.get_direction() == 2) my_cat.increase_speed();
                    else my_cat.right();
                    break;
                }
            }
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                if (ev.timer.source == spawn_timer) {
                    // spawn wave
                    for (int i = 0; i < 10; i++) {
                        bullet b;
                        b.set_bitmap(shared_bullet_bmp);
                        b.fire(rand() % (width - 16), 0);
                        bullets.push_back(b);
                    }
                }
                else if (ev.timer.source == countdown_timer) {
                    countdown--;
                    if (countdown <= 0)
                        done = true;
                }
            }
        }
        al_draw_filled_rectangle(0, 0, bar_width, 20, al_map_rgb(0, 255, 0));

        my_cat.move_cat(width, height);

        
        //udpating bullet positions
        for (int i = 0; i < (int)bullets.size(); i++) {
            if (bullets[i].get_status()) {
                bullets[i].move_bullet(width, height);
                

                //bullet and cat collision
                if (my_cat.get_x() < bullets[i].get_x() + 16 && my_cat.get_x() + 64 > bullets[i].get_x() &&  my_cat.get_y() < bullets[i].get_y() + 16 && my_cat.get_y() + 64 > bullets[i].get_y()) {
                    score++;
                    bullets[i].erase_bullet();
                }
            }
        }

        // remove dead bullets
        for (int i = (int)bullets.size() - 1; i >= 0; i--) {
            if (!bullets[i].get_status())
                bullets.erase(bullets.begin() + i);
        }

        al_clear_to_color(black);
        my_cat.draw_cat();
       // al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Time: %d", countdown);
        //al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 50, 0, "Score: %d", score);
        
        for (int i = 0; i < (int)bullets.size(); i++)
            bullets[i].draw_bullet();
        al_flip_display();
    }

    al_destroy_bitmap(shared_bullet_bmp);
    al_destroy_timer(spawn_timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    return 0;
}