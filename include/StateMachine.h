#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

class GameState;

class IState {
public:
    virtual ~IState() {}
    virtual void Enter(GameState& game) = 0;
    virtual void Update(GameState& game, float dt) = 0;
    virtual void Exit(GameState& game) = 0;
    virtual void HandleEvent(GameState& game, const std::string& event) = 0;
};

class StateMachine {
public:
    void AddState(const std::string& name, std::unique_ptr<IState> state);
    void SetCurrentState(GameState& game, const std::string& name);
    void Update(GameState& game, float dt);
    void HandleEvent(GameState& game, const std::string& event);

private:
    std::unordered_map<std::string, std::unique_ptr<IState>> m_states;
    IState* m_currentState = nullptr;
};