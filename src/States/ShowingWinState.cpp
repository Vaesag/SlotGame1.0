#include "States/ShowingWinState.h"
#include "GameState.h"
#include <iostream>
#include <map>

/**
 * Рассчитывает количество очков за линию символов.
 * @param line Вектор символов на линии.
 * @return Количество очков за линию.
 */
static int CalculateScore(const std::vector<Symbol>& line) {
    std::map<Symbol, int> freq;

    // Подсчёт частоты каждого символа
    for (auto s : line) {
        freq[s]++;
    }

    // Поиск символа с максимальной частотой
    Symbol mainSym;
    int maxCount = 0;
    for (auto& kv : freq) {
        if (kv.second > maxCount) {
            maxCount = kv.second;
            mainSym = kv.first;
        }
    }

    // Если символов меньше трёх, очки не начисляются
    if (maxCount < 3) return 0;

    bool four = (maxCount == 4); // Проверка на четыре одинаковых символа
    int score = 0;

    // Начисление очков в зависимости от символа и количества
    switch (mainSym) {
    case Symbol::Strawberry:
        score = four ? 125 : 10;
        break;
    case Symbol::Grapes:
        score = four ? 250 : 25;
        break;
    case Symbol::Pineapple:
        score = four ? 500 : 50;
        break;
    case Symbol::Lemon:
        score = four ? 10000 : 100;
        break;
    }

    return score;
}

// ===================== Методы ShowingWinState ===================== //

//Вызывается при входе в состояние "Показ результата".

void ShowingWinState::Enter(GameState& game) {
    std::cout << "[ShowingWinState] Enter\n";
    m_showTime = 0.0f; // Сброс времени отображения результата
}

//Обновляет состояние "Показ результата". Вызывается в каждом кадре.

void ShowingWinState::Update(GameState& game, float dt) {
    m_showTime += dt;

    // Если прошло больше 5 секунд, возвращаемся в состояние ожидания
    if (m_showTime > 5.0f) {
        std::cout << "[ShowingWinState] Time to go back to WaitingForPlayer\n";
        game.GetStateMachine().SetCurrentState(game, "WaitingForPlayer");
    }
}

//Вызывается при выходе из состояния "Показ результата".

void ShowingWinState::Exit(GameState& game) {
    std::cout << "[ShowingWinState] Exit\n";
    game.m_showResultText = false; // Скрыть текст результата
}

//Обрабатывает события, связанные с результатами вращения барабанов.

void ShowingWinState::HandleEvent(GameState& game, const std::string& event) {
    std::vector<Symbol> lineSymbols;
    lineSymbols.reserve(4);

    // Получаем символы из центральной линии барабанов
    for (int i = 0; i < 4; ++i) {
        lineSymbols.push_back(game.GetSlotMachine().GetSymbolAtCentralLine(i));
    }

    if (event == "Jackpot") {
        // Обработка выигрыша "Джекпот"
        m_jackpot = true;
        game.m_resultText = "Jackpot!";
        game.m_showResultText = true;
        std::cout << "[ShowingWinState] Jackpot!\n";

        // Добавление очков за джекпот
        int addScore = CalculateScore(lineSymbols);
        if (addScore > 0) {
            game.m_score += addScore;
        }

    }
    else if (event == "NoJackpot") {
        // Обработка отсутствия "Джекпота"
        m_jackpot = false;

        int addScore = CalculateScore(lineSymbols);
        if (addScore > 0) {
            // Если есть 3 одинаковых символа в линии
            game.m_score += addScore;
            game.m_resultText = "3 in line! +" + std::to_string(addScore) + " points";
            game.m_showResultText = true;
            std::cout << "[ShowingWinState] 3 identical symbols, added " << addScore << "\n";
        }
        else {
            // Если выигрыша нет
            game.m_resultText = "No win";
            game.m_showResultText = true;
            std::cout << "[ShowingWinState] No jackpot and no 3-in-line\n";
        }
    }
}
