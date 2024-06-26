# tetra.c
Spinning tetrahedron, inspired by donut.c. This is a 3D spinning tetrahedron in C, using Tait Bryan angles for intrinsic rotation. The tetrahedron is made up of 4 faces, each with a different character. Rendered in terminal but mileage may vary depending on terminal size and other factors.

```bash
$ gcc tetra.c
$ ./a.out
```

## Demo

## Annotated Code
This is the nonobfuscated version of the code, with comments explaining what each part does.
```c
// Spinning tetrahedron in 3D space, may need to play around with macros to get it to work on your setup (e.g. terminal size, obj size, etc.)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// play around with these
#define TETRA_WIDTH 12
#define MEM_WIDTH 160
#define MEM_HEIGHT 44
#define PROJ_DIST 100

// don't touch these
float A, B, C;
float tetraWidth = 20;
float zBuffer[MEM_WIDTH * MEM_HEIGHT];
char buffer[MEM_WIDTH * MEM_HEIGHT];
int backgroundASCII = ' ';
char faceChars[] = {'#', '*', '=', '.'};  // Characters for each face

// bad kernels
float vertices[4][3] = {
    {-1, -1, -1},
    {1, -1, 1},
    {-1, 1, 1},
    {1, 1, -1}
};

int faces[4][3] = {
    {0, 1, 2},
    {0, 1, 3},
    {0, 2, 3},
    {1, 2, 3}
};

// intrinsic rotation calcs with Tait Bryan angles
float calcX(float i, float j, float k) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
           j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calcY(float i, float j, float k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
           j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
           i * cos(B) * sin(C);
}

float calcZ(float i, float j, float k) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, char ch) {
    float x = calcX(cubeX, cubeY, cubeZ);
    float y = calcY(cubeX, cubeY, cubeZ);
    float z = calcZ(cubeX, cubeY, cubeZ) + PROJ_DIST;

    float ooz = 1 / z;

    int xp = (int)(MEM_WIDTH / 2 + TETRA_WIDTH * 2 * ooz * x);
    int yp = (int)(MEM_HEIGHT / 2 + TETRA_WIDTH * ooz * y);

    if (xp >= 0 && xp < MEM_WIDTH && yp >= 0 && yp < MEM_HEIGHT) {
        int idx = xp + yp * MEM_WIDTH;
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

void render_frame(float A, float B, float C) {
    memset(buffer, backgroundASCII, MEM_WIDTH * MEM_HEIGHT);
    memset(zBuffer, 0, MEM_WIDTH * MEM_HEIGHT * sizeof(float));

    for (int face = 0; face < 4; face++) {
        // i'm so lazy lol
        // a more general implementation would let u scale faces but idc
        float v1x = vertices[faces[face][0]][0] * tetraWidth;
        float v1y = vertices[faces[face][0]][1] * tetraWidth;
        float v1z = vertices[faces[face][0]][2] * tetraWidth;

        float v2x = vertices[faces[face][1]][0] * tetraWidth;
        float v2y = vertices[faces[face][1]][1] * tetraWidth;
        float v2z = vertices[faces[face][1]][2] * tetraWidth;

        float v3x = vertices[faces[face][2]][0] * tetraWidth;
        float v3y = vertices[faces[face][2]][1] * tetraWidth;
        float v3z = vertices[faces[face][2]][2] * tetraWidth;

        for (float i = 0; i < 1; i += 0.01) {
            for (float j = 0; j < 1 - i; j += 0.01) {
                float x = v1x + (v2x - v1x) * i + (v3x - v1x) * j;
                float y = v1y + (v2y - v1y) * i + (v3y - v1y) * j;
                float z = v1z + (v2z - v1z) * i + (v3z - v1z) * j;

                calculateForSurface(x, y, z, faceChars[face]);
            }
        }
    }

    printf("\x1b[H");
    for (int k = 0; k < MEM_WIDTH * MEM_HEIGHT; k++) {
        putchar(k % MEM_WIDTH ? buffer[k] : 10);
    }
}

int main() {
    printf("\x1b[2J"); // clear screen

    // render loop
    while (1) {
        render_frame(A, B, C);
        A += 0.05;
        B += 0.05;
        C += 0.01;
        // FPS
        usleep(30000);
    }

    return 0;
}
```
