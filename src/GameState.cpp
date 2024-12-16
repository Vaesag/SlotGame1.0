#include "GameState.h"
#include "States/WaitingForPlayerState.h"
#include "States/SpinningState.h"
#include "States/ShowingWinState.h"
#include <iostream>

static void RenderBigText(int x, int y, const char* text) {
    glColor3f(1.0f, 1.0f, 0.0f);
    glRasterPos2i(x, y);
    for (const char* p = text; *p; p++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
    }
}

static void RenderText(int x, int y, const char* text) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(x, y);
    for (const char* p = text; *p; p++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
    }
}

GameState::GameState() {
    m_stateMachine.AddState("WaitingForPlayer", std::make_unique<WaitingForPlayerState>());
    m_stateMachine.AddState("Spinning", std::make_unique<SpinningState>());
    m_stateMachine.AddState("ShowingWin", std::make_unique<ShowingWinState>());

    m_stateMachine.SetCurrentState(*this, "WaitingForPlayer");

    m_score = 0;
}

void GameState::Update(float dt) {
    m_stateMachine.Update(*this, dt);
    m_slotMachine.Update(dt);
}

void GameState::Render() {
    m_slotMachine.Render();

    int symbolSize = 100;
    int reelCount = 4;
    int visibleSymbols = 3;
    int totalWidth = reelCount * symbolSize;
    int totalHeight = visibleSymbols * symbolSize;
    int startX = (m_slotMachine.GetWidth() - totalWidth) / 2;
    int startY = (m_slotMachine.GetHeight() - totalHeight) / 2;

    int scoreY = startY - 50;
    std::string scoreStr = "Score: " + std::to_string(m_score);
    int textWidth = (int)scoreStr.size() * 9;
    int scoreX = (m_slotMachine.GetWidth() - textWidth) / 2;
    RenderBigText(scoreX, scoreY, scoreStr.c_str());

    if (m_showResultText) {
        int textY = startY + totalHeight + 50;
        int textWidth = (int)m_resultText.size() * 9;
        int x = (m_slotMachine.GetWidth() - textWidth) / 2;
        RenderBigText(x, textY, m_resultText.c_str());
    }
}

void GameState::OnResize(int width, int height) {
    m_slotMachine.OnResize(width, height);
}

void GameState::OnStartButtonPressed() {
    std::cout << "[GameState] Start button pressed\n";
    m_stateMachine.HandleEvent(*this, "StartPressed");
}

void GameState::OnStopButtonPressed() {
    std::cout << "[GameState] Stop button pressed\n";
    m_stateMachine.HandleEvent(*this, "StopPressed");
}

void GameState::OnTimeOut() {
    std::cout << "[GameState] Timeout event\n";
    m_stateMachine.HandleEvent(*this, "TimeOut");
}

void GameState::OnMouseClick(int x, int y) {
    std::cout << "[GameState] Mouse click at: " << x << ", " << y << "\n";
    ButtonType btn = m_slotMachine.CheckButtonClick(x, y);
    if (btn == ButtonType::Start) {
        OnStartButtonPressed();
    }
    else if (btn == ButtonType::Stop) {
        OnStopButtonPressed();
    }
    else {
        std::cout << "[GameState] Click not on a button.\n";
    }
}