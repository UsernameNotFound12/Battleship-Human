//
// Created by Nishanth on 5/15/2026.
//

#include "Player.h"
#include <iostream>
#include <sstream>
#include <algorithm>

namespace BattleShip {

Player::Player(const std::string& name, int rows, int cols,
               const std::vector<std::pair<char,int>>& shipDefs)
    : name(name), board(rows, cols)
{
    std::vector<std::pair<char,int>> sorted = shipDefs;
    std::sort(sorted.begin(), sorted.end());
    for (auto& [sym, size] : sorted) {
        ships.emplace_back(sym, size);
    }
}

const std::string& Player::getName() const { return name; }
Board& Player::getBoard() { return board; }
bool Player::hasLost() const { return board.allShipsSunk(); }

bool Player::getOrientation(char shipSymbol) {
    while (true) {
        std::cout << name << ", do you want to place " << shipSymbol
                  << " horizontally or vertically?\n";
        std::cout << "Enter h for horizontal or v for vertical\n";
        std::cout << "Your choice: ";

        std::string line;
        std::getline(std::cin, line);

        if (line == "h" || line == "H") return true;
        if (line == "v" || line == "V") return false;
    }
}

bool Player::getCoordinate(int& row, int& col) {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);

    int r, c;
    if (!(iss >> r >> c)) return false;

    std::string extra;
    if (iss >> extra) return false;

    row = r;
    col = c;
    return true;
}

void Player::placeShips() {
    for (Ship& ship : ships) {
        bool placed = false;
        while (!placed) {
            board.displayPlacementBoard();
            bool horizontal = getOrientation(ship.getSymbol());

            std::cout << name << ", enter the row and column you want to place "
                      << ship.getSymbol() << ", which is " << ship.getSize()
                      << " long, at with a space in between row and col: ";

            int row, col;
            if (!getCoordinate(row, col)) continue;
            if (!board.placeShip(ship, row, col, horizontal)) continue;

            placed = true;
        }
    }
    board.displayPlacementBoard();
}

void Player::takeTurn(Board& opponentBoard, const std::string& opponentName) {
    bool validMove = false;
    while (!validMove) {
        std::cout << name << ", where would you like to fire?\n";
        std::cout << "Enter your attack coordinate in the form row col: ";

        int row, col;
        if (!getCoordinate(row, col)) continue;

        Ship* shipHit = nullptr;
        ShotResult result = opponentBoard.receiveShot(row, col, shipHit);

        if (result == ShotResult::INVALID || result == ShotResult::ALREADY_SHOT) continue;

        bool hit = (result == ShotResult::HIT);
        board.markFiringBoard(row, col, hit);
        validMove = true;

        displayBoards();

        if (hit && shipHit) {
            std::cout << name << " hit " << opponentName << "'s "
                      << shipHit->getSymbol() << "!\n";
            if (shipHit->isSunk()) {
                std::cout << name << " destroyed " << opponentName << "'s "
                          << shipHit->getSymbol() << "!\n";
            }
        } else {
            std::cout << "Missed.\n";
        }
    }
}

void Player::displayBoards() const {
    std::cout << "\n" << name << "'s Firing Board\n";
    board.displayFiringBoard();
    std::cout << "\n\n" << name << "'s Placement Board\n";
    board.displayPlacementBoard();
}

}