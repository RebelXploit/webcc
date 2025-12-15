#include "webcc/audio.h"
#include "webcc/dom.h"
#include "webcc/system.h"
#include "webcc/input.h"

// Global state
bool is_playing = false;

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

// Helper for constructing style string
void make_width_style(int percent, char* buf) {
    // "width: XX%;"
    char num[16];
    int_to_str(percent, num);
    
    const char* prefix = "width: ";
    const char* suffix = "%;";
    
    int i = 0;
    for(int k=0; prefix[k]; ++k) buf[i++] = prefix[k];
    for(int k=0; num[k]; ++k) buf[i++] = num[k];
    for(int k=0; suffix[k]; ++k) buf[i++] = suffix[k];
    buf[i] = '\0';
}

extern "C" void webcc_on_mousedown(int button, int x, int y) {
    if (is_playing) {
        webcc::audio::pause("bg-music");
        webcc::dom::set_inner_text("play-btn", "Play Music");
        is_playing = false;
    } else {
        webcc::audio::play("bg-music");
        webcc::dom::set_inner_text("play-btn", "Pause Music");
        is_playing = true;
    }
    webcc::flush();
}

extern "C" void webcc_on_mouseup(int button, int x, int y) {}
extern "C" void webcc_on_mousemove(int x, int y) {}

extern "C" void update(float time_ms) {
    if (is_playing) {
        float current_time = webcc::audio::get_current_time("bg-music");
        float duration = webcc::audio::get_duration("bg-music");
        if (duration > 0) {
            float progress = current_time / duration;
            char style[128];
            int percent = (int)(progress * 100);
            char num[16];
            int_to_str(percent, num);
            
            const char* full_style = "height: 100%; background: #4CAF50; border-radius: 5px; width: ";
            const char* suffix = "%;";
            
            int i = 0;
            for(int k=0; full_style[k]; ++k) style[i++] = full_style[k];
            for(int k=0; num[k]; ++k) style[i++] = num[k];
            for(int k=0; suffix[k]; ++k) style[i++] = suffix[k];
            style[i] = '\0';
            
            webcc::dom::set_attribute("progress-bar-fill", "style", style);
        }
    }
    webcc::flush();
}

int main() {
    webcc::system::set_title("WebCC Audio Demo");
    
    // Style the body to center content
    webcc::dom::set_attribute("body", "style", "margin: 0; height: 100vh; display: flex; justify-content: center; align-items: center; background: #111; color: #eee; font-family: sans-serif;");

    // Create a container for the game
    webcc::dom::create_element("game-container", "div");
    webcc::dom::set_attribute("game-container", "style", "position: relative; border: 2px solid #444; box-shadow: 0 0 20px rgba(0,0,0,0.5); display: flex; flex-direction: column; align-items: center; background: #222; padding: 20px; min-width: 300px;");
    webcc::dom::append_child("body", "game-container");

    // Add a title via DOM
    webcc::dom::create_element("game-title", "h1");
    webcc::dom::set_inner_text("game-title", "WebCC Audio Demo");
    webcc::dom::set_attribute("game-title", "style", "color: #fff; margin: 10px 0; font-family: monospace;");
    webcc::dom::append_child("game-container", "game-title");

    // Add some description text
    webcc::dom::create_element("game-desc", "p");
    webcc::dom::set_inner_text("game-desc", "This demo shows how to play audio from C++ via WebCC. Click the button to toggle playback.");
    webcc::dom::set_attribute("game-desc", "style", "color: #aaa; margin-bottom: 20px; font-size: 14px; text-align: center;");
    webcc::dom::append_child("game-container", "game-desc");

    // Create audio element
    webcc::audio::create_audio("bg-music", "assets/music.mp3");
    webcc::audio::set_loop("bg-music", 1);
    webcc::audio::set_volume("bg-music", 0.5f);

    // Create a progress bar
    webcc::dom::create_element("progress-bar-container", "div");
    webcc::dom::set_attribute("progress-bar-container", "style", "width: 80%; height: 10px; background: #111; border: 1px solid #444; border-radius: 5px; margin-bottom: 20px;");
    webcc::dom::append_child("game-container", "progress-bar-container");

    webcc::dom::create_element("progress-bar-fill", "div");
    webcc::dom::set_attribute("progress-bar-fill", "style", "width: 0%; height: 100%; background: #4CAF50; border-radius: 5px;");
    webcc::dom::append_child("progress-bar-container", "progress-bar-fill");

    // Create a button
    webcc::dom::create_element("play-btn", "button");
    webcc::dom::set_inner_text("play-btn", "Play Music");
    webcc::dom::set_attribute("play-btn", "style", "padding: 15px 30px; font-size: 18px; cursor: pointer; background: #4CAF50; color: white; border: none; border-radius: 5px; transition: background 0.3s;");
    webcc::dom::append_child("game-container", "play-btn");

    webcc::input::init_mouse("play-btn");
    
    webcc::system::set_main_loop("update");

    webcc::flush();
    return 0;
}
