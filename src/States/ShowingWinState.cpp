#include "States/ShowingWinState.h"
#include "GameState.h"
#include <iostream>

// Функция для подсчёта очков на основе символов в центральной линии
static int CalculateScore(const std::vector<Symbol>& line) {
    // line содержит 4 символа (т.к. REEL_COUNT=4)
    // Нужно определить количество одинаковых символов:
    // Посчитаем частоту каждого символа:
    std::map<Symbol, int> freq;
    for (auto s : line) {
        freq[s]++;
    }

    // Найдём максимум частоты и какой символ
    Symbol mainSym;
    int maxCount = 0;
    for (auto& kv : freq) {
        if (kv.second > maxCount) {
            maxCount = kv.second;
            mainSym = kv.first;
        }
    }

    // Если maxCount <3, значит очков нет
    if (maxCount < 3) return 0;

    // Определяем очки в зависимости от символа и количества
    // Три одинаковых: Клубника (10), Виноград (25), Ананас (50), Лимон (100)
    // Четыре одинаковых: Клубника (125), Виноград (250), Ананас (500), Лимоны (10000)

    bool four = (maxCount == 4);

    int score = 0;
    switch (mainSym) {
    case Symbol::Strawberry:
        if (four) score = 125; else score = 10;
        break;
    case Symbol::Grapes:
        if (four) score = 250; else score = 25;
        break;
    case Symbol::Pineapple:
        if (four) score = 500; else score = 50;
        break;
    case Symbol::Lemon:
        if (four) score = 10000; else score = 100;
        break;
    }
    return score;
}

void ShowingWinState::Enter(GameState& game) {
    std::cout << "[ShowingWinState] Enter\n";
    m_showTime = 0.0f;
}

void ShowingWinState::Update(GameState& game, float dt) {
    m_showTime += dt;
    if (m_showTime > 5.0f) {
        std::cout << "[ShowingWinState] Time to go back to WaitingForPlayer\n";
        game.GetStateMachine().SetCurrentState(game, "WaitingForPlayer");
    }
}

void ShowingWinState::Exit(GameState& game) {
    std::cout << "[ShowingWinState] Exit\n";
    game.m_showResultText = false;
}

void ShowingWinState::HandleEvent(GameState& game, const std::string& event) {
    // Получим символы на центральной линии
    std::vector<Symbol> lineSymbols;
    lineSymbols.reserve(4);
    for (int i = 0; i < 4; ++i) {
        lineSymbols.push_back(game.GetSlotMachine().GetSymbolAtCentralLine(i));
    }

    if (event == "Jackpot") {
        m_jackpot = true;
        game.m_resultText = "Jackpot!";
        game.m_showResultText = true;
        std::cout << "[ShowingWinState] Jackpot!\n";

        // Здесь 4 одинаковых символа гарантированно
        int addScore = CalculateScore(lineSymbols);
        if (addScore > 0) {
            game.m_score += addScore;
        }

    }
    else if (event == "NoJackpot") {
        m_jackpot = false;
        // Не все 4 одинаковые.
        // Проверим, может 3 одинаковых?
        int addScore = CalculateScore(lineSymbols);
        if (addScore > 0) {
            // Значит было 3 одинаковых
            game.m_score += addScore;
            game.m_resultText = "3 in line! +" + std::to_string(addScore) + " points";
            game.m_showResultText = true;
            std::cout << "[ShowingWinState] 3 identical symbols, added " << addScore << "\n";
        }
        else {
            // Менее 3 одинаковых, нет выигрыша
            game.m_resultText = "No win";
            game.m_showResultText = true;
            std::cout << "[ShowingWinState] No jackpot and no 3-in-line\n";
        }
    }
}