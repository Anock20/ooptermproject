//#include <iostream>
//#include <string>
//#include <thread>
//#include <chrono>
//#include <random>
//
//class TypingGame {
//public:
//    TypingGame() : gameOver(false), score(0) {}
//
//    void startGame() {
//        std::thread dropThread(&TypingGame::dropString, this);
//        dropThread.detach();
//
//        while (!gameOver) {
//            std::string userInput;
//            std::cin >> userInput;
//
//            if (userInput == currentString) {
//                score++;
//                currentString = "";
//            }
//            else {
//                std::cout << "Wrong input!" << std::endl;
//            }
//        }
//    }
//
//private:
//    void dropString() {
//        while (!gameOver) {
//            if (currentString.empty()) {
//                currentString = generateString();
//                displayString();
//            }
//
//            std::this_thread::sleep_for(std::chrono::milliseconds(getRandomSpeed()));
//
//            if (!currentString.empty()) {
//                gameOver = true;
//                std::cout << "Game Over! Your score: " << score << std::endl;
//            }
//        }
//    }
//
//    std::string generateString() {
//        std::string str = "";
//        std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
//        std::random_device rd;
//        std::mt19937 generator(rd());
//
//        for (int i = 0; i < 4; i++) {
//            str += characters[generator() % characters.size()];
//        }
//
//        return str;
//    }
//
//    void displayString() {
//        // Clear the console screen
//        std::cout << "\033[2J\033[H";  // Works on Unix-like systems, may need adjustment on Windows
//
//        std::cout << currentString << std::endl;
//    }
//
//    int getRandomSpeed() {
//        // Generate a random speed between 500 and 1500 milliseconds
//        std::random_device rd;
//        std::mt19937 generator(rd());
//        std::uniform_int_distribution<int> distribution(500, 1500);
//
//        return distribution(generator);
//    }
//
//    bool gameOver;
//    int score;
//    std::string currentString;
//};
//
//int main() {
//    TypingGame game;
//    game.startGame();
//
//    return 0;
//}
