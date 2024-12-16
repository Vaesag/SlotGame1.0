#pragma once

#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Символы, используемые на барабанах
enum class Symbol {
    Strawberry,  // Клубника
    Grapes,      // Виноград
    Pineapple,   // Ананас
    Lemon        // Лимон
};

// Типы кнопок
enum class ButtonType {
    None,  // Нет кнопки
    Start, // Кнопка "Start"
    Stop   // Кнопка "Stop"
};

// Структура, описывающая барабан
struct Reel {
    std::vector<Symbol> symbols;  // Лента символов на барабане
    float rotation = 0.0f;        // Текущее смещение барабана
    float speed = 0.0f;           // Текущая скорость вращения
    bool spinning = false;        // Флаг, указывает на состояние вращения
    float elapsedTime = 0.0f;     // Прошедшее время с момента старта
    bool accelerating = true;     // Флаг ускорения
    bool decelerating = false;    // Флаг замедления
    float startDelay = 0.0f;      // Задержка старта вращения
    bool started = false;         // Флаг, указывает, что вращение началось

    float targetRotation = 0.0f;  // Целевой угол остановки
    float maxSpeed = 800.0f;      // Максимальная скорость вращения
};

// Класс, управляющий работой слот-машины
class SlotMachine {
public:
    SlotMachine();
    ~SlotMachine();

    // Основной игровой цикл
    void Update(float dt);

    // Отрисовка слот-машины
    void Render();

    // Обработка изменения размеров окна
    void OnResize(int width, int height);

    // Запуск вращения барабанов
    void StartSpinning();

    // Остановка вращения барабанов
    void StopSpinning();

    // Проверка состояния вращения
    bool IsSpinning() const;
    bool IsStopped() const;

    // Получение размеров окна
    int GetWidth() const;
    int GetHeight() const;

    // Проверка результата (например, джекпот)
    bool CheckJackpot();

    // Получение символа на центральной линии
    Symbol GetSymbolAtCentralLine(int reelIndex);

    // Управление отображением кнопок
    void ShowStartButton(bool show);
    void ShowStopButton(bool show);

    // Проверка нажатия на кнопку
    ButtonType CheckButtonClick(int x, int y);

private:
    // Структура для хранения информации о текстурах
    struct TextureInfo {
        GLuint texId;     // ID текстуры
        int width;        // Ширина текстуры
        int height;       // Высота текстуры
    };

    // Структура для описания кнопки
    struct ButtonRect {
        int x;      // Координата X
        int y;      // Координата Y
        int width;  // Ширина
        int height; // Высота
    };

    // Загрузка текстур
    void LoadResources();

    // Отрисовка текстуры
    void DrawTexture(GLuint texId, int x, int y, int width, int height);

    // Обновление анимации барабанов
    void UpdateAnimation(float dt);

    // Инициализация барабанов
    void InitializeReels();

    // Обновление позиций кнопок
    void UpdateButtonPositions();

    // Генерация ленты символов для барабана
    void GenerateSymbolStrip(std::vector<Symbol>& strip);

    // Выравнивание барабана по ближайшему символу
    void AlignRotation(Reel& r);

    // Расчёт текущей скорости барабана
    float CalculateSpeed(Reel& r, float dt);

    // Константы
    const int SYMBOL_SIZE = 100;        // Размер одного символа
    const int VISIBLE_SYMBOLS = 3;     // Количество видимых символов
    const int REEL_COUNT = 4;          // Количество барабанов
    const int STRIP_LENGTH = 20;       // Длина ленты символов на барабане

    float m_accelerationTime = 1.0f;   // Время ускорения барабанов
    float m_decelerationTime = 1.0f;   // Время замедления барабанов

    bool m_shouldStop = false;         // Флаг остановки вращения

    // Текстуры
    std::map<Symbol, TextureInfo> m_symbolTextures; // Текстуры символов
    TextureInfo m_goButtonTexture;                 // Текстура кнопки "Start"
    TextureInfo m_stopButtonTexture;               // Текстура кнопки "Stop"

    // Параметры кнопок
    ButtonRect m_startButtonRect; // Параметры кнопки "Start"
    ButtonRect m_stopButtonRect;  // Параметры кнопки "Stop"

    // Барабаны
    std::vector<Reel> m_reels;

    // Флаги отображения кнопок
    bool m_showStartButton = true;
    bool m_showStopButton = false;

    // Размеры окна
    int m_windowWidth = 800;
    int m_windowHeight = 600;
};
