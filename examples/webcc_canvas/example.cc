#include "webcc/canvas.h"
#include "webcc/dom.h"
#include "webcc/system.h"
#include "webcc/input.h"

// Global state
float rotation = 0.0f;
float mouse_x = 0.0f;
float mouse_y = 0.0f;
bool is_clicking = false;

// FPS counting
float last_time = 0.0f;
float fps = 0.0f;

// Input callbacks exported to JS
extern "C" void webcc_on_mousemove(int x, int y) {
    mouse_x = (float)x;
    mouse_y = (float)y;
}

extern "C" void webcc_on_mousedown(int button, int x, int y) {
    is_clicking = true;
}

extern "C" void webcc_on_mouseup(int button, int x, int y) {
    is_clicking = false;
}

extern "C" void update(float time_ms) {
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
    webcc::canvas::set_fill_style("demo-canvas", 20, 20, 30);
    webcc::canvas::fill_rect("demo-canvas", 0, 0, 600, 600);

    // Draw rotating square at center
    webcc::canvas::save("demo-canvas");
    webcc::canvas::translate("demo-canvas", 300, 300);
    webcc::canvas::rotate("demo-canvas", rotation);
    
    if (is_clicking) {
        webcc::canvas::set_fill_style("demo-canvas", 255, 50, 50);
        webcc::canvas::set_shadow("demo-canvas", 20, 0, 0, "red");
    } else {
        webcc::canvas::set_fill_style("demo-canvas", 100, 200, 255);
        webcc::canvas::set_shadow("demo-canvas", 10, 5, 5, "rgba(0,0,0,0.5)");
    }
    
    webcc::canvas::fill_rect("demo-canvas", -50, -50, 100, 100);
    webcc::canvas::restore("demo-canvas");

    // Draw circle at mouse position
    webcc::canvas::begin_path("demo-canvas");
    webcc::canvas::arc("demo-canvas", mouse_x, mouse_y, 10, 0, 6.28f);
    webcc::canvas::set_fill_style("demo-canvas", 255, 255, 0);
    webcc::canvas::fill("demo-canvas");

    // Draw FPS via HUD overlay 
    webcc::canvas::clear_rect("hud-canvas", 0, 0, 200, 40);
    webcc::canvas::set_font("hud-canvas", "20px Arial");
    webcc::canvas::set_fill_style("hud-canvas", 0, 255, 0);
    webcc::canvas::fill_text_f("hud-canvas", "FPS: %f", fps, 10, 25);

    // Rotate based on delta_time (e.g., 1 radian per second)
    rotation += 1.0f * delta_time;

    webcc::flush();
}

int main() {
    webcc::system::set_title("WebCC Canvas Demo");
    
    // Style the body to center content
    webcc::dom::set_attribute("body", "style", "margin: 0; height: 100vh; display: flex; justify-content: center; align-items: center; background: #111; color: #eee; font-family: sans-serif;");

    // Create a container for the game
    webcc::dom::create_element("game-container", "div");
    webcc::dom::set_attribute("game-container", "style", "position: relative; border: 2px solid #444; box-shadow: 0 0 20px rgba(0,0,0,0.5); display: flex; flex-direction: column; align-items: center; background: #222; padding: 10px;");
    webcc::dom::append_child("body", "game-container");

    // Add a title via DOM
    webcc::dom::create_element("game-title", "h1");
    webcc::dom::set_inner_text("game-title", "WebCC Canvas Demo");
    webcc::dom::set_attribute("game-title", "style", "color: #fff; margin: 10px 0; font-family: monospace;");
    webcc::dom::append_child("game-container", "game-title");

    // Add some description text
    webcc::dom::create_element("game-desc", "p");
    webcc::dom::set_inner_text("game-desc", "This text is a DOM element created from C++. The canvas below is Canvas 2D.");
    webcc::dom::set_attribute("game-desc", "style", "color: #aaa; margin-bottom: 20px; font-size: 14px;");
    webcc::dom::append_child("game-container", "game-desc");

    // Create main render canvas and append to container
    webcc::canvas::create_canvas("demo-canvas", 600, 600);
    webcc::dom::append_child("game-container", "demo-canvas");

    // HUD canvas overlay for FPS (to match WebGL example)
    webcc::canvas::create_canvas("hud-canvas", 600, 600);
    webcc::dom::set_attribute("hud-canvas", "style", "position: absolute; left: 0; top: 0; pointer-events: none;");
    webcc::dom::append_child("game-container", "hud-canvas");
    
    // Initialize input listeners on the canvas so we get correct offsets
    webcc::input::init_mouse("demo-canvas");

    webcc::system::log("Starting demo loop...");
    webcc::system::set_main_loop("update");
    
    webcc::flush();
    return 0;
}
