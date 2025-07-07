#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <limits>

std::string getChoiceName(int choice) {
    switch (choice) {
        case 1: return "Rock";
        case 2: return "Paper";
        case 3: return "Scissors";
        default: return "Unknown";
    }
}

void printTitle(){
    std::cout << "\n";
    std::cout << "╔════════════════════════════╗\n";
    std::cout << "║     Rock Paper Scissors    ║\n";
    std::cout << "╚════════════════════════════╝\n";
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 3);

    int winPlayer = 0, winComputer = 0;
    int selection;

    printTitle();

    do {
        std::cout << "\n1. Rock; 2. Paper; 3. Scissors; 0. Exit.\n> ";
        std::cin >> selection;

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            std::cout << "\n[Error] Enter a number\n\n";
            continue;
        }

        if (selection == 0) {
            std::cout << "\nThank you for playing!\n";
            break;
        }

        if (selection < 1 || selection > 3) {
            std::cout << "\n[Error] Invalid choice.\n\n";
            continue;
        }

        int choiceComputer = dist(gen);

        std::cout << "Score: You - " << winPlayer << " | Bot - " << winComputer << "\n\n";
        std::cout << "Bot has selected: " << getChoiceName(choiceComputer) << "\n";
        std::cout << "You chose: " << getChoiceName(selection) << "\n";

        if (selection == choiceComputer) {
            std::cout << "\033[33;40mDraw!\033[0m\n";
        } else if ((selection == 1 && choiceComputer == 3) || // Rock beats Scissors
        (selection == 2 && choiceComputer == 1) || // Paper beats Rock
        (selection == 3 && choiceComputer == 2)) { // Scissors beats Paper
            std::cout << "\033[32mYou win!\033[0m\n";
            winPlayer++;
        } else {
            std::cout << "\033[31mBot wins!\033[0m\n";
            winComputer++;
        }

    } while (true);

    std::cout << "\nGame Over! Here's your final score:\n";
    std::cout << "You: " << winPlayer << " | Bot: " << winComputer << "\n";
    
    if (winPlayer > winComputer) {
        std::cout << "\033[32mCongratulations! You won the game!\033[0m\n";
    } else if (winPlayer < winComputer) {
        std::cout << "\033[31mBetter luck next time! The bot won!\033[0m\n";
    } else {
        std::cout << "\033[33;40mIt's a draw! Well played!\033[0m\n";
    }

    return 0;
}