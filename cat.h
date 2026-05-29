#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>


#define MAX_SPEED 3

class cat
{
public:
	cat();
	~cat();
	void create_cat_bitmap(ALLEGRO_DISPLAY* display);
	void erase_cat();
	void move_cat(int width, int height);
	void draw_cat();
	int get_direction();
	int get_speed();
	int get_x();
	int get_y();
	void up();
	void down();
	void right();
	void left();
	void increase_speed();

private:
	int x, y;
	int direction, speed;
	int color;
	int score;
	ALLEGRO_BITMAP* cat_bmp;


};

