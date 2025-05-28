#include<allegro5/allegro.h>
#include <allegro5//allegro_primitives.h>
#include <iostream>

// Define a bitmap structure for easy configuration
struct Bitmap{
	int x, y;
	ALLEGRO_COLOR color;
};

void create_ship_bitmap(ALLEGRO_BITMAP* bitmap,ALLEGRO_DISPLAY* display);

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

    ALLEGRO_BITMAP* ship = al_create_bitmap(64,64);

	// Bitmap will need movement in the future so keyboard input is required
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_EVENT event;
	if(!event_queue) {
		std::cout << "Event queue failed!" << std::endl;
		return -1;
	}
	al_install_keyboard();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	create_ship_bitmap(ship, display);

    while(true) {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        // Draw ship at center of screen
        al_draw_bitmap(ship, 400, 300, 0);
		// Swap buffers to display the drawn content
        al_flip_display();
        al_wait_for_event(event_queue, &event);
	}

    // Clean up game objects upon exit
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(ship);
	al_destroy_event_queue(event_queue);

}

void create_ship_bitmap(ALLEGRO_BITMAP* bitmap, ALLEGRO_DISPLAY* display) {
    al_set_target_bitmap(bitmap);

    ALLEGRO_COLOR colors[4] = {
        al_map_rgb(80, 180, 255),    // Body (light blue)
        al_map_rgb(200, 200, 255),   // Cockpit (light gray/blue)
        al_map_rgb(60, 60, 120),     // Wing (dark blue)
        al_map_rgb(50, 220, 80)     //  Blaster (light green)
    };

    al_clear_to_color(al_map_rgb(0, 0, 0)); 

    // Define ship parts using Bitmap struct
    Bitmap body = { 32, 4,  colors[0] }; 
    Bitmap leftWing = { 12, 32, colors[2] };
    Bitmap rightWing = { 52, 32, colors[2] };
    Bitmap cockpit = { 32, 24, colors[1] };
    Bitmap blaster = { 32, 8,  colors[3] };

	// Draw main body (facing upwards)
    al_draw_filled_triangle(body.x, body.y, 60, 56, 4, 56, body.color);

    // Draw left wing
    al_draw_filled_triangle(leftWing.x, leftWing.y, 4, 56, 24, 56, leftWing.color);

    // Draw right wing
    al_draw_filled_triangle(rightWing.x, rightWing.y, 60, 56, 40, 56, rightWing.color);

    // Draw cockpit
    al_draw_filled_ellipse(cockpit.x, cockpit.y, 8, 12, cockpit.color);

    // Draw blaster (small circle at tip)
    al_draw_filled_circle(blaster.x, blaster.y, 3, blaster.color);

    al_set_target_backbuffer(display);
}
