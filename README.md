# MST & TSP_Solver

# EECS 281: Project 4 - Among Us

**Project Identifier:** 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7

## Project Overview

This project implements various graph algorithms in the context of the game *Among Us*, where you play as both an Impostor and a Ghost Crewmate. There are three main parts:

- **Part A: Minimum Spanning Tree (MST)**
  - Devised a vent network (MST) that connects every room while minimizing the total distance.
  
- **Part B: FASTTSP Mode**
  - Approximates a solution for the Travelling Salesperson Problem (TSP) to efficiently visit every room and return to the starting location.
  
- **Part C: OPTTSP Mode**
  - Calculates the optimal TSP solution using a Branch and Bound (BnB) algorithm.

#### Note: 
The file executable file amongus.cpp is available for public view. Due to University policy I am unable to publish the file containing the MST and RSP algorithms, though it is available for viewing upon request.

## Command Line Arguments

### Required Arguments

- `-m, --mode {MST|FASTTSP|OPTTSP}`: 
  - `MST`: Find the Minimum Spanning Tree.
  - `FASTTSP`: Find a fast approximation to the TSP.
  - `OPTTSP`: Find the optimal TSP solution using a Branch and Bound algorithm.
  
- `-h, --help`: Display program usage and exit.

### Example Commands
- `./amongus --mode MST < inputFile.txt`
- `./amongus -m FASTTSP < inputFile.txt`
- `./amongus --mode OPTTSP < inputFile.txt`

## Input File Format

The input consists of an integer `n` (the number of vertices), followed by `n` ordered pairs of integers representing the Cartesian coordinates of the vertices (or rooms).

## Compilation and Execution

To compile and execute your project, ensure the following:

- **Makefile**: The project is compiled with `gcc` version 11.3.0 using the `-O3` optimization flag.
- To compile: `make -R -r`
- To run: `./amongus --mode {MST|FASTTSP|OPTTSP} < inputFile.txt`

### Sample Execution Command
$ ./amongus --mode MST < inputFile.txt


