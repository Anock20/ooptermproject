#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <thread>

using namespace std;

const int MAX_STRING_LENGTH = 5;
const int RECTANGLE_WIDTH = 40;
const int RECTANGLE_HEIGHT = 20;

class StringGenerator {
public:
    virtual string generateRandomString() = 0;
    virtual ~StringGenerator() = default;
};

class BasicStringGenerator : public StringGenerator {
public:
    string generateRandomString() override {
        string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        string randomString;

        for (int i = 0; i < MAX_STRING_LENGTH; ++i) {
            int index = rand() % characters.length();
            randomString += characters[index];
        }

        return randomString;
    }
};

class StringDecorator : public StringGenerator {
protected:
    unique_ptr<StringGenerator> component;

public:
    StringDecorator(unique_ptr<StringGenerator> comp) : component(move(comp)) {}

    string generateRandomString() override {
        return component->generateRandomString();
    }
};

class AlphaNumericDecorator : public StringDecorator {
public:
    AlphaNumericDecorator(unique_ptr<StringGenerator> comp) : StringDecorator(move(comp)) {}

    string generateRandomString() override {
        string baseString = component->generateRandomString();
        string extraCharacters = "0123456789";

        for (int i = 0; i < MAX_STRING_LENGTH; ++i) {
            if (rand() % 2 == 0) {
                int index = rand() % extraCharacters.length();
                baseString[i] = extraCharacters[index];
            }
        }

        return baseString;
    }
};

class AlphaSpecialCharDecorator : public StringDecorator {
public:
    AlphaSpecialCharDecorator(unique_ptr<StringGenerator> comp) : StringDecorator(move(comp)) {}

    string generateRandomString() override {
        string baseString = component->generateRandomString();
        string extraCharacters = "!@#$%^&*()-=_+[]{}|;:'\",.<>/?";

        for (int i = 0; i < MAX_STRING_LENGTH; ++i) {
            if (rand() % 2 == 0) {
                int index = rand() % extraCharacters.length();
                baseString[i] = extraCharacters[index];
            }
        }

        return baseString;
    }
};

// Function to create and apply decorators based on user input
unique_ptr<StringGenerator> createStringGenerator() {
    unique_ptr<StringGenerator> generator = make_unique<BasicStringGenerator>();

    cout << "Select options:\n";
    cout << "1. 알파벳\n";
    cout << "2. 알파벳 + 숫자\n";
    cout << "3. 알파벳 + 특수문자\n";
    int option;
    cin >> option;

    switch (option) {
    case 1:
        // Do nothing, use the basic generator
        break;
    case 2:
        generator = make_unique<AlphaNumericDecorator>(move(generator));
        break;
    case 3:
        generator = make_unique<AlphaSpecialCharDecorator>(move(generator));
        break;
    default:
        cout << "Invalid option. Using basic generator.\n";
        break;
    }

    return generator;
}

void printRectangle(int targetStringPosition, int targetStringXPosition, string targetString) {
    for (int i = 0; i < RECTANGLE_HEIGHT; ++i) {
        for (int j = 0; j < RECTANGLE_WIDTH; ++j) {
            if (i == 0 || i == RECTANGLE_HEIGHT - 1 || j == 0 || j == RECTANGLE_WIDTH - 1) {
                cout << '*';
            }
            else if (i == targetStringPosition && j == targetStringXPosition) {
                cout << targetString;
                j += MAX_STRING_LENGTH - 1;
            }
            else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
        unique_ptr<StringGenerator> generator = createStringGenerator();
        string targetString = generator->generateRandomString();   
        string inputString;
    int targetStringPosition = 1;
    int targetStringXPosition = (rand() % 4) * (RECTANGLE_WIDTH / 4); // Random x position

    while (true) {

        cout << "산성비 타자 게임" << endl;
        cout << "------------------" << endl;
        cout << "타이핑할 문자열: " << targetString << endl;
        cout << "------------------" << endl;

        // 테두리를 '*'로 표시하는 직사각형 출력
        printRectangle(targetStringPosition, targetStringXPosition, targetString);

        cout << "입력하세요: " << inputString << endl;

        if (_kbhit()) {
            char inputChar = _getch();
            if (inputChar == 13) {
                if (inputString.length() == MAX_STRING_LENGTH) {
                    if (inputString == targetString) {
                        targetString = generator->generateRandomString();
                        inputString.clear();
                        targetStringPosition = 0; // Start from the top
                        targetStringXPosition = (rand() % 4) * (RECTANGLE_WIDTH / 4); // Random x position
                    }
                    else {
                        cout << "올바른 문자열을 입력하세요!" << endl;
                        inputString.clear();
                    }
                }
                else {
                    cout << "문자열 길이가 5가 아닙니다." << endl;
                    inputString.clear();
                }
            }
            else {
                inputString += inputChar;
                if (inputString.length() > MAX_STRING_LENGTH) {
                    inputString.pop_back();
                }
            }
        }

        int sleepTime = rand() % 501 + 250; 
        Sleep(sleepTime);

        if (targetStringPosition < RECTANGLE_HEIGHT - 2) {
            targetStringPosition++;
        }
        else {
            targetString = generator->generateRandomString();
            targetStringPosition = 0; // Start from the top
            targetStringXPosition = (rand() % 4) * (RECTANGLE_WIDTH / 4); // Random x position
        }

        system("cls"); // Clear the screen after updating the game state
    }

    return 0;
}