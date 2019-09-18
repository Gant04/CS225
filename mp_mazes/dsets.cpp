/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
		for(int i=0;i<num;i++){
			table.push_back(-1);
		}

}

int DisjointSets::find(int elem){
		if(table[elem]<0){
				return elem;
		} else{
			  table[elem]=find(table[elem]);
				return table[elem];
		}
}

void DisjointSets::setunion(int a,int b){
	int root1=find(a);
	int root2=find(b);
	int new_size=table[root1]+table[root2];
	if(table[root1]<=table[root2]){
		table[root2]=root1;
		table[root1]=new_size;
	}
	else{
		table[root1]=root2;
		table[root2]=new_size;
	}
}
int DisjointSets::size(int elem){
		int a=find(elem);
		return table[a]*-1;
}
