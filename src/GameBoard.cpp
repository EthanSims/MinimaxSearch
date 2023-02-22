#include "GameBoard.h"

using namespace std;

/**
 * @brief Construct a new Game Board object
 * 
 * @param input filestream to read initial state from
 */
GameBoard::GameBoard(ifstream &input) {
   char currSlot;
   
   for (int row = 0 ; row < 6 ; row++) {
      input >> currSlot;
   }

}