//Carlos Moreno, CS162, Program 5: Summer List, Submission #1

/*  
A header with the sturcture for list node and constants
*/

#ifndef summer_H
#define summer_H

#include <iostream> 
#include <cstring>
#include <cctype>
using namespace std;

const int SIZE = 500;

struct item {
    char *title;
    char *description;
    int priority;
    bool isPlanned;
    item * next;
};

#endif