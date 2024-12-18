#pragma once

#include "StateMachine.h"
#include "SlotMachine.h"
#include <GL/freeglut.h>
#include <string>

/**
 * ������� �����, ����������� ���������� ����.
 */
class GameState {
public:
    // �����������. �������������� ������ ��������� � ����-������.
    GameState();

    // �������� ������� ����: ���������� ���������.
    void Update(float dt);

    // ��������� �������� ��������� ����.
    void Render();

    // ��������� ��������� �������� ����.
    void OnResize(int width, int height);

    // �������: ������ ������ "Start".
    void OnStartButtonPressed();

    // �������: ������ ������ "Stop".
    void OnStopButtonPressed();

    // �������: ������� ����� �������� ���������.
    void OnTimeOut();

    // �������: ������� ������� ����.
    void OnMouseClick(int x, int y);

    // ��������� ������ �� ������ ���������.
    StateMachine& GetStateMachine() { return m_stateMachine; }

    // ��������� ������ �� ����-������.
    SlotMachine& GetSlotMachine() { return m_slotMachine; }

    // ����� ���������� �������� ��������� (��������, "Jackpot!").
    std::string m_resultText;

    // ���� ��� ����������� ���������� �� ������.
    bool m_showResultText = false;

    // ������� ���� ������.
    int m_score = 0;

private:
    // ������ ��������� ��� ���������� �������� �������.
    StateMachine m_stateMachine;

    // ����-������ � ����������.
    SlotMachine m_slotMachine;
};