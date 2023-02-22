#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include <vector>
#include <fstream>

using namespace std;

enum Pieces {
   RED,
   GREEN
};

class GameBoard {
   private:
      vector<Pieces> columns[7];
      int numPieces;
   public:
      GameBoard(ifstream&);

      int* getAvailMoves();

      int getNumPieces();
};

#endif