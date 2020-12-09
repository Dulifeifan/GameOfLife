/**
 * CSE 411
 * Fall 2018
 * Programming Assignment #4
 *
 * There are two goals to this assignment.  The first is to implement an
 * iterative simulation.  The second is to practice visualization of a
 * simulation.  To that end, we will write a program that generates videos that
 * depict the execution of Conway's Game of Life.
 *
 * Conway's Game of Life is a simulation, which takes as its initial state a
 * two-dimensional grid of zeroes and ones.  The state of a cell in step k+1 is
 * determined exclusively by the state of that cell and its neighbors in step k.
 *
 * The rules are as follows:
 * - If a "1" cell has fewer than two live neighbors, then it becomes "0" in
 *   the next round.  This is "underpopulation"
 * - If a "1" cell has two or three live neighbors, then it remains "1" in the
 *   next round.  This is "healthy population"
 * - If a "1" cell has more than three live neighbors, then it becomes "0" in
 *   the next round.  This is "overpopulation".
 * - If a "0" cell has exactly three live neighbors, then it becomes "1" in the
 *   next round.  This is "reproduction".
 *
 * More details, and some examples, can be found at
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life.
 *
 * The input to your program will be a text file of N lines, each of which
 * contains M columns.  The values in this file will be 1s and 0s, and they will
 * represent the initial state of the game.  This input should be given by the
 * "-i" parameter.
 *
 * The output of your program will be a video file, generated with OpenCV.  The
 * file name will be determined by the "-o" parameter.  The frame rate of the
 * video will be determined by the "-f" parameter.  The number of pixels per
 * cell of the game will be determined by the "-p" parameter.  Your program
 * should run the simulation for a number of rounds determined by the "-r"
 * parameter.  Your output video should include a text watermark,
 * determined by the "-w" parameter.  Lastly, the "-s" parameter should
 * determine which frames of the game should be output to image files.  For
 * example, "-s1,4,16,256" would result in frames 1, 4, 16, and 256 being output
 * as images named frame1.png, frame4.png, frame16.png, and frame256.png
 *
 * You should consider using tbb or custom threads to both (a) parallelize the
 * creation of frames, and (b) pass frames to the video output generator.  Be
 * sure to use appropriate smart pointers to avoid memory leaks.
 *
 * Your program should use advanced features of C++ whenever appropriate.  It
 * should compile with g++ version 7.  You should organize your code into files
 * in a way that is appropriate.  You should comment your code.  You should only
 * use libraries that are easily installed into an Ubuntu Docker container.
 *
 * Turn-in will be via bitbucket.
 */

int main(int argc, char *argv[]) {
  // By now, you should be able to write your own argument parsing code :)
}