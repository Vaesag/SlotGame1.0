#pragma once

#include "StateMachine.h"
#include <string>

/**
 *  ласс состо€ни€, отвечающего за вращение барабанов.
 */
class SpinningState : public IState {
public:
    // ¬ыполн€етс€, когда игра переходит в состо€ние вращени€ барабанов.
    void Enter(GameState& game) override;

    // ќбновление состо€ни€ (например, обновление времени и вращени€ барабанов).
    void Update(GameState& game, float dt) override;

    // ¬ыполн€етс€, когда состо€ние завершает свою работу.
    void Exit(GameState& game) override;

    // ќбработка событий, св€занных с этим состо€нием (например, остановка барабанов).
    void HandleEvent(GameState& game, const std::string& event) override;

private:
    float m_time = 0.0f;       // ¬рем€, прошедшее с момента начала вращени€.
    bool m_stopPressed = false; // ‘лаг, указывающий, была ли нажата кнопка "—топ".
};
