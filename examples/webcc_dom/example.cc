#include "webcc/dom.h"
#include "webcc/system.h"
#include "webcc/input.h"

int item_count = 0;
int last_clicked_x = 0;
int last_clicked_y = 0;

// Global handles
int box_container = 0;
int counter_el = 0;
int click_pos_el = 0;
int add_btn = 0;

// Helper for int to string
void int_to_str(int v, char* buf) {
    if (v == 0) {
        buf[0] = '0'; buf[1] = '\0';
        return;
    }
    int i = 0;
    if (v < 0) {
        buf[i++] = '-';
        v = -v;
    }
    int temp = v;
    int len = 0;
    while (temp > 0) {
        temp /= 10;
        len++;
    }
    for (int j = 0; j < len; j++) {
        buf[i + len - 1 - j] = (v % 10) + '0';
        v /= 10;
    }
    buf[i + len] = '\0';
}

// Simple pseudo-random number generator
int simple_rand() {
    static unsigned int seed = 12345;
    seed = seed * 1103515245 + 12345;
    return (seed / 65536) % 32768;
}

// Generate random color
void get_random_color(char* buf) {
    int r = simple_rand() % 256;
    int g = simple_rand() % 256;
    int b = simple_rand() % 256;
    
    const char* prefix = "rgb(";
    int i = 0;
    for (int k = 0; prefix[k]; ++k) buf[i++] = prefix[k];
    
    char num[16];
    int_to_str(r, num);
    for (int k = 0; num[k]; ++k) buf[i++] = num[k];
    buf[i++] = ',';
    buf[i++] = ' ';
    
    int_to_str(g, num);
    for (int k = 0; num[k]; ++k) buf[i++] = num[k];
    buf[i++] = ',';
    buf[i++] = ' ';
    
    int_to_str(b, num);
    for (int k = 0; num[k]; ++k) buf[i++] = num[k];
    buf[i++] = ')';
    buf[i] = '\0';
}

void update(float time_ms) {
    // Poll events
    uint8_t opcode;
    const uint8_t* data;
    uint32_t len;
    while (webcc::poll_event(opcode, &data, len)) {
        switch (opcode) {
            case webcc::input::EVENT_MOUSE_DOWN: {
                int32_t args[3];
                __builtin_memcpy(args, data, 12);
                int button = args[0];
                int x = args[1];
                int y = args[2];

                item_count++;
                last_clicked_x = x;
                last_clicked_y = y;
                
                char num[16];
                int i;
                
                int_to_str(item_count, num);
                
                int item = webcc::dom::create_element("div");
                
                // Build text: "Box #X"
                char text[64];
                i = 0;
                const char* text_prefix = "Box #";
                for (int k = 0; text_prefix[k]; ++k) text[i++] = text_prefix[k];
                for (int k = 0; num[k]; ++k) text[i++] = num[k];
                text[i] = '\0';
                
                webcc::dom::set_inner_text(item, text);
                
                // Generate random color
                char color[32];
                get_random_color(color);
                
                // Build style string with random background color
                char style[256];
                i = 0;
                const char* style_prefix = "padding: 15px 20px; margin: 5px; border-radius: 8px; color: white; font-weight: bold; display: inline-block; box-shadow: 0 2px 5px rgba(0,0,0,0.3); transition: transform 0.2s; cursor: pointer; background: ";
                for (int k = 0; style_prefix[k]; ++k) style[i++] = style_prefix[k];
                for (int k = 0; color[k]; ++k) style[i++] = color[k];
                style[i++] = ';';
                style[i] = '\0';
                
                webcc::dom::set_attribute(item, "style", style);
                webcc::dom::append_child(box_container, item);

                // Update counter
                int_to_str(item_count, num);
                char counter_text[64];
                i = 0;
                const char* ct = "Total Boxes: ";
                for(int k=0; ct[k]; ++k) counter_text[i++] = ct[k];
                for(int k=0; num[k]; ++k) counter_text[i++] = num[k];
                counter_text[i] = '\0';
                webcc::dom::set_inner_text(counter_el, counter_text);

                // Update click position
                char click_text[64];
                i = 0;
                const char* cl = "Last Click: (";
                for(int k=0; cl[k]; ++k) click_text[i++] = cl[k];
                int_to_str(last_clicked_x, num);
                for(int k=0; num[k]; ++k) click_text[i++] = num[k];
                click_text[i++] = ',';
                click_text[i++] = ' ';
                int_to_str(last_clicked_y, num);
                for(int k=0; num[k]; ++k) click_text[i++] = num[k];
                click_text[i++] = ')';
                click_text[i] = '\0';
                webcc::dom::set_inner_text(click_pos_el, click_text);
                break;
            }
        }
    }
    webcc::flush();
}

int main() {
    webcc::system::set_title("WebCC DOM Demo");
    
    int body = webcc::dom::get_body();

    // Style the body to center content
    webcc::dom::set_attribute(body, "style", "margin: 0; height: 100vh; display: flex; justify-content: center; align-items: center; background: #111; color: #eee; font-family: sans-serif;");

    // Create a container for the game
    int game_container = webcc::dom::create_element("div");
    webcc::dom::set_attribute(game_container, "style", "position: relative; border: 2px solid #444; box-shadow: 0 0 20px rgba(0,0,0,0.5); display: flex; flex-direction: column; align-items: center; background: #222; padding: 20px; min-width: 500px;");
    webcc::dom::append_child(body, game_container);

    // Add a title via DOM
    int game_title = webcc::dom::create_element("h1");
    webcc::dom::set_inner_text(game_title, "WebCC DOM Demo");
    webcc::dom::set_attribute(game_title, "style", "color: #fff; margin: 10px 0; font-family: monospace;");
    webcc::dom::append_child(game_container, game_title);

    // Add some description text
    int game_desc = webcc::dom::create_element("p");
    webcc::dom::set_inner_text(game_desc, "Click the button below to create colorful boxes with random colors. The DOM is controlled through C++!");
    webcc::dom::set_attribute(game_desc, "style", "color: #aaa; margin-bottom: 20px; font-size: 14px; text-align: center;");
    webcc::dom::append_child(game_container, game_desc);

    // Stats container
    int stats = webcc::dom::create_element("div");
    webcc::dom::set_attribute(stats, "style", "display: flex; gap: 20px; margin-bottom: 20px; font-size: 14px; color: #4CAF50;");
    webcc::dom::append_child(game_container, stats);

    counter_el = webcc::dom::create_element("div");
    webcc::dom::set_inner_text(counter_el, "Total Boxes: 0");
    webcc::dom::append_child(stats, counter_el);

    click_pos_el = webcc::dom::create_element("div");
    webcc::dom::set_inner_text(click_pos_el, "Last Click: (0, 0)");
    webcc::dom::append_child(stats, click_pos_el);

    // Create a button
    add_btn = webcc::dom::create_element("button");
    webcc::dom::set_inner_text(add_btn, "Create Box");
    webcc::dom::set_attribute(add_btn, "style", "padding: 15px 30px; font-size: 18px; cursor: pointer; background: #4CAF50; color: white; border: none; border-radius: 5px; transition: background 0.3s; margin-bottom: 20px;");
    webcc::dom::append_child(game_container, add_btn);

    // Container for boxes
    box_container = webcc::dom::create_element("div");
    webcc::dom::set_attribute(box_container, "style", "display: flex; flex-wrap: wrap; justify-content: center; gap: 5px; max-width: 600px; padding: 20px; background: #1a1a1a; border-radius: 10px; min-height: 100px;");
    webcc::dom::append_child(game_container, box_container);

    webcc::input::init_mouse(add_btn);

    webcc::system::set_main_loop(update);

    webcc::flush();
    return 0;
}
