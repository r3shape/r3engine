#include "../include/r3_shapes2D.h"

R3_Vertex_Data _create_circle2D_impl(R3_Vec2 size, R3_Vec3 color) { return (R3_Vertex_Data) {0}; }

R3_Vertex_Data _create_triangle2D_impl(R3_Vec2 size, R3_Vec3 color) {
    f32 half_width =    size.x / 2.0f;
    f32 half_height =   size.y / 2.0f;

    f32 vertices[] = {
        -half_width, -half_height, 0.0,  color.x, color.y, color.z,   0.0, 0.0,
         half_width, -half_height, 0.0,  color.x, color.y, color.z,   1.0, 0.0,
         0.0,         half_height, 0.0,  color.x, color.y, color.z,   0.5, 1.0
    };

    return r3_graphics_api->create_vertex_data(
        vertices, 3,
        NULL,     0,
        R3_LOCATION_ATTR|R3_COLOR_ATTR|R3_TCOORD_ATTR
    );
}

R3_Vertex_Data _create_quad2D_impl(R3_Vec2 size, R3_Vec3 color) {
    f32 half_width =    size.x / 2.0f;
    f32 half_height =   size.y / 2.0f;

    f32 vertices[] = {
        -half_width, -half_height, 0.0,  color.x, color.y, color.z,   0.0, 0.0,
         half_width, -half_height, 0.0,  color.x, color.y, color.z,   1.0, 0.0,
         half_width,  half_height, 0.0,  color.x, color.y, color.z,   1.0, 1.0,
        -half_width,  half_height, 0.0,  color.x, color.y, color.z,   0.0, 1.0
    };

    ubyte4 indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    return r3_graphics_api->create_vertex_data(
        vertices, 4,
        indices,  6,
        R3_LOCATION_ATTR|R3_COLOR_ATTR|R3_TCOORD_ATTR
    );
}
