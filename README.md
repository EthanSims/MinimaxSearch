Author: Ethan Sims, ea.sims@me.com

This project was a school assignment from the Colorado School of Mines CSCI404 course.

The goal of this project was to implement a depth-limited minimax Search algorithm with alpha-beta pruning using an input map formatted properly in a txt file.

Command-line input format
  Interactive Mode: ./maxconnect4.exe interactive [input_file] [computer-next/human-next] [depth]
  One-move Mode: ./maxconnect4 one-move [input_file] [output_file] [depth]

Input file format: See input2.txt for context. The final number is used to decide who's turn is next (1 means red, 2 means green). The grid of numbers describes the board state. 0 means empty slot, 1 is a red slot, and 2 is a green slot.

In interactive mode, all output is sent to stdout. In one-move mode, iniput is printed, output is printed and saved to given output file.