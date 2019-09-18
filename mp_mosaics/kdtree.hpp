/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
		if(first[curDim]<second[curDim]){
			return true;
		} else if(first[curDim]>second[curDim]){
				return false;
		} else{
				return first<second?true:false;
		}

    //return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
			double currentBestDistanceSquared=0;
			double potentialDistanceSquared=0;

			for(int i=0;i<Dim;i++){
				currentBestDistanceSquared+=(target[i]-currentBest[i])*(target[i]-currentBest[i]);
			}

			for(int i=0;i<Dim;i++){
				potentialDistanceSquared+=(target[i]-potential[i])*(target[i]-potential[i]);
			}

			if(currentBestDistanceSquared>potentialDistanceSquared){
					return true;
			
			} else if(currentBestDistanceSquared<potentialDistanceSquared){
					return false;
			} else{
				return potential<currentBest?true:false;
			}
}

template <int Dim>
int KDTree<Dim>::Partition(vector<Point<Dim>> & newPoints,int left,int right,int currDim){
	int i=left-1;
	Point<Dim> pivot=newPoints[right];

	for(int j=left;j<=right-1;j++){
			if(smallerDimVal(newPoints[j],pivot,currDim)){
					i++;
					Point<Dim> temp=newPoints[i];
					newPoints[i]=newPoints[j];
					newPoints[j]=temp;
			}
	}

	Point<Dim> temp=newPoints[i+1];
	newPoints[i+1]=newPoints[right];
	newPoints[right]=temp;
	return i+1;

}

template<int Dim>
int  KDTree<Dim>::QuickSelect(vector<Point<Dim>>& newPoints, int left, int right,int k,int currDim){
		if(left==right){
				return left;
		}

		int pivot=Partition(newPoints,left,right,currDim);

		if(pivot-left==k-1){
				return pivot;
		} else if(pivot-left>k-1){
				return QuickSelect(newPoints,left,pivot-1,k,currDim);
		} else{
				return QuickSelect(newPoints,pivot+1,right,k-pivot+left-1,currDim);
		}
}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* root){
	if(root==NULL){
		return NULL;
	}

	KDTreeNode* new_root= new KDTreeNode(root->point);
	new_root->left=copy(root->left);
	new_root->right=copy(root->right);

	return new_root;

}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::KDTree_helper(vector<Point<Dim>> &  newPoints,int left,int right,int currDim){
		
		if(left>right){
				return NULL;

		}

		int k;
		int size=right-left+1;
		if(size%2==0){	
			k=(int) size/2;
		} else{
			k=(int) size/2+1;
		}

		int median= QuickSelect(newPoints,left,right,k,currDim);
		KDTreeNode* node2return= new KDTreeNode(newPoints[median]);
		node2return->left=KDTree_helper(newPoints,left,median-1,(currDim+1)%Dim);
		node2return->right=KDTree_helper(newPoints,median+1,right,(currDim+1)%Dim);

		return node2return;

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

		if(newPoints.empty()){
				root=NULL;
		} 

		vector<Point<Dim>> copy_vector;
		//std::copy(newPoints.begin(),newPoints.end(),copy_vector.begin());
		for(unsigned int i=0;i<newPoints.size();i++){
				copy_vector.push_back(newPoints[i]);
			//	std::cout<<newPoints[i]<<" ";

		}
		//std::cout<<std::endl;
		root=KDTree_helper(copy_vector,0,newPoints.size()-1,0);

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
	 *
   */

	this->root=copy(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* root){
	if(root==NULL){
		return;
	}

	KDTreeNode* temp_left=root->left;
	KDTreeNode* temp_right=root->right;
	delete root;
	
	root=NULL;
	destroy(temp_left);
	destroy(temp_right);

}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
	destroy(root);


}

template <int Dim>
double KDTree<Dim>::radius(const Point<Dim> first,const Point<Dim> second) const{
	double distanceSquared=0;
	
	for(int i=0;i<Dim;i++){
		distanceSquared+=(first[i]-second[i])*(first[i]-second[i]);
	}

	return std::sqrt(distanceSquared);

}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query,KDTreeNode* root,int currDim)const{
	if(root==NULL){
		return Point<Dim>();
	}

	if(root->left==NULL && root->right==NULL){
			return root->point;
	}

	Point<Dim> temp=root->point;
	Point<Dim> & currPoint=root->point;

	bool wentLeft;
	
	
	if(smallerDimVal(query,currPoint,currDim)){
		if(root->left!=NULL){
		temp=findNearestNeighbor(query,root->left, (currDim+1)%Dim);
		}
		wentLeft=true;
	} else{
		if(root->right!=NULL){		
		temp=findNearestNeighbor(query,root->right,(currDim+1)%Dim);
		}
		wentLeft=false;
	}
	Point<Dim> best=temp;

		

	double currRadius=radius(query,temp);
	
	if(shouldReplace(query,best,root->point)){
		best=root->point;
		double currRadius=radius(query,best);

		
	
	}
	
	//std::cout<<currRadius<<std::endl;
	if(query[currDim]-currRadius<=root->point[currDim] && root->point[currDim]<=query[currDim]+currRadius){
			Point<Dim> temp2;

			if(wentLeft && root->right!=NULL){
				temp2= findNearestNeighbor(query,root->right,(currDim+1)%Dim);
				if(shouldReplace(query,best,temp2)){
					best=temp2;
					currRadius=radius(query,temp2);
				}

	


			} 
			
			if(!wentLeft && root->left!=NULL){
				temp2=findNearestNeighbor(query,root->left,(currDim+1)%Dim);
				if(shouldReplace(query,best,temp2)){
					best=temp2;
					currRadius=radius(query,temp2);
				}
				

	
			}				

	}

	/*
	for(int i=0;i<Dim;i++){
		std::cout<<best[i]<<" ";
	}

	std::cout<<std::endl;*/

	return best;
	

	/*
	if(smallerDimVal(query,currPoint,currDim)){
		if(root->left!=NULL){
			temp=findNearestNeighbor(query,root->left,(currDim+1)%Dim);
		
			if(shouldReplace(query,temp,root->point)){
						
				if(root->right!=NULL){
					temp=findNearestNeighbor(query,root->right,(currDim+1)%Dim);
				}
			
				if(shouldReplace(query,temp,root->point)){
					return root->point;
				} 
				
				else{
					return temp;
				}
			}else{
				return temp;
			}
			
 		}
		else{
			return root->point;
		}
	}

	else{
		if(root->right!=NULL){
			temp=findNearestNeighbor(query,root->right,(currDim+1)%Dim);
			
			if(shouldReplace(query,temp,root->point)){
				if(root->left!=NULL){
					temp=findNearestNeighbor(query,root->left,(currDim+1)%Dim);
				}

				if(shouldReplace(query,temp,root->point)){
					return root->point;
				} else{
					return temp;
				}
			} else{
				return temp;
			}
		} 
		else{
			return root->point;
		}
	}
 
	*/

	

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
		if(root==NULL){
    return Point<Dim>();
		} else{
				return findNearestNeighbor(query,root,0);
		}
}

