//
// Created by mfbut on 5/3/2026.
//

#ifndef ECS36BBATTLESHIPHUMANSONLY_GAME_H
#define ECS36BBATTLESHIPHUMANSONLY_GAME_H

#include "Player.h"
#include <memory>
#include <string>
#include <vector>
#include <utility>

namespace BattleShip {

    class Game {
    public:
        explicit Game(const std::string& configFile);

        void run();

    private:
        int rows;
        int cols;
        std::vector<std::pair<char,int>> shipDefs;
        std::unique_ptr<Player> player1;
        std::unique_ptr<Player> player2;

        void readConfig(const std::string& configFile);
        void setup();
        void gameLoop();
        std::string getPlayerName(int playerNumber);
    };
} // BattleShip

#endif //ECS36BBATTLESHIPHUMANSONLY_GAME_H
