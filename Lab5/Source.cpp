#include<allegro5/allegro.h>
#include <allegro5//allegro_primitives.h>
#include <iostream>

// Define a bitmap structure for easy configuration
struct Bitmap{
	int x, y;
	ALLEGRO_COLOR color;
};

void create_bitmap(ALLEGRO_BITMAP* bitmap,ALLEGRO_DISPLAY* display);

int main() {

    /*
	* Initialize Allegro and all its addons, cretae a strictly 64 x 64 bitmap
    */

	if(!al_init()){
		std::cout << "Allegro failed!" << std::endl;
		return -1;
	}

	ALLEGRO_DISPLAY* display = al_create_display(800, 600);
	if(!display){
		std::cout << "Display failed!" << std::endl;
		return -1;
	}
	al_init_primitives_addon();

    ALLEGRO_BITMAP* bitmap = al_create_bitmap(64,64);

	// Bitmap will need movement in the future so keyobard input is required
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_EVENT event;
	if(!event_queue) {
		std::cout << "Event queue failed!" << std::endl;
		return -1;
	}
	al_install_keyboard();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	create_bitmap(bitmap, display);

    while(true) {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(bitmap, 100, 100, 0);
        al_flip_display();
        al_wait_for_event(event_queue, &event);
	}

    // Clean up game objects upon exit
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(bitmap);
	al_destroy_event_queue(event_queue);

}

void create_bitmap(ALLEGRO_BITMAP* bitmap, ALLEGRO_DISPLAY* display) {
    al_set_target_bitmap(bitmap);

    ALLEGRO_COLOR colors[3] = {
        al_map_rgb(255, 50, 50),   // Red
        al_map_rgb(50, 255, 50),   // Green
        al_map_rgb(50, 50, 255)    // Blue
    };

    // Define each indicvual primtive within the bitmap
    Bitmap prims[4] = {
        { 4, 4, colors[0] },    // Rectangle
        { 48, 12, colors[1] },  // Circle
        { 0, 63, colors[2] },   // Line start
        { 32, 40, colors[0] }   // Triangle
    };

    al_clear_to_color(al_map_rgb(0, 0, 0));

	// Draw first primitive
    al_draw_filled_rectangle(prims[0].x, prims[0].y, prims[0].x + 20, prims[0].y + 20, prims[0].color);

	// Draw second primitive
    al_draw_filled_circle(prims[1].x, prims[1].y, 10, prims[1].color);

	// Draw third primitive
    al_draw_line(prims[2].x, prims[2].y, 63, 0, prims[2].color, 2.0);

	// Draw last primitive
    al_draw_filled_triangle(
        prims[3].x, prims[3].y,
        60, 60,
        10, 60,
        prims[3].color
    );

    al_set_target_backbuffer(display);
}
