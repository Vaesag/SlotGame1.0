#pragma once
#include "StateMachine.h"
#include <string>

class ShowingWinState : public IState {
public:
    void Enter(GameState& game) override;
    void Update(GameState& game, float dt) override;
    void Exit(GameState& game) override;
    void HandleEvent(GameState& game, const std::string& event) override;

private:
    bool m_jackpot = false;
    float m_showTime = 0.0f;
};

