#pragma once

#include "StateMachine.h"
#include <string>

/**
 * Класс состояния, которое отвечает за отображение выигрыша (например, "Джекпот").
 */
class ShowingWinState : public IState {
public:
    // Срабатывает, когда игра переходит в это состояние.
    void Enter(GameState& game) override;

    // Обновление состояния (например, проверка времени, сколько результат отображается).
    void Update(GameState& game, float dt) override;

    // Срабатывает, когда состояние завершает свою работу.
    void Exit(GameState& game) override;

    // Обработка событий, связанных с этим состоянием.
    void HandleEvent(GameState& game, const std::string& event) override;

private:
    bool m_jackpot = false;   // Был ли выигран джекпот.
    float m_showTime = 0.0f;  // Сколько времени отображается результат.
};
