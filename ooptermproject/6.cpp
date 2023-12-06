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

string generateRandomString() {
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string randomString;

    for (int i = 0; i < MAX_STRING_LENGTH; ++i) {
        int index = rand() % characters.length();
        randomString += characters[index];
    }

    return randomString;
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

    string targetString = generateRandomString();
    string inputString;
    int targetStringPosition = 1;
    int targetStringXPosition = (rand() % 4) * (RECTANGLE_WIDTH / 4); // Random x position

    while (true) {
        system("cls");

        cout << "�꼺�� Ÿ�� ����" << endl;
        cout << "------------------" << endl;
        cout << "Ÿ������ ���ڿ�: " << targetString << endl;
        cout << "------------------" << endl;

        // �׵θ��� '*'�� ǥ���ϴ� ���簢�� ���
        printRectangle(targetStringPosition, targetStringXPosition, targetString);

        cout << "�Է��ϼ���: " << inputString << endl;

        if (_kbhit()) {
            char inputChar = _getch();
            if (inputChar == 13) {
                if (inputString.length() == MAX_STRING_LENGTH) {
                    if (inputString == targetString) {
                        targetString = generateRandomString();
                        inputString.clear();
                        targetStringPosition = 0; // Start from the top
                        targetStringXPosition = (rand() % 4) * (RECTANGLE_WIDTH / 4); // Random x position
                    }
                    else {
                        cout << "�ùٸ� ���ڿ��� �Է��ϼ���!" << endl;
                        inputString.clear();
                    }
                }
                else {
                    cout << "���ڿ� ���̰� 5�� �ƴմϴ�." << endl;
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

        int sleepTime = rand() % 501 + 250; // Random sleep time between 500 and 1000 milliseconds
        Sleep(sleepTime);
        if (targetStringPosition < RECTANGLE_HEIGHT - 2) {
            targetStringPosition++;
        }
        else {
            targetString = generateRandomString();
            targetStringPosition = 0; // Start from the top
            targetStringXPosition = (rand() % 4) * (RECTANGLE_WIDTH / 4); // Random x position
        }
    }

    return 0;
}
