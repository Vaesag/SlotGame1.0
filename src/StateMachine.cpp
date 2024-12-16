#include "StateMachine.h"
#include "GameState.h"
#include <iostream>

//Добавление нового состояния в машину состояний.

void StateMachine::AddState(const std::string& name, std::unique_ptr<IState> state) {
    m_states[name] = std::move(state);
}

/**
 * Установка текущего состояния.
 * Сначала вызывается метод `Exit` текущего состояния, затем `Enter` нового.
 */
void StateMachine::SetCurrentState(GameState& game, const std::string& name) {
    if (m_currentState) {
        std::cout << "[StateMachine] Exiting state...\n";
        m_currentState->Exit(game); // Завершаем текущее состояние.
    }

    m_currentState = m_states[name].get(); // Устанавливаем новое состояние.
    if (m_currentState) {
        std::cout << "[StateMachine] Entering state: " << name << "\n";
        m_currentState->Enter(game); // Вызываем метод Enter нового состояния.
    }
}

/**
 * Обновление текущего состояния.
 * @param game Ссылка на игровой контекст.
 * @param dt Время, прошедшее с предыдущего кадра.
 */
void StateMachine::Update(GameState& game, float dt) {
    if (m_currentState) {
        m_currentState->Update(game, dt); // Вызываем Update текущего состояния.
    }
}

/**
 * Обработка событий текущего состояния.
 * @param game Ссылка на игровой контекст.
 * @param event Имя события, которое нужно обработать.
 */
void StateMachine::HandleEvent(GameState& game, const std::string& event) {
    if (m_currentState) {
        m_currentState->HandleEvent(game, event); // Передаём событие текущему состоянию.
    }
}

