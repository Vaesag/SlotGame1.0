#include "States/SpinningState.h"
#include "GameState.h"
#include "SlotMachine.h"
#include <iostream>

void SpinningState::Enter(GameState& game) {
    std::cout << "[SpinningState] Enter\n";
    m_time = 0.0f;
    m_stopPressed = false;
    game.GetSlotMachine().ShowStartButton(false);
    game.GetSlotMachine().ShowStopButton(true);
    game.GetSlotMachine().StartSpinning();
}

void SpinningState::Update(GameState& game, float dt) {
    m_time += dt;
    if (m_time >= 7.0f && !m_stopPressed) {
        std::cout << "[SpinningState] Timeout reached\n";
        game.OnTimeOut();
    }

    if (m_stopPressed && !game.GetSlotMachine().IsSpinning()) {
        bool jackpot = game.GetSlotMachine().CheckJackpot();
        game.GetStateMachine().SetCurrentState(game, "ShowingWin");
        game.GetStateMachine().HandleEvent(game, jackpot ? "Jackpot" : "NoJackpot");
    }
}

void SpinningState::Exit(GameState& game) {
    std::cout << "[SpinningState] Exit\n";
}

void SpinningState::HandleEvent(GameState& game, const std::string& event) {
    if (event == "StopPressed") {
        std::cout << "[SpinningState] StopPressed event\n";
        m_stopPressed = true;
        game.GetSlotMachine().StopSpinning();
    }
    else if (event == "TimeOut") {
        std::cout << "[SpinningState] TimeOut event\n";
        m_stopPressed = true;
        game.GetSlotMachine().StopSpinning();
    }
}
