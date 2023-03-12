/**
 * @file main.cpp
 * @author Ethan Sims (ea.sims@me.com)
 * @brief handles command-line arguments and starts game
 */

#include <stdio.h>
#include <fstream>
#include "../includes/GameBoard.h"

using namespace std;

/**
 * @brief runs interactive mode of program (human and computer take turns)
 * 
 * @param inputFile filestream for file containing original board state
 * @param DEPTH depth of search (how many moves ahead to look)
 * @param humanNext boolean value denoting if it is the human's turn
 */
void runInteractive(GameBoard board, bool humanNext) {
   if(!humanNext) {

   }
}

void runOneMove(GameBoard board, ofstream &outputFile) {
   board.printBoard();
   board.getComputerMove();
   board.printBoard();
   board.saveBoard(outputFile);
   exit(0);
}

/**
 * @brief entry point for program
 * 
 * @param argc number of arguments
 * @param argv array of arguments
 * @return int - 0 for success, -1 otherwise
 */
int main(int argc, char* argv[]) {
   // input handling
   if (argc != 5) {
      fprintf(stderr, "Incorrect number of arguments given.");
      return -1;
   }

   if (!(((string) argv[1]) == "interactive" || ((string) argv[1]) == "one-move")) {
      fprintf(stderr, "Unexpected argument given: %s", argv[1]);
      return -1;
   }

   if (((string) argv[1]) == "interactive" && !(((string) argv[3]) == "computer-next" || ((string) argv[3]) == "human-next")) {
      fprintf(stderr, "Unexpected argument given: %s", argv[3]);
      return -1;
   }

   GameBoard board(argv[2], atoi(argv[4]));

   if (((string) argv[1]) == "interactive") { // run interactive mode
      runInteractive(board, ((string) argv[3]) == "human-next");
   } else { // run one-move mode
      // open outputFile and test its existence
      ofstream outputFile(argv[3], ofstream::out);
      runOneMove(board, outputFile);
   }

   return 0;
}