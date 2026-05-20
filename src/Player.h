//
// Created by Nishanth on 5/15/2026.
//

#ifndef ECS36BBATTLESHIPHUMANSONLY_PLAYER_H
#define ECS36BBATTLESHIPHUMANSONLY_PLAYER_H

#include "Board.h"
#include "Ship.h"
#include <string>
#include <vector>

namespace BattleShip {

    class Player {
    public:
        Player(const std::string& name, int rows, int cols,
               const std::vector<std::pair<char,int>>& shipDefs);

        const std::string& getName() const;
        Board& getBoard();
        bool hasLost() const;

        void placeShips();
        void takeTurn(Board& opponentBoard, const std::string& opponentName);
        void displayBoards() const;

    private:
        std::string name;
        Board board;
        std::vector<Ship> ships;

        bool getOrientation(char shipSymbol);
        bool getCoordinate(int& row, int& col);
    };

}

#endif //ECS36BBATTLESHIPHUMANSONLY_PLAYER_H
