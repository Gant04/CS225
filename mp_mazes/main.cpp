#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;

		SquareMaze s;
		PNG* temp= s.drawCreativeMaze();
		temp->writeToFile("creative.png");
		delete temp;
    return 0;
}
