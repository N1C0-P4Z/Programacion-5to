#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NB_COLS 239
#define NB_ROWS 58

char screen[NB_ROWS][NB_COLS];
char cleared_screen[NB_ROWS][NB_COLS];
char buffer[3 + NB_ROWS * (NB_COLS + 1)];

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    float x, y;
} Vec2;

const Vec3 cube_vertices[8] = {
    { -1, -1, -1 }, // 0
    { -1,  1, -1 }, // 1
    {  1,  1, -1 }, // 2
    {  1, -1, -1 }, // 3
    {  1,  1,  1 }, // 4
    {  1, -1,  1 }, // 5
    { -1, -1,  1 }, // 6
    { -1,  1,  1 }  // 7
};

const unsigned char cube_triangles[12][3] = {
    // front face
    { 0, 1, 2 },
    { 0, 2, 3 },
    // right
    { 3, 2, 4 },
    { 3, 4, 5 },
    // back
    { 5, 4, 7 },
    { 5, 7, 6 },
    // left
    { 6, 7, 1 },
    { 6, 1, 0 },
    // top
    { 6, 0, 3 },
    { 6, 3, 5 },
    // bottom
    { 1, 7, 4 },
    { 1, 4, 2 }
};

const char symbols[] = "$$**++--@@==";
const Vec3 camera_v = { 0, 0, 1 };

long long prev_time_ns;
long long target_delta_time_ns = 16666667; // 60 FPS

void displayScreen() {
    for (int i = 0; i < NB_ROWS; i++) {
        const int offset = 3 + i * (NB_COLS + 1);
        memcpy(buffer + offset, screen[i], NB_COLS);
        buffer[offset + NB_COLS] = '\n';
    }
    write(STDOUT_FILENO, buffer, sizeof(buffer));
}

void clearScreen() {
    memset(screen, ' ', sizeof(screen));
}

float dot_product(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross_product(Vec3 a, Vec3 b) {
    Vec3 result = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return result;
}

Vec3 rotateAroundY(Vec3 v, float rotation_angle_rad) {
    Vec3 result = {
        cosf(rotation_angle_rad) * v.x + sinf(rotation_angle_rad) * v.z,
        v.y,
        -sinf(rotation_angle_rad) * v.x + cosf(rotation_angle_rad) * v.z
    };
    return result;
}

Vec3 rotateAroundZ(Vec3 v, float rotation_angle_rad) {
    Vec3 result = {
        cosf(rotation_angle_rad) * v.x - sinf(rotation_angle_rad) * v.y,
        sinf(rotation_angle_rad) * v.x + cosf(rotation_angle_rad) * v.y,
        v.z
    };
    return result;
}

Vec3 rotateAroundX(Vec3 v, float rotation_angle_rad) {
    Vec3 result = {
        v.x,
        cosf(rotation_angle_rad) * v.y - sinf(rotation_angle_rad) * v.z,
        sinf(rotation_angle_rad) * v.y + cosf(rotation_angle_rad) * v.z
    };
    return result;
}

Vec2 project(Vec3 v) {
    Vec2 result = {
        roundf(v.x / v.z + NB_COLS / 2.0f),
        roundf(v.y / v.z + NB_ROWS / 2.0f)
    };
    return result;
}

void drawScanLine(int y, int x0, int x1, char symbol) {
    if (y < 0 || y >= NB_ROWS) return;
    
    int left = x0 < x1 ? x0 : x1;
    int right = x0 < x1 ? x1 : x0;
    
    if (left < 0) left = 0;
    if (right >= NB_COLS) right = NB_COLS - 1;
    
    for (int x = left; x <= right; x++) {
        screen[y][x] = symbol;
    }
}

void drawFlatBottom(Vec2 t, Vec2 b0, Vec2 b1, char symbol) {
    float x_b = t.x;
    float x_e = t.x;

    float x_dec_0 = (t.x - b0.x) / (b0.y - t.y);
    float x_dec_1 = (t.x - b1.x) / (b1.y - t.y);

    int y_b = (int)t.y;
    int y_e = (int)(b0.y + 1);
    
    for (int y = y_b; y < y_e; y++) {
        drawScanLine(y, (int)roundf(x_b), (int)roundf(x_e), symbol);
        x_b -= x_dec_0;
        x_e -= x_dec_1;
    }
}

void drawFlatTop(Vec2 t0, Vec2 t1, Vec2 b, char symbol) {
    float x_b = t0.x;
    float x_e = t1.x;

    float x_inc_0 = (b.x - t0.x) / (b.y - t0.y);
    float x_inc_1 = (b.x - t1.x) / (b.y - t1.y);

    int y_b = (int)t0.y;
    int y_e = (int)(b.y + 1);
    
    for (int y = y_b; y < y_e; y++) {
        drawScanLine(y, (int)roundf(x_b), (int)roundf(x_e), symbol);
        x_b += x_inc_0;
        x_e += x_inc_1;
    }
}

void drawTriangle(Vec2 vec0, Vec2 vec1, Vec2 vec2, char symbol) {
    Vec2 v0 = vec0;
    Vec2 v1 = vec1;
    Vec2 v2 = vec2;
    
    // Sort the vertices by ASC y
    if (v0.y > v1.y) {
        Vec2 tmp = v0;
        v0 = v1;
        v1 = tmp;
    }
    
    if (v1.y > v2.y) {
        Vec2 tmp = v2;
        v2 = v1;
        v1 = tmp;
    }
    
    if (v0.y > v1.y) {
        Vec2 tmp = v0;
        v0 = v1;
        v1 = tmp;
    }

    if (v2.y == v1.y) {
        drawFlatBottom(v0, v1, v2, symbol);
        return;
    }

    if (v0.y == v1.y) {
        drawFlatTop(v0, v1, v2, symbol);
        return;
    }

    // Find the midpoint
    Vec2 midpoint = {
        v0.x + (v2.x - v0.x) * (v1.y - v0.y) / (v2.y - v0.y),
        v1.y
    };
    
    drawFlatBottom(v0, v1, midpoint, symbol);
    drawFlatTop(v1, midpoint, v2, symbol);
}

void drawCube(float rx, float ry, float rz) {
    for (int s = 0; s < 12; s++) {
        Vec3 transformed_vertices[3];
        
        for (int i = 0; i < 3; i++) {
            transformed_vertices[i] = cube_vertices[cube_triangles[s][i]];
            // Rotate it
            transformed_vertices[i] = rotateAroundX(transformed_vertices[i], rx);
            transformed_vertices[i] = rotateAroundY(transformed_vertices[i], ry);
            transformed_vertices[i] = rotateAroundZ(transformed_vertices[i], rz);
            // Push it into screen
            transformed_vertices[i].z += 8;
            // Scale it
            const float scale = 60;
            transformed_vertices[i].y *= scale;
            transformed_vertices[i].x *= scale * 3;
        }
        
        // Back-face culling
        Vec3 v_01 = {
            transformed_vertices[1].x - transformed_vertices[0].x,
            transformed_vertices[1].y - transformed_vertices[0].y,
            transformed_vertices[1].z - transformed_vertices[0].z
        };
        
        Vec3 v_02 = {
            transformed_vertices[2].x - transformed_vertices[0].x,
            transformed_vertices[2].y - transformed_vertices[0].y,
            transformed_vertices[2].z - transformed_vertices[0].z
        };
        
        Vec3 normal = cross_product(v_01, v_02);
        
        if (dot_product(camera_v, normal) >= 0) {
            continue;
        }

        // Project 2D points
        Vec2 projected_points[3];
        for (int i = 0; i < 3; i++) {
            projected_points[i] = project(transformed_vertices[i]);
        }
        
        // Draw the triangle
        drawTriangle(projected_points[0], projected_points[1], projected_points[2], symbols[s]);
    }
}

void setTargetFPS(int fps) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    prev_time_ns = ts.tv_sec * 1000000000LL + ts.tv_nsec;
    target_delta_time_ns = 1000000000LL / fps;
}

float getDeltaTime() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long long now = ts.tv_sec * 1000000000LL + ts.tv_nsec;
    long long delta_t_ns = now - prev_time_ns;
    prev_time_ns = now;
    
    long long sleep_time = target_delta_time_ns - delta_t_ns;
    if (sleep_time > 0) {
        struct timespec sleep_ts = {
            .tv_sec = sleep_time / 1000000000LL,
            .tv_nsec = sleep_time % 1000000000LL
        };
        nanosleep(&sleep_ts, NULL);
    }
    
    return (float)delta_t_ns * 1e-9f;
}

int main() {
    for (int i = 0; i < NB_ROWS; i++) {
        for (int j = 0; j < NB_COLS; j++) {
            cleared_screen[i][j] = ' ';
        }
    }    setTargetFPS(60);
    
    // Clear screen and hide cursor
    write(STDOUT_FILENO, "\x1B[2J\x1B[?25l", 8);
    // Put cursor at position (0, 0)
    buffer[0] = '\x1B';
    buffer[1] = '[';
    buffer[2] = 'H';
    
    memset(cleared_screen, ' ', sizeof(cleared_screen));
    
    float rx = 0.0f;
    float ry = 0.0f;
    float rz = 0.0f;
    
    while (1) {
        float delta_time = getDeltaTime();
        clearScreen();
        drawCube(rx, ry, rz);
        displayScreen();
        
        rx = fmodf(rx + 0.8f * delta_time, 2 * M_PI);
        ry = fmodf(ry + 0.8f * delta_time, 2 * M_PI);
        rz = fmodf(rz + 0.8f * delta_time, 2 * M_PI);
    }
    
    return 0;
}
