// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstddef> 
#include <stdint.h>
#include <cstring>
#include "parts.cpp"

using namespace std;

    static struct option long_options[] = {
    { "help", no_argument, nullptr, 'h' },
    { "mode", required_argument, nullptr, 'm' },
    { nullptr,  0, nullptr, '\0'}
    };

// function declarations for main

void printHelp() {
  cout << "haaaalllppppp\n";
}  // printHelp()

int main(int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);

    int opt = 0;
    int option_index = 0;
    Graphs graph;

    while ((opt = getopt_long(argc, argv, "hm:", long_options, &option_index)) 
    != -1) {
        switch(opt) {
            case 'h':
                printHelp();
                exit(0);
                break;

            case 'm':

                if (*optarg == 'M') {
                    graph.is_prim = true;
                }
                else if (*optarg == 'F') {
                    graph.is_KNN = true;
                }
                else if (*optarg == 'O') {
                }
                else {
                    cerr << "Error: Invalid mode\n";
                    exit(1);
                }
                break;

            
            default: 
                cerr << "No mode specified" << endl;
                exit(1);
        }
    }
    graph.driver();
    return 0;
}