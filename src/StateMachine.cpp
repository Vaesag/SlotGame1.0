#include "StateMachine.h"
#include "GameState.h"
#include <iostream>

//���������� ������ ��������� � ������ ���������.

void StateMachine::AddState(const std::string& name, std::unique_ptr<IState> state) {
    m_states[name] = std::move(state);
}

/**
 * ��������� �������� ���������.
 * ������� ���������� ����� `Exit` �������� ���������, ����� `Enter` ������.
 */
void StateMachine::SetCurrentState(GameState& game, const std::string& name) {
    if (m_currentState) {
        std::cout << "[StateMachine] Exiting state...\n";
        m_currentState->Exit(game); // ��������� ������� ���������.
    }

    m_currentState = m_states[name].get(); // ������������� ����� ���������.
    if (m_currentState) {
        std::cout << "[StateMachine] Entering state: " << name << "\n";
        m_currentState->Enter(game); // �������� ����� Enter ������ ���������.
    }
}

/**
 * ���������� �������� ���������.
 * @param game ������ �� ������� ��������.
 * @param dt �����, ��������� � ����������� �����.
 */
void StateMachine::Update(GameState& game, float dt) {
    if (m_currentState) {
        m_currentState->Update(game, dt); // �������� Update �������� ���������.
    }
}

/**
 * ��������� ������� �������� ���������.
 * @param game ������ �� ������� ��������.
 * @param event ��� �������, ������� ����� ����������.
 */
void StateMachine::HandleEvent(GameState& game, const std::string& event) {
    if (m_currentState) {
        m_currentState->HandleEvent(game, event); // ������� ������� �������� ���������.
    }
}

