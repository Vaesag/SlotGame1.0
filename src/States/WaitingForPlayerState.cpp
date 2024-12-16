#include "States/WaitingForPlayerState.h"
#include "GameState.h"
#include "SlotMachine.h"
#include <iostream>

void WaitingForPlayerState::Enter(GameState& game) {
    std::cout << "[WaitingForPlayerState] Enter\n";
    game.GetSlotMachine().ShowStartButton(true);
    game.GetSlotMachine().ShowStopButton(false);
    game.m_showResultText = false; // �������� ��������� �� ������ ������
}

void WaitingForPlayerState::Update(GameState& game, float dt) {
    // �������� ������� Start ����� ����.
}

void WaitingForPlayerState::Exit(GameState& game) {
    std::cout << "[WaitingForPlayerState] Exit\n";
}

void WaitingForPlayerState::HandleEvent(GameState& game, const std::string& event) {
    if (event == "StartPressed") {
        std::cout << "[WaitingForPlayerState] StartPressed event\n";
        game.GetStateMachine().SetCurrentState(game, "Spinning");
    }
}
