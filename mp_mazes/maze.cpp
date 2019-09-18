/* Your code here! */
#include "maze.h"
#include <stdlib.h>
#include <time.h>
#include <queue>
#include<iostream>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;
using std::queue;
using std::pair;
using std::random_shuffle;
using std::unordered_map;

SquareMaze::SquareMaze(){
	//mazeSquare=NULL;
}

void SquareMaze::setWall(int x,int y,int dir,bool exists){
	if(dir==0){
			maze[y*width+x].right=exists;
	}

	if(dir==1){
			maze[y*width+x].down=exists;
	}
}

bool SquareMaze::canTravel(int x,int y,int dir) const{
		if(dir==0 && x<width-1){
			if(maze[y*width+x].right==false){
				return true;
			}
		}
		if(dir==1 && y<height-1){
			if(maze[y*width+x].down==false){
					return true;
			}
		}
		if(dir==2 && x-1>=0){
			if(maze[y*width+x-1].right==false){
					return true;
			}
		}

		if(dir==3 && y-1>=0){
			if(maze[(y-1)*width+x].down==false){
					return true;
			}
		}

		return false;
}




void SquareMaze::maze_helper(DisjointSets& dset,int x,int y){
	/*if(x>=width || y>=height || x<0||y<0){
			return;
	}

	if(dset.find(x*width+y)>=0){
			return;
	}
	srand(time(NULL));
	int rand_num=rand()%2;*/
	/*
	if(x==width-1){
			rand_num=0;
	}
	if(y==height-1){
		rand_num=1;
	}*/

	/*if(rand_num==1){*/

	int d1_og=x*height+y;
	int d1_right= y * width + x + 1;
	int d1_down= (y+1)*width+x;
/*
	if(d1_og!=0){
	dset.setunion(0,d1_og);
}*/
/*
	if(x<(width-1)&& (dset.find(d1_og)!= dset.find(d1_right))){
			mazeSquare[x][y].right=false;
			dset.setunion(d1_og,d1_right);
	}  if(y< (height-1) && dset.find(d1_og)!=dset.find(d1_down)){
			mazeSquare[x][y].down=false;
			dset.setunion(d1_og,d1_down);
	}*/

	//}
	/*else{
		if(y<height-1 && mazeSquare[x][y].down==true && dset.find(x*height+y) != dset.find(x*height+y+1)){
				mazeSquare[x][y].down=false;
				dset.setunion(x*height+y,x*height+y+1);
		}  if(x<width-1 && mazeSquare[x][y].right==true && dset.find(x*height+y)!=dset.find((x+1)*height+y)){
				mazeSquare[x][y].right=false;
				dset.setunion(x*height+y,(x+1)*height+y);
		}

	}*/
	/*
	maze_helper(dset,x+1,y);
	maze_helper(dset,x,y+1);
	maze_helper(dset,x-1,y);
	maze_helper(dset,x,y-1);*/

}
void SquareMaze::makeMaze(int width,int height){

	this->width=width;
	this->height=height;
	
	maze.clear();
	cell temp;
	temp.right=true;
	temp.down=true;
	for(int i=0;i<width*height;i++){
		temp.num=i;
		maze.push_back(temp);
	}




	DisjointSets dset;

	dset.addelements(width*height);
	int numElements=width*height;

	while(numElements>1){
		int wall=rand()%2;
		int rand_x=rand()%width;
		int rand_y=rand()%height;
		//std::cout<<rand_x+rand_y*width<<std::endl;
		//std::cout<<numElements<<std::endl;
		if(wall==0){
			if(rand_x<(width-1) && dset.find(maze[rand_y*width+rand_x].num)!=dset.find(maze[rand_y*width+rand_x+1].num)){
				setWall(rand_x,rand_y,0,false);
				dset.setunion(maze[rand_y*width+rand_x].num,maze[rand_y*width+rand_x+1].num);
				numElements--;
			}
		} else{
			if(rand_y< (height-1) && dset.find(maze[rand_y*width+rand_x].num)!=dset.find(maze[(rand_y+1)*width+rand_x].num)){
				setWall(rand_x,rand_y,1,false);
				dset.setunion(maze[rand_y*width+rand_x].num,maze[(rand_y+1)*width+rand_x].num);
				numElements--;
			}
		}

	}

	/* code */
	//std::cout<<maze.size()<<std::endl;

	//srand(time(NULL));
}



vector<int> SquareMaze::solveMaze(){
/*
	vector<bool> visited;
	for(int i=0;i<width*height;i++){
		visited.push_back(false);
	}


	vector<cell*> parent;

	for(int i=0;i<width*height;i++){
		cell_queue.push_back(maze[i]);
		parent.push_back(NULL);

	}
	int max_dist=0;
	int max_x=0;

	while(!cell_queue.empty()){
		cell & temp=cell_queue.front();
		cell_queue.pop();
		int x_test=temp.x;
		int y_test=temp.y;

		if(y_test==height-1){
				if(temp.distance>max_dist){
					max_dist=temp.distance;
					max_x=x_test;
				}
		}
		*/


		queue <cell> cell_queue;
		unordered_map<int,bool> visited;
		unordered_map<int,cell*> parent;
		unordered_map<int,int> direction;
		/*for(int i=0;i<width*height;i++){
			visited.push_back(false);
			parent.push_back(NULL);
			direction.push_back(-1);
		}*/
		cell_queue.push(maze[0]);
		visited[0]=true;
		while(!cell_queue.empty()){
			cell temp=cell_queue.front();
			int x_test=temp.num%width;
			int y_test=temp.num/width;
				//int y_test=coordinates.second;
			cell_queue.pop();
				//std::cout<<x_test<<" "<<y_test<<std::endl;
			int cellNum=temp.num;

		if(canTravel(x_test,y_test,0) && visited.find(cellNum+1)==visited.end()){

			visited[cellNum+1]=true;
			direction[cellNum+1]=0;
			parent[cellNum+1]=& maze[cellNum];
			cell_queue.push(maze[cellNum+1]);
		}

		if(canTravel(x_test,y_test,1)&& visited.find(cellNum+width)==visited.end()){

			visited[cellNum+width]=true;
			direction[cellNum+width]=1;
			parent[cellNum+width]=& maze[cellNum];
			cell_queue.push(maze[cellNum+width]);
		}

		if(canTravel(x_test,y_test,2)&& visited.find(cellNum-1)==visited.end()){
			visited[cellNum-1]=true;
			direction[cellNum-1]=2;
			parent[cellNum-1]=& maze[cellNum];
			cell_queue.push(maze[cellNum-1]);
		}

		if(canTravel(x_test,y_test,3)&& visited.find(cellNum-width)==visited.end()){
			visited[cellNum-width]=true;
			direction[cellNum-width]=3;
			parent[cellNum-width]=& maze[cellNum];
			cell_queue.push(maze[cellNum-width]);
		}

	}

	vector<int> path;
	vector<int> max_path;
	max_path.resize(0);
	//parent[0]=NULL;
	//std::cout<<parent.size()<<std::endl;
	unsigned max=0;
	for(int i=0;i<width;i++){
		cell* curr= &maze[i+(height-1)*width];
		path.clear();
		while(curr->num!=0){
			//std::cout<<curr<<" "<<curr->num<<std::endl;
			path.insert(path.begin(),direction[curr->num]);
			curr=parent[curr->num];

		}
		if(path.size()>max_path.size()){
			max_path=path;
		}

	}

	return max_path;

	/*
	while(curr->parent!= NULL){
		cell* par=curr->parent;
		if(par->x==curr->x){
			if(par->y==curr->y-1){
				path_vector.insert(path_vector.begin(),1);
				continue;
			}

			if(par->y==curr->y+1){
				path_vector.insert(path_vector.begin(),3);
				continue;
			}
		}

		if(par->y==curr->y){

			if(par->x==curr->x-1){
				path_vector.insert(path_vector.begin(),0);
				continue;
			}

			if(par->x==curr->x+1){
				path_vector.insert(path_vector.begin(),2);
				continue;
			}


		}
	}
*/
	//return path_vector;

	//return vector<int>(3);
	}

	PNG* SquareMaze::drawMaze() const{
		PNG* pic= new PNG(10*width+1,10*height+1);

		pic->getPixel(0,0)=HSLAPixel(0,0,0);
		for(int i=0;i<10*height+1;i++){

			pic->getPixel(0,i)=HSLAPixel(0,0,0);
		}

		for(int i=10;i<10*width+1;i++){
			pic->getPixel(i,0)=HSLAPixel(0,0,0);
		}

		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				if(maze[i+j*width].right){
					for(int k=0;k<=10;k++){
						pic->getPixel((i+1)*10,j*10+k)=HSLAPixel(0,0,0);
					}

				}

				if(maze[i+j*width].down){
					for(int k=0;k<=10;k++){
						pic->getPixel(i*10+k,(j+1)*10)=HSLAPixel(0,0,0);
					}

				}


			}
		}


		return pic;

	}

	PNG* SquareMaze::drawMazeWithSolution(){

		PNG* pic=drawMaze();
		vector<int> path=solveMaze();

		int curr_x=5;
		int curr_y=5;
		for(unsigned int i=0;i<path.size();i++){
			if(path[i]==0){
				for(int j=0;j<=10;j++){
					pic->getPixel(curr_x+j,curr_y)=HSLAPixel(0,1,0.5,1);
				}
				curr_x=curr_x+10;
			}

			if(path[i]==1){
					for(int j=0;j<=10;j++){
						pic->getPixel(curr_x,curr_y+j)=HSLAPixel(0,1,0.5,1);

					}
					curr_y=curr_y+10;

			}

			if(path[i]==2){
				for(int j=0;j<=10;j++){
					pic->getPixel(curr_x-j,curr_y)=HSLAPixel(0,1,0.5,1);

				}
				curr_x=curr_x-10;

			}

			if(path[i]==3){
				for(int j=0;j<=10;j++){
					pic->getPixel(curr_x,curr_y-j)=HSLAPixel(0,1,0.5,1);
					//curr_y=curr_y-10;
				}
				curr_y=curr_y-10;
			}



		}

		for(int k=1;k<=9;k++){
			pic->getPixel((curr_x/10)*10+k,(height)*10)=HSLAPixel(0,0,1);
		}

	return pic;

	}

	PNG* SquareMaze::drawCreativeMaze(){
		this->width=13;
		this->height=13;

		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				cell temp;
				temp.right=true;
				//temp.num=i+j*width;
				if(i==width-1){
					temp.down=true;
					maze.push_back(temp);
				} else{
					temp.down=false;
					maze.push_back(temp);
				}
			}
		}

		for(int i=0;i<width*height;i++){

			maze[i].num=i;
		}
		
		for(int i=0;i<width-1;i++){
				if(i>=1){
			  maze[i+5*width].down=true;
				}
				maze[i+6*width].right=false;
				//maze[i+6*width].down=false;
		}
		return drawMazeWithSolution();

	}
