#include "States/WaitingForPlayerState.h"
#include "GameState.h"
#include "SlotMachine.h"
#include <iostream>

//Вход в состояние "Ожидание игрока".

void WaitingForPlayerState::Enter(GameState& game) {
    std::cout << "[WaitingForPlayerState] Enter\n";

    // Отображение кнопки "Start" и скрытие кнопки "Stop"
    game.GetSlotMachine().ShowStartButton(true);
    game.GetSlotMachine().ShowStopButton(false);

    // Скрытие текста с результатом предыдущей игры
    game.m_showResultText = false;
}

//Обновление состояния "Ожидание игрока".

void WaitingForPlayerState::Update(GameState& game, float dt) {
    // В данном состоянии ничего не обновляется.
    // Ожидаем действия игрока.
}

//Выход из состояния "Ожидание игрока".

void WaitingForPlayerState::Exit(GameState& game) {
    std::cout << "[WaitingForPlayerState] Exit\n";
}

//Обработка событий в состоянии "Ожидание игрока".

void WaitingForPlayerState::HandleEvent(GameState& game, const std::string& event) {
    if (event == "StartPressed") {
        std::cout << "[WaitingForPlayerState] StartPressed event\n";

        // Переход в состояние "Вращение барабанов"
        game.GetStateMachine().SetCurrentState(game, "Spinning");
    }
}
