#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include "GameState.h"

// Глобальное состояние игры
GameState* g_game = nullptr;

// Колбэк на изменение размера окна
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (g_game) { // Проверяем, инициализирован ли указатель
        g_game->OnResize(width, height);
    }
    else {
        // Если g_game == nullptr, можем вывести предупреждение или ничего не делать
        std::cout << "[framebuffer_size_callback] g_game is null, cannot call OnResize\n";
    }
}

// Колбэк на нажатие кнопки мыши
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "[main] Mouse click at " << xpos << ", " << ypos << "\n";

        if (g_game) { // Проверяем, инициализирован ли указатель
            g_game->OnMouseClick((int)xpos, (int)ypos);
        }
        else {
            std::cout << "[mouse_button_callback] g_game is null, cannot call OnMouseClick\n";
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Slot Machine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    glEnable(GL_TEXTURE_2D);            // Включаем 2D текстуры глобально
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Выравнивание пикселей
    glEnable(GL_BLEND);                 // Включаем смешивание для альфа-канала
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);

    // Теперь создаем GameState, после инициализации OpenGL
    g_game = new GameState();

    // Устанавливаем колбэки
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    g_game->OnResize(800, 600);

    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        float dt = (float)(currentTime - lastTime);
        lastTime = currentTime;

        g_game->Update(dt);
        g_game->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete g_game; // Освобождаем память
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
