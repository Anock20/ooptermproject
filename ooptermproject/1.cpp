//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//#include <vector>
//#include <algorithm>
//
//// abstract class for decorators
//class stringdecorator {
//public:
//    virtual std::string decorate(const std::string& input) const = 0;
//};
//
//// concrete decorator for adding random numbers to the string
//class numberdecorator : public stringdecorator {
//public:
//    virtual std::string decorate(const std::string& input) const override {
//        return input + std::to_string(rand() % 10);
//    }
//};
//
//// concrete decorator for adding random special characters to the string
//class specialcharacterdecorator : public stringdecorator {
//public:
//    virtual std::string decorate(const std::string& input) const override {
//        const std::string specialcharacters = "!@#$%^&*()_+-=";
//        return input + specialcharacters[rand() % specialcharacters.length()];
//    }
//};
//
//// class for handling the falling strings
//class fallingstring {
//private:
//    std::string value;
//    int xposition;
//    int yposition;
//
//public:
//    fallingstring(const std::string& initialvalue, int x, int y)
//        : value(initialvalue), xposition(x), yposition(y) {}
//
//    std::string getvalue() const {
//        return value;
//    }
//
//    int getxposition() const {
//        return xposition;
//    }
//
//    int getyposition() const {
//        return yposition;
//    }
//
//    void fall() {
//        yposition++;
//    }
//};
//
//// class for the main game
//class typinggame {
//private:
//    std::vector<fallingstring> fallingstrings;
//    stringdecorator* decorator;
//
//public:
//    typinggame(stringdecorator* dec) : decorator(dec) {}
//
//    void generatestring(int screenwidth) {
//        const std::string options[] = { "alphabet", "number", "specialcharacter" };
//        std::string chosenoption = options[rand() % 3];
//
//        std::string basestring;
//        if (chosenoption == "alphabet") {
//            basestring = "abcdefghijklmnopqrstuvwxyz";
//        }
//        else if (chosenoption == "number") {
//            basestring = "0123456789";
//        }
//        else if (chosenoption == "specialcharacter") {
//            basestring = "!@#$%^&*()_+-=";
//        }
//
//        basestring = decorator->decorate(basestring);
//
//        int xposition = rand() % (screenwidth / 4);  // divide screen into 4 parts
//        fallingstrings.emplace_back(basestring, xposition, 0);
//    }
//
//    void displayscreen(int screenwidth, int screenheight) {
//        // clear the screen
//        system("cls");
//
//        for (const auto& str : fallingstrings) {
//            if (str.getyposition() < screenheight) {
//                std::cout << std::string(str.getxposition(), ' ') << str.getvalue() << std::endl;
//            }
//        }
//
//        // display game status or score
//        std::cout << "score: " << calculatescore() << std::endl;
//    }
//
//    int calculatescore() const {
//        // your scoring logic here
//        // for example, you can count the number of correctly typed strings
//        return 0;
//    }
//
//    void updategame() {
//        for (auto& str : fallingstrings) {
//            str.fall();
//        }
//
//        // remove strings that have reached the bottom
//        fallingstrings.erase(std::remove_if(fallingstrings.begin(), fallingstrings.end(),
//            [](const fallingstring& str) { return str.getyposition() >= 10; }),
//            fallingstrings.end());
//    }
//};
//
//int main() {
//    srand(static_cast<unsigned>(time(0)));
//
//    // get user input for string decoration option
//    std::cout << "choose string decoration option:\n";
//    std::cout << "1. alphabet\n";
//    std::cout << "2. number\n";
//    std::cout << "3. special character\n";
//    int choice;
//    std::cin >> choice;
//
//    stringdecorator* decorator = nullptr;
//
//    switch (choice) {
//    case 1:
//        decorator = new numberdecorator();
//        break;
//    case 2:
//        decorator = new specialcharacterdecorator();
//        break;
//    case 3:
//        // add more decorators as needed
//        break;
//    default:
//        std::cerr << "invalid choice\n";
//        return 1;
//    }
//
//    typinggame game(decorator);
//
//    int screenwidth = 80;
//    int screenheight = 10;
//
//    while (true) {
//        game.generatestring(screenwidth);
//        game.displayscreen(screenwidth, screenheight);
//        game.updategame();
//
//        // introduce a delay to control the speed of the falling strings
//        // adjust the sleep duration as needed
//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
//    }
//
//    delete decorator;  // don't forget to free the allocated memory
//    return 0;
//}
