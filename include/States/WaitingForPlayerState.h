#pragma once

#include "StateMachine.h"
#include <string>

/**
 * Класс состояния, отвечающего за ожидание действия игрока.
 */
class WaitingForPlayerState : public IState {
public:
    // Выполняется, когда игра переходит в состояние ожидания игрока.
    void Enter(GameState& game) override;

    // Обновление состояния ожидания.
    void Update(GameState& game, float dt) override;

    // Выполняется, когда игра покидает состояние ожидания.
    void Exit(GameState& game) override;

    // Обработка событий, связанных с этим состоянием (например, начало вращения барабанов).
    void HandleEvent(GameState& game, const std::string& event) override;
};
