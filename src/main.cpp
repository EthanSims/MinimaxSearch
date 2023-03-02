/**
 * @file main.cpp
 * @author Ethan Sims (ea.sims@me.com)
 * @brief handles command-line arguments and starts game
 */

#include <stdio.h>
#include <fstream>

using namespace std;

/**
 * @brief runs interactive mode of program (human and computer take turns)
 * 
 * @param inputFile filestream for file containing original board state
 * @param DEPTH depth of search (how many moves ahead to look)
 * @param humanNext boolean value denoting if it is the human's turn
 */
void runInteractive(ifstream &inputFile, const int DEPTH, bool humanNext) {
   if(!humanNext) {

   }
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

   if (!(argv[1] == "interactive" || argv[1] == "one-move")) {
      fprintf(stderr, "Unexpected argument given: %s", argv[1]);
      return -1;
   }

   if (argv[1] == "interactive" && !(argv[3] == "computer-next" || argv[3] == "human-next")) {
      fprintf(stderr, "Unexpected argument given: %s", argv[3]);
      return -1;
   }

   // open inputFile and test its existence
   ifstream inputFile(argv[2], ifstream::in);

   if (!inputFile) {
      fprintf(stderr, "Could not open file: %s", argv[2]);
      return -1;
   }

   if (argv[1] == "interactive") { // run interactive mode
      runInteractive(inputFile, sscanf(argv[4], "%d"), argv[3] == "human-next");
   } else { // run one-move mode

   }

   inputFile.close();

   return 0;
}