#include "States/SpinningState.h"
#include "GameState.h"
#include "SlotMachine.h"
#include <iostream>

//Вход в состояние "Вращение барабанов".

void SpinningState::Enter(GameState& game) {
    std::cout << "[SpinningState] Enter\n";

    m_time = 0.0f;                // Сброс таймера вращения
    m_stopPressed = false;        // Сбрасываем флаг остановки

    // Настройка кнопок
    game.GetSlotMachine().ShowStartButton(false);
    game.GetSlotMachine().ShowStopButton(true);

    // Запускаем вращение барабанов
    game.GetSlotMachine().StartSpinning();
}

//Обновление состояния "Вращение барабанов".

void SpinningState::Update(GameState& game, float dt) {
    m_time += dt;

    // Если прошло максимальное время вращения и кнопка "Stop" не нажата
    if (m_time >= 7.0f && !m_stopPressed) {
        std::cout << "[SpinningState] Timeout reached\n";
        game.OnTimeOut();
    }

    // Если кнопка "Stop" нажата и барабаны полностью остановились
    if (m_stopPressed && !game.GetSlotMachine().IsSpinning()) {
        bool jackpot = game.GetSlotMachine().CheckJackpot();

        // Переход к состоянию "Показ результата"
        game.GetStateMachine().SetCurrentState(game, "ShowingWin");

        // Передача события "Jackpot" или "NoJackpot" в состояние "Показ результата"
        game.GetStateMachine().HandleEvent(game, jackpot ? "Jackpot" : "NoJackpot");
    }
}

//Выход из состояния "Вращение барабанов".

void SpinningState::Exit(GameState& game) {
    std::cout << "[SpinningState] Exit\n";
}

//Обработка событий в состоянии "Вращение барабанов".

void SpinningState::HandleEvent(GameState& game, const std::string& event) {
    if (event == "StopPressed") {
        std::cout << "[SpinningState] StopPressed event\n";

        m_stopPressed = true; // Устанавливаем флаг остановки
        game.GetSlotMachine().StopSpinning(); // Останавливаем барабаны
    }
    else if (event == "TimeOut") {
        std::cout << "[SpinningState] TimeOut event\n";

        m_stopPressed = true; // Устанавливаем флаг остановки по таймауту
        game.GetSlotMachine().StopSpinning(); // Останавливаем барабаны
    }
}
