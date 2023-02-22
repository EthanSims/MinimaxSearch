/**
 * @file GameBoard.h
 * @author Ethan Sims (ea.sims@me.com)
 * @brief header file for GameBoard object
 * @date 2023-02-22
 */
#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include <vector>
#include <fstream>

using namespace std;

enum Pieces {
   RED = 'R',
   GREEN = 'G'
};

class GameBoard {
   private:
      vector<Pieces> columns[7];
      int numPieces;
      bool redNext;
      int scores[2];

      void getScores();
   public:
      GameBoard(ifstream&);

      vector<int> getAvailMoves();

      int getNumPieces();

      void printBoard();
};

#endif