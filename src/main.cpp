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
 * @param board board to play on
 * @param humanNext true if human player is next, false if computer is next
 */
void runInteractive(GameBoard board, bool humanNext) {
   if(!humanNext) {
      board.printBoard();
      if (board.getAvailMoves().size() == 0) exit(0);
      board.getComputerMove();
      board.saveBoard("computer.txt");
   }
   while (true) { 
      board.printBoard();
      if (board.getAvailMoves().size() == 0) exit(0);
      board.getUserMove();
      board.saveBoard("human.txt");
      board.printBoard();
      if (board.getAvailMoves().size() == 0) exit(0);
      board.getComputerMove();
      board.saveBoard("computer.txt");
   }  
}

/**
 * @brief runs one move mode
 * 
 * @param board board to play on
 * @param outputFile name of file to write output to
 */
void runOneMove(GameBoard board, string outputFile) {
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

   GameBoard board(argv[2], atoi(argv[4])); // makes new board with given input file and depth of search

   if (((string) argv[1]) == "interactive") { // run interactive mode
      runInteractive(board, ((string) argv[3]) == "human-next");
   } else { // run one-move mode
      // open outputFile and test its existence
      runOneMove(board, argv[3]);
   }

   return 0;
}