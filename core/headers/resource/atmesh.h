#pragma once

#include "../attypes.h"
#include "../athelpers.h"

#include "../backend/GL/atGLAPI.h"

typedef struct ATmeshLayout {
    int idx;
    int* vbo;
    int* vao;
    int* n_verts;
} ATmeshLayout;

typedef struct ATmeshData {
    int count;
    int* vbo;
    int* vao;
    int* n_verts;
} ATmeshData;

void _atDestroyMeshData(ATmeshData* d);
ATerrorType _atInitMeshData(ATmeshData* d, int max);

int _atSetMeshData(ATmeshData* d, int n_verts, float* vertices);
ATmeshLayout* _atGetMeshLayout(ATmeshData* d, int index);
void _atDestroyMeshLayout(ATmeshLayout* l);
