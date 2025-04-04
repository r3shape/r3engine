#include <r3/include/r3.h>

u8 running = 1;
u8 quit_callback2(u16 event_code, R3_Event data) {
    u16 key = data.u16[0];
    if (key == R3_KEY_ESCAPE) running = 0;
    return LIBX_TRUE;
}

u8 quit_callback1(u16 event_code, R3_Event data) {
    if (event_code == R3_EVENT_QUIT) running = 0;
    return LIBX_TRUE;
}

u8 resize_callback(u16 event_code, R3_Event data) {
    if (event_code == R3_EVENT_RESIZE) r3_core->graphics.gl.viewport(0, 0, data.u16[0], data.u16[1]);
    return LIBX_TRUE;
}

u8 camera_callback(u16 event_code, R3_Event data) {
    if (event_code == R3_EVENT_MOUSE_MOVE) {
        r3_core->graphics.rotate_camera(data.i16[0], -data.i16[1]);
        return LIBX_TRUE;
    }
    return LIBX_FALSE;
}

int main() {
    r3_init_core();
        
    R3_Window* window = r3_core->platform.create_window("Hello Cube", 800, 600);
    r3_core->platform.create_gl_context();
    r3_core->graphics.init_gl(&r3_core->graphics);
    
    r3_core->events.register_callback(R3_EVENT_QUIT, quit_callback1);
    r3_core->events.register_callback(R3_EVENT_RESIZE, resize_callback);
    r3_core->events.register_callback(R3_EVENT_KEY_PRESSED, quit_callback2);
    r3_core->events.register_callback(R3_EVENT_MOUSE_MOVE, camera_callback);
    
    struct Light {
        Vec3 ambient;
        Vec3 diffuse;
        Vec3 specular;
        Vec3 location;
    } u_light = {
        .ambient = mathx->vec.vec3(0.5, 0.5, 0.5),
        .diffuse = mathx->vec.vec3(0.3, 0.3, 0.3),
        .specular = mathx->vec.vec3(1.0, 1.0, 1.0),
        .location = mathx->vec.vec3(-2, 0.0, -2*32)
    };
    
    struct Material {
        f32 shine;
        Vec3 ambient;
        Vec3 diffuse;
        Vec3 specular;
    } u_material = {
        .shine = 32.0,
        .ambient = mathx->vec.vec3(1.0, 0.5, 0.31),
        .diffuse = mathx->vec.vec3(1.0, 0.5, 0.31),
        .specular = mathx->vec.vec3(0.5, 0.5, 0.5)
    };
    
    R3_Shader shader = r3_core->graphics.create_shader(
        filex->read("assets/shaders/light/shader.vert", 0),
        filex->read("assets/shaders/light/shader.frag", 0)
    );
    
    r3_core->graphics.set_uniform(&shader, &(R3_Uniform){.type = R3_UNIFORM_VEC3, .name = "u_light.ambient", .value = &u_light.ambient});
    r3_core->graphics.set_uniform(&shader, &(R3_Uniform){.type = R3_UNIFORM_VEC3, .name = "u_light.diffuse", .value = &u_light.diffuse});
    r3_core->graphics.set_uniform(&shader, &(R3_Uniform){.type = R3_UNIFORM_VEC3, .name = "u_light.specular", .value = &u_light.specular});
    r3_core->graphics.set_uniform(&shader, &(R3_Uniform){.type = R3_UNIFORM_VEC3, .name = "u_light.location", .value = &u_light.location});

    // TODO: debug why this float uniform types appear to not be set properly
    r3_core->graphics.set_uniform(&shader, &(R3_Uniform){.type = R3_UNIFORM_FLOAT, .name = "u_material.shine", .value = &u_material.shine});
    r3_core->graphics.set_uniform(&shader, &(R3_Uniform){.type = R3_UNIFORM_VEC3, .name = "u_material.ambient", .value = &u_material.ambient});
    r3_core->graphics.set_uniform(&shader, &(R3_Uniform){.type = R3_UNIFORM_VEC3, .name = "u_material.diffuse", .value = &u_material.diffuse});
    r3_core->graphics.set_uniform(&shader, &(R3_Uniform){.type = R3_UNIFORM_VEC3, .name = "u_material.specular", .value = &u_material.specular});

    R3_Shader shader2 = r3_core->graphics.create_shader(
        filex->read("assets/shaders/light/source.vert", 0),
        filex->read("assets/shaders/light/source.frag", 0)
    );

    R3_Texture texture = r3_core->graphics.create_texture2D("assets/textures/logo.png", R3_RGBA_FORMAT);
    
    f32 speed = 0.5;
    f32 rotation = 0.0;
    Mat4 u_model = mathx->mat.identity4();
    Vec3 location = mathx->vec.vec3(0, 0, 0);
    R3_Vertex_Data vertex_data = r3_core->graphics.create_vertex_data(
        (f32[]){
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        }, 36, NULL, 0, R3_LOCATION_ATTR | R3_NORMAL_ATTR
    );
    
    Mat4 u_model2 = mathx->mat.identity4();

    if (r3_core->graphics.init_pipeline(
        R3_TRIANGLE_MODE, &shader,
        mathx->mat.perspective(60.0, 800/600, 0.1, 1000)
    )) printf("render pipeline initialized\n");
    else printf("render pipeline failed to be initialized!\n");

    if (r3_core->graphics.init_camera(
        mathx->vec.vec3(0, 0, 3),
        mathx->vec.vec3(0, 0, 1),
        mathx->vec.vec3(0, 1, 0)
    )) printf("camera initialized!\n");
    else printf("camera failed to be initialized!\n");
    r3_core->graphics.camera.speed = 0.5;
    r3_core->graphics.camera.sensitivity = 0.05;

    r3_core->platform.hide_cursor();
    r3_core->platform.center_cursor();
    while (running) {
        r3_core->platform.poll_events();
        r3_core->platform.poll_inputs();
        
        if (r3_core->input.key_is_down(R3_KEY_F1)) r3_core->graphics.toggle_wireframe(1);
        else r3_core->graphics.toggle_wireframe(0);
        
        if (r3_core->input.key_is_down(R3_KEY_UP)) u_light.location.y += speed;
        if (r3_core->input.key_is_down(R3_KEY_DOWN)) u_light.location.y -= speed;
        if (r3_core->input.key_is_down(R3_KEY_LEFT)) u_light.location.x -= speed;
        if (r3_core->input.key_is_down(R3_KEY_RIGHT)) u_light.location.x += speed;
        
        if (r3_core->input.key_is_down(R3_KEY_A)) r3_core->graphics.translate_camera(-1, 0, 0);
        if (r3_core->input.key_is_down(R3_KEY_D)) r3_core->graphics.translate_camera( 1, 0, 0);
        if (r3_core->input.key_is_down(R3_KEY_W)) r3_core->graphics.translate_camera( 0, 0, 1);
        if (r3_core->input.key_is_down(R3_KEY_S)) r3_core->graphics.translate_camera( 0, 0,-1);
        if (r3_core->input.key_is_down(R3_KEY_SPACE)) r3_core->graphics.translate_camera(0,  1, 0);
        if (r3_core->input.key_is_down(R3_KEY_SHIFT)) r3_core->graphics.translate_camera(0, -1, 0);
        
        u_model = mathx->mat.identity4();
        u_model = mathx->mat.mult4(u_model, mathx->mat.scale4(32, 32, 32));
        u_model = mathx->mat.mult4(u_model, mathx->mat.trans4(location.x, location.y, location.z));
        
        u_model2 = mathx->mat.identity4();
        u_model2 = mathx->mat.mult4(u_model2, mathx->mat.scale4(32, 32, 32));
        u_model2 = mathx->mat.mult4(u_model2, mathx->mat.trans4(u_light.location.x, u_light.location.y, u_light.location.z));
        
        r3_core->graphics.push_pipeline(&vertex_data, &u_model, NULL, &texture, R3_TRIANGLE_MODE, R3_RENDER_ARRAYS);
        r3_core->graphics.push_pipeline(&vertex_data, &u_model2, &shader2, &texture, R3_TRIANGLE_MODE, R3_RENDER_ARRAYS);
        
        r3_core->graphics.update_camera();
        r3_core->graphics.flush_pipeline();
        r3_core->platform.swap_buffers();
    }
    
    r3_core->events.unregister_callback(R3_EVENT_QUIT, quit_callback1);
    r3_core->events.unregister_callback(R3_EVENT_RESIZE, resize_callback);
    r3_core->events.unregister_callback(R3_EVENT_KEY_PRESSED, quit_callback2);
    r3_core->events.unregister_callback(R3_EVENT_MOUSE_MOVE, camera_callback);
    
    r3_core->platform.destroy_gl_context();
    r3_core->platform.destroy_window();

    r3_cleanup_core();
    return 0;
}