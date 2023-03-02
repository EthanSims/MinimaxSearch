/**
 * @file GameBoard.h
 * @author Ethan Sims (ea.sims@me.com)
 * @brief header file for GameBoard object
 */
#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include <vector>
#include <fstream>

using namespace std;

enum Pieces {
   RED = 'R',
   GREEN = 'G',
   NONE = 'O'
};

class GameBoard {
   private:
      const static int NUM_COLS = 7;
      const static int NUM_ROWS = 6;
      vector<Pieces> columns[NUM_COLS];
      int numPieces;
      bool redNext;
      int scores[2];

      void getScores();
      int getScoresHelper(int, int, int, Pieces&);
   public:
      GameBoard(ifstream&);

      vector<int> getAvailMoves();

      int getNumPieces();

      void printBoard();
};

#endif