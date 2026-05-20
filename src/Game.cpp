//
// Created by mfbut on 5/3/2026.
//

#include "Game.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

namespace BattleShip {

    Game::Game(const std::string& configFile) {
        readConfig(configFile);
    }

    void Game::readConfig(const std::string& configFile) {
        std::ifstream file(configFile);
        if (!file) throw std::runtime_error("Could not open config file: " + configFile);

        int numShips;
        file >> rows >> cols >> numShips;

        for (int i = 0; i < numShips; i++) {
            char symbol;
            int size;
            file >> symbol >> size;
            shipDefs.push_back({symbol, size});
        }
    }

    std::string Game::getPlayerName(int playerNumber) {
        std::cout << "Player " << playerNumber << " please enter your name: ";
        std::string name;
        std::getline(std::cin, name);
        return name;
    }

    void Game::setup() {
        std::string name1 = getPlayerName(1);
        player1 = std::make_unique<Player>(name1, rows, cols, shipDefs);
        player1->placeShips();

        std::string name2 = getPlayerName(2);
        player2 = std::make_unique<Player>(name2, rows, cols, shipDefs);
        player2->placeShips();
    }

    void Game::gameLoop() {
        player1->displayBoards();

        while (true) {
            player1->takeTurn(player2->getBoard(), player2->getName());
            if (player2->hasLost()) {
                std::cout << "\n" << player1->getName() << " won the game!\n";
                return;
            }

            player2->displayBoards();

            player2->takeTurn(player1->getBoard(), player1->getName());
            if (player1->hasLost()) {
                std::cout << "\n" << player2->getName() << " won the game!\n";
                return;
            }

            player1->displayBoards();
        }
    }

    void Game::run() {
        setup();
        gameLoop();
    }
} // BattleShip