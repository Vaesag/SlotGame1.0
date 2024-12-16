#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include "GameState.h"

// ���������� ���������� ��� �������� ��������� ����
GameState* g_game = nullptr;

/**
 * ������ ��� ��������� ��������� �������� ����.
 * @param window ��������� �� ������� ����.
 * @param width ����� ������ ����.
 * @param height ����� ������ ����.
 */
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (g_game) {
        g_game->OnResize(width, height);
    }
    else {
        std::cout << "[framebuffer_size_callback] g_game is null, cannot call OnResize\n";
    }
}

//������ ��� ��������� ������� ����.

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "[main] Mouse click at " << xpos << ", " << ypos << "\n";

        if (g_game) {
            g_game->OnMouseClick(static_cast<int>(xpos), static_cast<int>(ypos));
        }
        else {
            std::cout << "[mouse_button_callback] g_game is null, cannot call OnMouseClick\n";
        }
    }
}

int main(int argc, char** argv) {
    // ������������� GLUT (��������� ��� ��������� ������� ��������� ������)
    glutInit(&argc, argv);

    // ������������� GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // ��������� ������ OpenGL (Compatibility Profile 2.1)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // �������� ����
    GLFWwindow* window = glfwCreateWindow(800, 600, "Slot Machine", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // ��������� ��������� OpenGL
    glfwMakeContextCurrent(window);

    // ������������� GLEW
    glewInit();

    // ��������� OpenGL
    glEnable(GL_TEXTURE_2D);            // ��������� 2D �������
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // ������������ ������ �������
    glEnable(GL_BLEND);                 // ��������� ���������� ��� �����-������
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // ��������� ����������
    glShadeModel(GL_SMOOTH);            // ������� ���������

    // �������� �������� ���������
    g_game = new GameState();

    // ��������� ��������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // �������������� ��������� ������� ����
    g_game->OnResize(800, 600);

    // ������� ���� ����������
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        // ������ ������� ����� �������
        double currentTime = glfwGetTime();
        float dt = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        // ���������� � ��������� �������� ���������
        g_game->Update(dt);
        g_game->Render();

        // ����� ������
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ������������ ��������
    delete g_game;
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
