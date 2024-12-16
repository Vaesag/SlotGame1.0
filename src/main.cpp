#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include "GameState.h"

// Глобальная переменная для хранения состояния игры
GameState* g_game = nullptr;

/**
 * Колбэк для обработки изменения размеров окна.
 * @param window Указатель на текущее окно.
 * @param width Новая ширина окна.
 * @param height Новая высота окна.
 */
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (g_game) {
        g_game->OnResize(width, height);
    }
    else {
        std::cout << "[framebuffer_size_callback] g_game is null, cannot call OnResize\n";
    }
}

//Колбэк для обработки нажатий мыши.

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
    // Инициализация GLUT (требуется для некоторых функций отрисовки текста)
    glutInit(&argc, argv);

    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Установка версии OpenGL (Compatibility Profile 2.1)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Создание окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "Slot Machine", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Установка контекста OpenGL
    glfwMakeContextCurrent(window);

    // Инициализация GLEW
    glewInit();

    // Настройки OpenGL
    glEnable(GL_TEXTURE_2D);            // Включение 2D текстур
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Выравнивание данных текстур
    glEnable(GL_BLEND);                 // Включение смешивания для альфа-канала
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Установка смешивания
    glShadeModel(GL_SMOOTH);            // Гладкое освещение

    // Создание игрового состояния
    g_game = new GameState();

    // Установка колбэков
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Первоначальная настройка размера окна
    g_game->OnResize(800, 600);

    // Главный цикл приложения
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        // Расчёт времени между кадрами
        double currentTime = glfwGetTime();
        float dt = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        // Обновление и отрисовка игрового состояния
        g_game->Update(dt);
        g_game->Render();

        // Смена кадров
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Освобождение ресурсов
    delete g_game;
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
