/* Your code here! */
#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"
using cs225::PNG;
using std::vector;
 class SquareMaze{
	public:
	SquareMaze();
	void maze_helper(DisjointSets& dset,int x,int y);
	void makeMaze(int width,int height);
	bool canTravel(int x,int y,int dir) const;
	void setWall(int x,int y,int dir,bool exists);
	vector<int> solve_helper(int z,int x,int y,vector <int> array);
	vector<int> solveMaze();
	PNG* drawMaze() const;
	PNG* drawMazeWithSolution();
	PNG* drawCreativeMaze();
	

	int width;
	int  height;

	struct cell{
		bool right;
		bool down;
		int num;
	};

	vector<cell> maze;


};
