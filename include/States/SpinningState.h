#pragma once
#include "StateMachine.h"
#include <string>

class SpinningState : public IState {
public:
    void Enter(GameState& game) override;
    void Update(GameState& game, float dt) override;
    void Exit(GameState& game) override;
    void HandleEvent(GameState& game, const std::string& event) override;

private:
    float m_time = 0.0f;
    bool m_stopPressed = false;
};
