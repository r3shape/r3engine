#include <stdio.h>
#include "../engine/include/r3.h"

u8 running = 1;
u8 quit_callback1(u16 event_code, R3_Event data) {
    u16 key = data.u16[0];
    if (key == R3_KEY_ESCAPE) running = 0;
    return LIBX_TRUE;
}

u8 quit_callback2(u16 event_code, R3_Event data) {
    if (event_code == R3_EVENT_QUIT) running = 0;
    return LIBX_TRUE;
}

int main() {
    r3_init_core();
    
    R3_Window window = r3_core->platform.create_window("Hello Triangle", 800, 600);
    r3_core->platform.create_gl_context();
    r3_core->graphics.init_gl(&r3_core->graphics);
    
    r3_core->events.register_callback(R3_EVENT_QUIT, quit_callback2);
    r3_core->events.register_callback(R3_EVENT_KEY_PRESSED, quit_callback1);
    
    r3_core->graphics.render_begin(R3_TRIANGLE_MODE, math_api->create_vector(LIBX_VEC4, (f32[4]){60/255.0, 120/255.0, 210/255.0, 255/255.0}), math_api->identity_matrix4());
    
    R3_Shader shader = r3_core->graphics.create_shader(
        fileio_api->read("../engine/assets/shaders/default/vertex.glsl", 0),
        fileio_api->read("../engine/assets/shaders/default/fragment.glsl", 0));

    R3_Vertex_Data vertex_data = r3_core->graphics.create_vertex_data(
        (f32[]){
            -0.5, -0.5, 0.5,    1.0, 0.0, 0.0,
             0.5, -0.5, 0.5,    0.0, 1.0, 0.0,
             0.0,  0.5, 0.5,    0.0, 0.0, 1.0
        }, 3, NULL, 0, R3_LOCATION_ATTR | R3_COLOR_ATTR
    );
    
    Matrix4 u_model = math_api->identity_matrix4();
    Matrix4 u_view = math_api->identity_matrix4();
    r3_core->graphics.set_uniform(&shader, "u_model", &u_model.mat);
    r3_core->graphics.set_uniform(&shader, "u_view", &u_view.mat);

    while (running) {
        r3_core->platform.poll_events();
        r3_core->platform.poll_inputs();
        r3_core->graphics.render_clear();
        
        r3_core->graphics.render_call(R3_TRIANGLE_MODE, &shader, 3, 0, vertex_data.vao);

        r3_core->graphics.send_uniform(&shader, R3_UNIFORM_MAT4, "u_model");
        r3_core->graphics.send_uniform(&shader, R3_UNIFORM_MAT4, "u_view");
        r3_core->graphics.render_end();
        
        r3_core->platform.swap_buffers();
    }
    
    r3_core->events.unregister_callback(R3_EVENT_QUIT, quit_callback2);
    r3_core->events.unregister_callback(R3_EVENT_KEY_PRESSED, quit_callback1);
    
    r3_core->platform.destroy_gl_context();
    r3_core->platform.destroy_window(&window);

    r3_cleanup_core();
    return 0;
}
