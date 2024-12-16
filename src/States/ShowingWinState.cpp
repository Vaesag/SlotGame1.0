#include "States/ShowingWinState.h"
#include "GameState.h"
#include <iostream>
#include <map>

/**
 * ������������ ���������� ����� �� ����� ��������.
 * @param line ������ �������� �� �����.
 * @return ���������� ����� �� �����.
 */
static int CalculateScore(const std::vector<Symbol>& line) {
    std::map<Symbol, int> freq;

    // ������� ������� ������� �������
    for (auto s : line) {
        freq[s]++;
    }

    // ����� ������� � ������������ ��������
    Symbol mainSym;
    int maxCount = 0;
    for (auto& kv : freq) {
        if (kv.second > maxCount) {
            maxCount = kv.second;
            mainSym = kv.first;
        }
    }

    // ���� �������� ������ ���, ���� �� �����������
    if (maxCount < 3) return 0;

    bool four = (maxCount == 4); // �������� �� ������ ���������� �������
    int score = 0;

    // ���������� ����� � ����������� �� ������� � ����������
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

// ===================== ������ ShowingWinState ===================== //

//���������� ��� ����� � ��������� "����� ����������".

void ShowingWinState::Enter(GameState& game) {
    std::cout << "[ShowingWinState] Enter\n";
    m_showTime = 0.0f; // ����� ������� ����������� ����������
}

//��������� ��������� "����� ����������". ���������� � ������ �����.

void ShowingWinState::Update(GameState& game, float dt) {
    m_showTime += dt;

    // ���� ������ ������ 5 ������, ������������ � ��������� ��������
    if (m_showTime > 5.0f) {
        std::cout << "[ShowingWinState] Time to go back to WaitingForPlayer\n";
        game.GetStateMachine().SetCurrentState(game, "WaitingForPlayer");
    }
}

//���������� ��� ������ �� ��������� "����� ����������".

void ShowingWinState::Exit(GameState& game) {
    std::cout << "[ShowingWinState] Exit\n";
    game.m_showResultText = false; // ������ ����� ����������
}

//������������ �������, ��������� � ������������ �������� ���������.

void ShowingWinState::HandleEvent(GameState& game, const std::string& event) {
    std::vector<Symbol> lineSymbols;
    lineSymbols.reserve(4);

    // �������� ������� �� ����������� ����� ���������
    for (int i = 0; i < 4; ++i) {
        lineSymbols.push_back(game.GetSlotMachine().GetSymbolAtCentralLine(i));
    }

    if (event == "Jackpot") {
        // ��������� �������� "�������"
        m_jackpot = true;
        game.m_resultText = "Jackpot!";
        game.m_showResultText = true;
        std::cout << "[ShowingWinState] Jackpot!\n";

        // ���������� ����� �� �������
        int addScore = CalculateScore(lineSymbols);
        if (addScore > 0) {
            game.m_score += addScore;
        }

    }
    else if (event == "NoJackpot") {
        // ��������� ���������� "��������"
        m_jackpot = false;

        int addScore = CalculateScore(lineSymbols);
        if (addScore > 0) {
            // ���� ���� 3 ���������� ������� � �����
            game.m_score += addScore;
            game.m_resultText = "3 in line! +" + std::to_string(addScore) + " points";
            game.m_showResultText = true;
            std::cout << "[ShowingWinState] 3 identical symbols, added " << addScore << "\n";
        }
        else {
            // ���� �������� ���
            game.m_resultText = "No win";
            game.m_showResultText = true;
            std::cout << "[ShowingWinState] No jackpot and no 3-in-line\n";
        }
    }
}
