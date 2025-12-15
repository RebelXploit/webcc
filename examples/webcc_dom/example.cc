#include "webcc/dom.h"
#include "webcc/system.h"
#include "webcc/input.h"

int item_count = 0;
int last_clicked_x = 0;
int last_clicked_y = 0;

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

extern "C" void webcc_on_mousedown(int button, int x, int y) {
    item_count++;
    last_clicked_x = x;
    last_clicked_y = y;
    
    char num[16];
    int i;
    
    // Build item_id: "item-X"
    char item_id[32];
    const char* prefix = "item-";
    i = 0;
    for (int k = 0; prefix[k]; ++k) item_id[i++] = prefix[k];
    int_to_str(item_count, num);
    for (int k = 0; num[k]; ++k) item_id[i++] = num[k];
    item_id[i] = '\0';
    
    webcc::dom::create_element(item_id, "div");
    
    // Build text: "Box #X"
    char text[64];
    i = 0;
    const char* text_prefix = "Box #";
    for (int k = 0; text_prefix[k]; ++k) text[i++] = text_prefix[k];
    for (int k = 0; num[k]; ++k) text[i++] = num[k];
    text[i] = '\0';
    
    webcc::dom::set_inner_text(item_id, text);
    
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
    
    webcc::dom::set_attribute(item_id, "style", style);
    webcc::dom::append_child("box-container", item_id);

    // Update counter
    int_to_str(item_count, num);
    char counter_text[64];
    i = 0;
    const char* ct = "Total Boxes: ";
    for(int k=0; ct[k]; ++k) counter_text[i++] = ct[k];
    for(int k=0; num[k]; ++k) counter_text[i++] = num[k];
    counter_text[i] = '\0';
    webcc::dom::set_inner_text("counter", counter_text);

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
    webcc::dom::set_inner_text("click-pos", click_text);

    webcc::flush();
}

int main() {
    webcc::system::set_title("WebCC DOM Demo");
    
    // Style the body to center content
    webcc::dom::set_attribute("body", "style", "margin: 0; height: 100vh; display: flex; justify-content: center; align-items: center; background: #111; color: #eee; font-family: sans-serif;");

    // Create a container for the game
    webcc::dom::create_element("game-container", "div");
    webcc::dom::set_attribute("game-container", "style", "position: relative; border: 2px solid #444; box-shadow: 0 0 20px rgba(0,0,0,0.5); display: flex; flex-direction: column; align-items: center; background: #222; padding: 20px; min-width: 500px;");
    webcc::dom::append_child("body", "game-container");

    // Add a title via DOM
    webcc::dom::create_element("game-title", "h1");
    webcc::dom::set_inner_text("game-title", "WebCC DOM Demo");
    webcc::dom::set_attribute("game-title", "style", "color: #fff; margin: 10px 0; font-family: monospace;");
    webcc::dom::append_child("game-container", "game-title");

    // Add some description text
    webcc::dom::create_element("game-desc", "p");
    webcc::dom::set_inner_text("game-desc", "Click the button below to create colorful boxes with random colors. The DOM is controlled through C++!");
    webcc::dom::set_attribute("game-desc", "style", "color: #aaa; margin-bottom: 20px; font-size: 14px; text-align: center;");
    webcc::dom::append_child("game-container", "game-desc");

    // Stats container
    webcc::dom::create_element("stats", "div");
    webcc::dom::set_attribute("stats", "style", "display: flex; gap: 20px; margin-bottom: 20px; font-size: 14px; color: #4CAF50;");
    webcc::dom::append_child("game-container", "stats");

    webcc::dom::create_element("counter", "div");
    webcc::dom::set_inner_text("counter", "Total Boxes: 0");
    webcc::dom::append_child("stats", "counter");

    webcc::dom::create_element("click-pos", "div");
    webcc::dom::set_inner_text("click-pos", "Last Click: (0, 0)");
    webcc::dom::append_child("stats", "click-pos");

    // Create a button
    webcc::dom::create_element("add-btn", "button");
    webcc::dom::set_inner_text("add-btn", "Create Box");
    webcc::dom::set_attribute("add-btn", "style", "padding: 15px 30px; font-size: 18px; cursor: pointer; background: #4CAF50; color: white; border: none; border-radius: 5px; transition: background 0.3s; margin-bottom: 20px;");
    webcc::dom::append_child("game-container", "add-btn");

    // Container for boxes
    webcc::dom::create_element("box-container", "div");
    webcc::dom::set_attribute("box-container", "style", "display: flex; flex-wrap: wrap; justify-content: center; gap: 5px; max-width: 600px; padding: 20px; background: #1a1a1a; border-radius: 10px; min-height: 100px;");
    webcc::dom::append_child("game-container", "box-container");

    webcc::input::init_mouse("add-btn");

    webcc::flush();
    return 0;
}

extern "C" void webcc_on_mouseup(int button, int x, int y) {}
extern "C" void webcc_on_mousemove(int x, int y) {}
