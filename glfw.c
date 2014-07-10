#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 640
#define HEIGHT 480

#define FOV 70

#define MOUSE_SPEED 2

#define BOOST_MUL 2

#define DEG_RAD(d) ((float)(d) * M_PI / 180)

static float yaw = 0, pitch = 0;
static float x = 0, y = 0, z = 0;
static int forward = 0, up = 0, right = 0;
static bool boost = false;
static bool mouse_grabbed = false;

void error_callback(int, const char*);

void mouse_button_callback(GLFWwindow *, int, int, int);
void key_callback(GLFWwindow *, int, int, int, int);
void mouse_resolve(GLFWwindow *);

void framebuffer_size_callback(GLFWwindow *, int, int);

void display(void);
double get_delta();

int main(int argc, char **argv)
{
    GLFWwindow *window;

    if (!glfwInit())
        return 1;

    if (!(window = glfwCreateWindow(640, 480, "Test.", NULL, NULL))) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glfwSetErrorCallback(error_callback);

    glEnable(GL_DEPTH_TEST);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (mouse_grabbed)
            mouse_resolve(window);

        display();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
    exit(error);
}

void display(void)
{
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_DEPTH_BUFFER_BIT);

    double delta = get_delta();

    float cos_pitch = cosf(DEG_RAD(pitch));

    float lx = -cos_pitch * sinf(DEG_RAD(yaw));
    float ly = sinf(DEG_RAD(pitch));
    float lz = -cos_pitch * cosf(DEG_RAD(yaw));

    x += lx * forward * delta * 10;
    y += ly * forward * delta * 10;
    z += lz * forward * delta * 10;

    y += 1.0 * up * delta * 10;

    x -= lz * right * delta * 10;
    z += lx * right * delta * 10;

    glLoadIdentity();

    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0, 1, 0);

    glTranslatef(0, 0, -5);

    glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex3f(-1, -1, 0);
        glColor3f(1, 1, 0);
        glVertex3f(1, -1, 0);
        glColor3f(0, 1, 1);
        glVertex3f(1, 1, 0);
        glColor3f(1, 0, 1);
        glVertex3f(-1, 1, 0);
    glEnd();

    glTranslatef(0, -3, 5);

    glBegin(GL_QUADS);
        glColor3f(0.5, 0, 0);
        glVertex3f(-100, 0, -100);
        glVertex3f(100, 0, -100);
        glColor3f(0, 0.5, 0);
        glVertex3f(100, 0, 100);
        glVertex3f(-100, 0, 100);
    glEnd();
}

double get_delta()
{
    static double last_time = 0;

    double time = glfwGetTime();

    double delta = time - last_time;

    last_time = time;

    return delta;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
        mouse_grabbed = !mouse_grabbed;
    int cmode = mouse_grabbed ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL;

    glfwSetInputMode(window, GLFW_CURSOR, cmode);
}

void cursor_enter_callback(GLFWwindow *window, int entered)
{
    if (entered == GL_TRUE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void mouse_resolve(GLFWwindow *window)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    glfwSetCursorPos(window, width / 2, height / 2);

    float dpp = (float)FOV / (float)width;

    int dx = xpos - width / 2;
    int dy = ypos - height / 2;

    yaw -= dx * dpp * MOUSE_SPEED;
    pitch -= dy * dpp * MOUSE_SPEED;

    if (yaw > 180) yaw -= 360;
    if (yaw <= -180) yaw += 360;
    if (pitch > 89.9) pitch = 89.9;
    if (pitch < -89.9) pitch = -89.9;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        action = 1;
    } else if (action == GLFW_RELEASE) {
        action = -1;
    }

    switch (key) {
        case GLFW_KEY_W: forward += action;
                         break;
        case GLFW_KEY_S: forward -= action;
                         break;

        case GLFW_KEY_Z: up += action;
                         break;
        case GLFW_KEY_X: up -= action;
                         break;

        case GLFW_KEY_D: right += action;
                         break;
        case GLFW_KEY_A: right -= action;
                         break;
        case GLFW_KEY_LEFT_SHIFT: ;
                                  break;
    }

    if (forward > 1) forward = 1;
    if (forward < -1) forward = -1;

    if (up > 1) up = 1;
    if (up < -1) up = -1;

    if (right > 1) right = 1;
    if (right < -1) right = -1;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    if (height == 0)
        height = 1;

    float ratio = (float)width / (float)height;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, width, height);

    gluPerspective(FOV, ratio, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}
