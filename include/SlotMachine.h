#pragma once
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// 4 уникальных символа
enum class Symbol {
    Strawberry,
    Grapes,
    Pineapple,
    Lemon
};

enum class ButtonType {
    None,
    Start,
    Stop
};

// Структура барабана
struct Reel {
    std::vector<Symbol> symbols; // Лента из 20 символов
    float rotation = 0.0f;       // текущий offset по ленте в пикселях
    float speed = 0.0f;          // текущая скорость
    bool spinning = false;
    float elapsedTime = 0.0f;    // сколько времени прошло с начала вращения/торможения
    bool accelerating = true;    // сначала разгоняемся
    bool decelerating = false;   // потом тормозим
    float startDelay = 0.0f;     // задержка перед стартом
    bool started = false;        // стартовал ли барабан после задержки

    float targetRotation = 0.0f; // целевой rotation, чтобы остановиться на другом символе
    float maxSpeed = 800.0f;     // maxSpeed индивидуальна для барабана
};

class SlotMachine {
public:
    SlotMachine();
    ~SlotMachine();

    void Update(float dt);
    void Render();
    void OnResize(int width, int height);

    // Запуск вращения барабанов с разными параметрами
    void StartSpinning();

    // Остановка вращения
    void StopSpinning();

    bool IsSpinning() const;
    bool IsStopped() const;

    int GetWidth() const;
    int GetHeight() const;

    bool CheckJackpot();
    Symbol GetSymbolAtCentralLine(int reelIndex);

    void ShowStartButton(bool show);
    void ShowStopButton(bool show);

    ButtonType CheckButtonClick(int x, int y);

private:
    struct TextureInfo {
        GLuint texId;
        int width, height;
    };

    struct ButtonRect {
        int x, y, width, height;
    };

    void LoadResources();
    void DrawTexture(GLuint texId, int x, int y, int width, int height);
    void UpdateAnimation(float dt);
    void InitializeReels();
    void UpdateButtonPositions();

    // Генерируем ленту из 20 символов 1 раз
    void GenerateSymbolStrip(std::vector<Symbol>& strip);

    // Округление rotation при остановке
    void AlignRotation(Reel& r);

    // Расчет скорости по времени и режиму (разгон или торможение)
    float CalculateSpeed(Reel& r, float dt);

    const int SYMBOL_SIZE = 100;
    const int VISIBLE_SYMBOLS = 3;
    const int REEL_COUNT = 4;

    // Длина ленты
    const int STRIP_LENGTH = 20;

    // Время разгона/торможения
    float m_accelerationTime = 1.0f;
    float m_decelerationTime = 1.0f;

    bool m_shouldStop = false;

    std::map<Symbol, TextureInfo> m_symbolTextures;
    TextureInfo m_goButtonTexture;
    TextureInfo m_stopButtonTexture;

    ButtonRect m_startButtonRect;
    ButtonRect m_stopButtonRect;

    std::vector<Reel> m_reels;

    bool m_showStartButton = true;
    bool m_showStopButton = false;

    int m_windowWidth = 800;
    int m_windowHeight = 600;
};