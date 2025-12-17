#include "webcc/canvas.h"
#include "webcc/dom.h"
#include "webcc/system.h"
#include "webcc/input.h"

// Global state
float rotation = 0.0f;
float mouse_x = 0.0f;
float mouse_y = 0.0f;
bool is_clicking = false;

// Canvas Handles
int demo_canvas = 0;
int hud_canvas = 0;

// FPS counting
float last_time = 0.0f;
float fps = 0.0f;

extern "C" void update(float time_ms) {
    // Poll events
    uint8_t opcode;
    const uint8_t* data;
    uint32_t len;
    while (webcc::poll_event(opcode, &data, len)) {
        switch (opcode) {
            case webcc::input::EVENT_MOUSE_MOVE: {
                int32_t args[2];
                __builtin_memcpy(args, data, 8);
                mouse_x = (float)args[0];
                mouse_y = (float)args[1];
                break;
            }
            case webcc::input::EVENT_MOUSE_DOWN: {
                is_clicking = true;
                break;
            }
            case webcc::input::EVENT_MOUSE_UP: {
                is_clicking = false;
                break;
            }
        }
    }

    // Calculate Delta Time (in seconds)
    float delta_time = (time_ms - last_time) / 1000.0f;
    last_time = time_ms;
    
    // Avoid huge delta_time on first frame
    if (delta_time > 0.1f) delta_time = 0.016f;

    // Calculate FPS
    if (delta_time > 0.0f) {
        fps = 1.0f / delta_time;
    }

    // Clear background
    webcc::canvas::set_fill_style(demo_canvas, 20, 20, 30);
    webcc::canvas::fill_rect(demo_canvas, 0, 0, 600, 600);

    // Draw rotating square at center
    webcc::canvas::save(demo_canvas);
    webcc::canvas::translate(demo_canvas, 300, 300);
    webcc::canvas::rotate(demo_canvas, rotation);
    
    if (is_clicking) {
        webcc::canvas::set_fill_style(demo_canvas, 255, 50, 50);
        webcc::canvas::set_shadow(demo_canvas, 20, 0, 0, "red");
    } else {
        webcc::canvas::set_fill_style(demo_canvas, 100, 200, 255);
        webcc::canvas::set_shadow(demo_canvas, 10, 5, 5, "rgba(0,0,0,0.5)");
    }
    
    webcc::canvas::fill_rect(demo_canvas, -50, -50, 100, 100);
    webcc::canvas::restore(demo_canvas);

    // Draw circle at mouse position
    webcc::canvas::begin_path(demo_canvas);
    webcc::canvas::arc(demo_canvas, mouse_x, mouse_y, 10, 0, 6.28f);
    webcc::canvas::set_fill_style(demo_canvas, 255, 255, 0);
    webcc::canvas::fill(demo_canvas);

    // Draw FPS via HUD overlay 
    webcc::canvas::clear_rect(hud_canvas, 0, 0, 200, 40);
    webcc::canvas::set_font(hud_canvas, "20px Arial");
    webcc::canvas::set_fill_style(hud_canvas, 0, 255, 0);
    webcc::canvas::fill_text_f(hud_canvas, "FPS: %f", fps, 10, 25);

    // Rotate based on delta_time (e.g., 1 radian per second)
    rotation += 1.0f * delta_time;

    webcc::flush();
}

int main() {
    webcc::system::set_title("WebCC Canvas Demo");
    
    int body = webcc::dom::get_body();

    // Style the body to center content
    webcc::dom::set_attribute(body, "style", "margin: 0; height: 100vh; display: flex; justify-content: center; align-items: center; background: #111; color: #eee; font-family: sans-serif;");

    // Create a container for the game
    int game_container = webcc::dom::create_element("div");
    webcc::dom::set_attribute(game_container, "style", "position: relative; border: 2px solid #444; box-shadow: 0 0 20px rgba(0,0,0,0.5); display: flex; flex-direction: column; align-items: center; background: #222; padding: 10px;");
    webcc::dom::append_child(body, game_container);

    // Add a title via DOM
    int game_title = webcc::dom::create_element("h1");
    webcc::dom::set_inner_text(game_title, "WebCC Canvas Demo");
    webcc::dom::set_attribute(game_title, "style", "color: #fff; margin: 10px 0; font-family: monospace;");
    webcc::dom::append_child(game_container, game_title);

    // Add some description text
    int game_desc = webcc::dom::create_element("p");
    webcc::dom::set_inner_text(game_desc, "This text is a DOM element created from C++. The canvas below is Canvas 2D.");
    webcc::dom::set_attribute(game_desc, "style", "color: #aaa; margin-bottom: 20px; font-size: 14px;");
    webcc::dom::append_child(game_container, game_desc);

    // Create main render canvas and append to container
    demo_canvas = webcc::canvas::create_canvas("demo-canvas", 600, 600);
    webcc::dom::append_child(game_container, demo_canvas);

    // HUD canvas overlay for FPS (to match WebGL example)
    hud_canvas = webcc::canvas::create_canvas("hud-canvas", 600, 600);
    webcc::dom::set_attribute(hud_canvas, "style", "position: absolute; left: 0; top: 0; pointer-events: none;");
    webcc::dom::append_child(game_container, hud_canvas);
    
    // Initialize input listeners on the canvas so we get correct offsets
    webcc::input::init_mouse(demo_canvas);

    webcc::system::log("Starting demo loop...");
    webcc::system::set_main_loop("update");
    
    webcc::flush();
    return 0;
}
