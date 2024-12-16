#pragma once
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

struct Reel {
    std::vector<Symbol> symbols; 
    float rotation = 0.0f;       
    float speed = 0.0f;          
    bool spinning = false;
    float elapsedTime = 0.0f;    
    bool accelerating = true;    
    bool decelerating = false;   
    float startDelay = 0.0f;     
    bool started = false;        

    float targetRotation = 0.0f; 
    float maxSpeed = 800.0f;     
};

class SlotMachine {
public:
    SlotMachine();
    ~SlotMachine();

    void Update(float dt);
    void Render();
    void OnResize(int width, int height);

    void StartSpinning();

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

    void GenerateSymbolStrip(std::vector<Symbol>& strip);

    void AlignRotation(Reel& r);

    float CalculateSpeed(Reel& r, float dt);

    const int SYMBOL_SIZE = 100;
    const int VISIBLE_SYMBOLS = 3;
    const int REEL_COUNT = 4;

    const int STRIP_LENGTH = 20;

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