#pragma once

#include "StateMachine.h"
#include "SlotMachine.h"
#include <GL/freeglut.h>
#include <string>

/**
 * Главный класс, управляющий состоянием игры.
 */
class GameState {
public:
    // Конструктор. Инициализирует машину состояний и слот-машину.
    GameState();

    // Основной игровой цикл: обновление состояния.
    void Update(float dt);

    // Отрисовка текущего состояния игры.
    void Render();

    // Обработка изменения размеров окна.
    void OnResize(int width, int height);

    // Событие: нажата кнопка "Start".
    void OnStartButtonPressed();

    // Событие: нажата кнопка "Stop".
    void OnStopButtonPressed();

    // Событие: истекло время вращения барабанов.
    void OnTimeOut();

    // Событие: нажатие кнопкой мыши.
    void OnMouseClick(int x, int y);

    // Получение ссылки на машину состояний.
    StateMachine& GetStateMachine() { return m_stateMachine; }

    // Получение ссылки на слот-машину.
    SlotMachine& GetSlotMachine() { return m_slotMachine; }

    // Текст результата вращения барабанов (например, "Jackpot!").
    std::string m_resultText;

    // Флаг для отображения результата на экране.
    bool m_showResultText = false;

    // Текущий счет игрока.
    int m_score = 0;

private:
    // Машина состояний для управления игровыми этапами.
    StateMachine m_stateMachine;

    // Слот-машина с барабанами.
    SlotMachine m_slotMachine;
};