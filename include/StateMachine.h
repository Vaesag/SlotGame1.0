#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

// Предварительное объявление класса GameState
class GameState;

// Интерфейс состояния (IState) для реализации паттерна "Состояние"
class IState {
public:
    virtual ~IState() {}

    //Вызывается при входе в состояние.
    virtual void Enter(GameState& game) = 0;

    //Обновление состояния. Вызывается в каждом игровом кадре.
    virtual void Update(GameState& game, float dt) = 0;

    //Вызывается при выходе из состояния.
    virtual void Exit(GameState& game) = 0;

    //Обработка событий для текущего состояния.
    virtual void HandleEvent(GameState& game, const std::string& event) = 0;
};

// Класс для управления состояниями (StateMachine)
class StateMachine {
public:
    //Добавление состояния в машину состояний.
    void AddState(const std::string& name, std::unique_ptr<IState> state);

    //Смена текущего состояния.
    void SetCurrentState(GameState& game, const std::string& name);

    //Обновление текущего состояния. Вызывается в каждом игровом кадре.
    void Update(GameState& game, float dt);

    //Передача события текущему состоянию.
    void HandleEvent(GameState& game, const std::string& event);

private:
    std::unordered_map<std::string, std::unique_ptr<IState>> m_states; // Словарь состояний
    IState* m_currentState = nullptr; // Указатель на текущее состояние
};
