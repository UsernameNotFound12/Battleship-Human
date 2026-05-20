//
// Created by Nishanth on 5/15/2026.
//

#ifndef ECS36BBATTLESHIPHUMANSONLY_BOARD_H
#define ECS36BBATTLESHIPHUMANSONLY_BOARD_H

#include "Ship.h"
#include <vector>

namespace BattleShip {

    enum class ShotResult { HIT, MISS, ALREADY_SHOT, INVALID };

    class Board {
    public:
        Board(int rows, int cols);

        int getRows() const;
        int getCols() const;

        bool placeShip(Ship& ship, int row, int col, bool horizontal);
        ShotResult receiveShot(int row, int col, Ship*& shipHit);
        void markFiringBoard(int row, int col, bool hit);
        bool allShipsSunk() const;

        void displayPlacementBoard() const;
        void displayFiringBoard() const;

    private:
        int rows;
        int cols;
        std::vector<std::vector<char>> placementGrid;
        std::vector<std::vector<char>> firingGrid;
        std::vector<Ship*> ships;

        bool isInBounds(int row, int col) const;
        void printGrid(const std::vector<std::vector<char>>& grid) const;
    };

}


#endif //ECS36BBATTLESHIPHUMANSONLY_BOARD_H
