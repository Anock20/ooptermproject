#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <conio.h>
#include <windows.h>

const int SCREEN_WIDTH = 80;  // 콘솔 창 가로 길이
const int SCREEN_HEIGHT = 25; // 콘솔 창 세로 길이

// 문자열 생성을 위한 기본 인터페이스
class TextGenerator {
public:
    virtual std::string generateText() = 0;
};

// 랜덤 문자열 생성 클래스
class RandomTextGenerator : public TextGenerator {
public:
    std::string generateText() override {
        static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+{}[]|;:,.<>?";
        std::string text;
        int length = rand() % 10 + 1; // 최대 길이 10으로 제한

        for (int i = 0; i < length; ++i) {
            text += charset[rand() % sizeof(charset)];
        }

        return text;
    }
};

// 데코레이터 클래스: 알파벳만 생성
class AlphabetDecorator : public TextGenerator {
public:
    AlphabetDecorator(TextGenerator* generator) : generator(generator) {}

    std::string generateText() override {
        std::string text = generator->generateText();
        for (char& c : text) {
            if (!isalpha(c)) {
                c = 'A' + rand() % 26; // 알파벳으로 대체
            }
        }
        return text;
    }

private:
    TextGenerator* generator;
};

// 데코레이터 클래스: 숫자만 생성
class NumberDecorator : public TextGenerator {
public:
    NumberDecorator(TextGenerator* generator) : generator(generator) {}

    std::string generateText() override {
        std::string text = generator->generateText();
        for (char& c : text) {
            if (!isdigit(c)) {
                c = '0' + rand() % 10; // 숫자로 대체
            }
        }
        return text;
    }

private:
    TextGenerator* generator;
};

class FallingText {
public:
    FallingText(TextGenerator* generator) : generator(generator), y(0) {
        text = generator->generateText();  // 처음에 한 번만 호출하여 텍스트를 생성
        x = (SCREEN_WIDTH / 4) * (rand() % 4); // 4등분하여 랜덤한 위치로 설정
    }

    void fall() {
        while (y < SCREEN_HEIGHT) {
            draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(getRandomSleepTime())); // 랜덤 시간 동안 잠시 멈춤

            if (_kbhit()) {
                // 키 입력이 감지되면 입력을 처리
                handleInput();
            }

            clear();
            y++;
        }
    }

private:
    TextGenerator* generator;
    int x, y;
    std::string text;

    void draw() {
        for (int i = 0; i < y; ++i) {
            std::cout << std::endl;
        }

        for (int i = 0; i < x; ++i) {
            std::cout << ' ';
        }

        std::cout << text << std::endl;
    }

    void clear() {
        system("cls"); // Windows에서 콘솔을 지우는 명령어
    }

    // 랜덤한 시간 반환 (예: 50ms에서 200ms 사이의 랜덤한 값)
    int getRandomSleepTime() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(50, 200); // 조절 가능한 범위로 수정

        return dis(gen);
    }

    // 키 입력 처리 함수
// 키 입력 처리 함수
    void handleInput() {
        if (_kbhit()) {
            int key = _getch(); // 키 입력 받기

            // 여기에서 키 입력에 따른 처리를 추가
            std::cout << "키 입력: " << key << std::endl;

            // 문자열과 입력 값이 일치하면 문자열을 지우고 종료
            if (key == text[0]) {
                clear();
                y = SCREEN_HEIGHT; // 종료 조건을 만족시켜 루프를 빠져나감
            }
        }
    }

};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // 기본 랜덤 문자열 생성기 생성
    TextGenerator* generator = new RandomTextGenerator();

    // 옵션에 따라 데코레이터를 추가
    int option;
    std::cout << "1. 알파벳, 2. 숫자 - 옵션을 입력하세요: ";
    std::cin >> option;

    if (option & 1) {
        generator = new AlphabetDecorator(generator);
    }
    if (option & 2) {
        generator = new NumberDecorator(generator);
    }

    FallingText fallingText(generator);
    fallingText.fall();

    delete generator;

    return 0;
}
