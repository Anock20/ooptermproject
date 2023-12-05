#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <conio.h>
#include <windows.h>

const int SCREEN_WIDTH = 80;  // �ܼ� â ���� ����
const int SCREEN_HEIGHT = 25; // �ܼ� â ���� ����

// ���ڿ� ������ ���� �⺻ �������̽�
class TextGenerator {
public:
    virtual std::string generateText() = 0;
};

// ���� ���ڿ� ���� Ŭ����
class RandomTextGenerator : public TextGenerator {
public:
    std::string generateText() override {
        static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+{}[]|;:,.<>?";
        std::string text;
        int length = rand() % 10 + 1; // �ִ� ���� 10���� ����

        for (int i = 0; i < length; ++i) {
            text += charset[rand() % sizeof(charset)];
        }

        return text;
    }
};

// ���ڷ����� Ŭ����: ���ĺ��� ����
class AlphabetDecorator : public TextGenerator {
public:
    AlphabetDecorator(TextGenerator* generator) : generator(generator) {}

    std::string generateText() override {
        std::string text = generator->generateText();
        for (char& c : text) {
            if (!isalpha(c)) {
                c = 'A' + rand() % 26; // ���ĺ����� ��ü
            }
        }
        return text;
    }

private:
    TextGenerator* generator;
};

// ���ڷ����� Ŭ����: ���ڸ� ����
class NumberDecorator : public TextGenerator {
public:
    NumberDecorator(TextGenerator* generator) : generator(generator) {}

    std::string generateText() override {
        std::string text = generator->generateText();
        for (char& c : text) {
            if (!isdigit(c)) {
                c = '0' + rand() % 10; // ���ڷ� ��ü
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
        text = generator->generateText();  // ó���� �� ���� ȣ���Ͽ� �ؽ�Ʈ�� ����
        x = (SCREEN_WIDTH / 4) * (rand() % 4); // 4����Ͽ� ������ ��ġ�� ����
    }

    void fall() {
        while (y < SCREEN_HEIGHT) {
            draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(getRandomSleepTime())); // ���� �ð� ���� ��� ����

            if (_kbhit()) {
                // Ű �Է��� �����Ǹ� �Է��� ó��
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
        system("cls"); // Windows���� �ܼ��� ����� ��ɾ�
    }

    // ������ �ð� ��ȯ (��: 50ms���� 200ms ������ ������ ��)
    int getRandomSleepTime() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(50, 200); // ���� ������ ������ ����

        return dis(gen);
    }

    // Ű �Է� ó�� �Լ�
// Ű �Է� ó�� �Լ�
    void handleInput() {
        if (_kbhit()) {
            int key = _getch(); // Ű �Է� �ޱ�

            // ���⿡�� Ű �Է¿� ���� ó���� �߰�
            std::cout << "Ű �Է�: " << key << std::endl;

            // ���ڿ��� �Է� ���� ��ġ�ϸ� ���ڿ��� ����� ����
            if (key == text[0]) {
                clear();
                y = SCREEN_HEIGHT; // ���� ������ �������� ������ ��������
            }
        }
    }

};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // �⺻ ���� ���ڿ� ������ ����
    TextGenerator* generator = new RandomTextGenerator();

    // �ɼǿ� ���� ���ڷ����͸� �߰�
    int option;
    std::cout << "1. ���ĺ�, 2. ���� - �ɼ��� �Է��ϼ���: ";
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
