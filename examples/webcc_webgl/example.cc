#include "webcc/webgl.h"
#include "webcc/canvas.h"
#include "webcc/dom.h"
#include "webcc/system.h"

const char* vs_source = 
    "attribute vec3 position;"
    "attribute vec3 color;"
    "varying vec3 vColor;"
    "uniform float angle;"
    "void main() {"
    "  float c = cos(angle);"
    "  float s = sin(angle);"
    "  mat4 rotY = mat4("
    "    c, 0.0, -s, 0.0,"
    "    0.0, 1.0, 0.0, 0.0,"
    "    s, 0.0, c, 0.0,"
    "    0.0, 0.0, 0.0, 1.0"
    "  );"
    "  mat4 rotX = mat4("
    "    1.0, 0.0, 0.0, 0.0,"
    "    0.0, c, -s, 0.0,"
    "    0.0, s, c, 0.0,"
    "    0.0, 0.0, 0.0, 1.0"
    "  );"
    "  gl_Position = rotX * rotY * vec4(position, 1.0);"
    "  gl_Position.z -= 0.0;" // Keep it centered
    "  vColor = color;"
    "}";

const char* fs_source = 
    "precision mediump float;"
    "varying vec3 vColor;"
    "void main() {"
    "  gl_FragColor = vec4(vColor, 1.0);"
    "}";

// Cube vertices: x, y, z, r, g, b
float vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
    
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

    // Bottom face
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

    // Right face
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

    // Left face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f
};

float angle = 0.0f;

float last_time = 0.0f;
float fps = 0.0f;

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

    angle += delta_time * 0.5f; // rotate at 0.5 rad/s

    webcc::webgl::clear_color("gl", 0.1f, 0.1f, 0.1f, 1.0f);
    webcc::webgl::clear("gl", 0x4000 | 0x0100); // COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT

    webcc::webgl::use_program("gl", "prog");
    
    // Update uniform
    webcc::webgl::uniform_1f("gl", "prog", "angle", angle);

    webcc::webgl::bind_buffer("gl", 0x8892, "vbo");
    
    // Position
    webcc::webgl::enable_vertex_attrib_array("gl", 0);
    webcc::webgl::vertex_attrib_pointer("gl", 0, 3, 0x1406, 0, 6 * sizeof(float), 0);

    // Color
    webcc::webgl::enable_vertex_attrib_array("gl", 1);
    webcc::webgl::vertex_attrib_pointer("gl", 1, 3, 0x1406, 0, 6 * sizeof(float), 3 * sizeof(float));

    webcc::webgl::draw_arrays("gl", 0x0004, 0, 36); // GL_TRIANGLES

    // Draw FPS text via Canvas 2D overlay
    webcc::canvas::clear_rect("hud-canvas", 0, 0, 200, 40);
    webcc::canvas::set_font("hud-canvas", "20px Arial");
    webcc::canvas::set_fill_style("hud-canvas", 0, 255, 0);
    webcc::canvas::fill_text_f("hud-canvas", "FPS: %f", fps, 10, 25);

    webcc::flush();
}

int main() {
    webcc::system::set_title("WebCC WebGL Demo");
    
    // Style the body to center content
    webcc::dom::set_attribute("body", "style", "margin: 0; height: 100vh; display: flex; justify-content: center; align-items: center; background: #111; color: #eee; font-family: sans-serif;");

    // Create a container for the game
    webcc::dom::create_element("game-container", "div");
    webcc::dom::set_attribute("game-container", "style", "position: relative; border: 2px solid #444; box-shadow: 0 0 20px rgba(0,0,0,0.5); display: flex; flex-direction: column; align-items: center; background: #222; padding: 10px;");
    webcc::dom::append_child("body", "game-container");

    // Add a title via DOM
    webcc::dom::create_element("game-title", "h1");
    webcc::dom::set_inner_text("game-title", "WebCC WebGL Demo");
    webcc::dom::set_attribute("game-title", "style", "color: #fff; margin: 10px 0; font-family: monospace;");
    webcc::dom::append_child("game-container", "game-title");

    // Add some description text
    webcc::dom::create_element("game-desc", "p");
    webcc::dom::set_inner_text("game-desc", "This is a 3D Cube rendered with WebGL via WebCC.");
    webcc::dom::set_attribute("game-desc", "style", "color: #aaa; margin-bottom: 20px; font-size: 14px;");
    webcc::dom::append_child("game-container", "game-desc");

    // HUD canvas overlay for FPS (like canvas example)
    webcc::canvas::create_canvas("hud-canvas", 800, 600);
    webcc::dom::set_attribute("hud-canvas", "style", "position: absolute; left: 0; top: 0; pointer-events: none;");
    webcc::dom::append_child("game-container", "hud-canvas");

    webcc::dom::create_element("gl-canvas", "canvas");
    webcc::dom::set_attribute("gl-canvas", "width", "600");
    webcc::dom::set_attribute("gl-canvas", "height", "600");
    webcc::dom::append_child("game-container", "gl-canvas");

    // Initialize WebGL
    webcc::webgl::create_context("gl", "gl-canvas");
    webcc::webgl::enable("gl", 0x0B71); // GL_DEPTH_TEST

    // Create Shaders
    webcc::webgl::create_shader("gl", "vs", 0x8B31, vs_source); // GL_VERTEX_SHADER
    webcc::webgl::create_shader("gl", "fs", 0x8B30, fs_source); // GL_FRAGMENT_SHADER
    
    // Create Program
    webcc::webgl::create_program("gl", "prog");
    webcc::webgl::attach_shader("gl", "prog", "vs");
    webcc::webgl::attach_shader("gl", "prog", "fs");
    webcc::webgl::bind_attrib_location("gl", "prog", 0, "position");
    webcc::webgl::bind_attrib_location("gl", "prog", 1, "color");
    webcc::webgl::link_program("gl", "prog");
    
    // Create Buffer
    webcc::webgl::create_buffer("gl", "vbo");
    webcc::webgl::bind_buffer("gl", 0x8892, "vbo"); // GL_ARRAY_BUFFER
    
    // Upload Data
    webcc::webgl::buffer_data("gl", 0x8892, (uint32_t)vertices, sizeof(vertices), 0x88E4); // GL_STATIC_DRAW

    webcc::system::set_main_loop("update");
    
    webcc::flush();
    return 0;
}
