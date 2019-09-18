/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */

template<typename T>
void BinaryTree<T>::mirror(Node* root_){
	if(root_==NULL){
		return;
	}

	Node* temp=root_->left;
	root_->left=root_->right;
	root_->right=temp;

	mirror(root_->left);
	mirror(root_->right);
}

    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
	mirror(root);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
	InorderTraversal<T> t(root);
	TreeTraversal<int>::Iterator it = t.begin();

	if(root==NULL){
		return true;
	}

	if(root->left==NULL && root->right==NULL){
		return true;
	}

	T prev= (*it)->elem;
	++it;
	T curr= (*it)->elem;

	while(true){
		if(prev>=curr){
			return false;

		}
		++it;

		if(!(it!=t.end())){
			break;
		}

		prev=curr;
		curr=(*it)->elem;

	}

	return true;

}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */

template <typename T>
T BinaryTree<T>::min(Node* root_) const{

	if(root_->left==NULL && root_->right==NULL){
							return root->elem;
	}



	T min_=root_->elem;

	if(root_->left!=NULL){
				T val=min(root_->left);
				if(val<min_){
					min_=val;
				}
	}

	if(root_->right!=NULL){
		T val= min(root_->right);
		if(val<min_){
			min_=val;
		}
	}



	return min_;

}

template <typename T>
T BinaryTree<T>::max(Node* root_) const{
	if(root_->left==NULL && root_->right==NULL){
							return root->elem;
	}



	T max_=root_->elem;

	if(root_->left!=NULL){
				T val=max(root_->left);
				if(val>max_){
					max_=val;
				}
	}

	if(root_->right!=NULL){
		T val= max(root_->right);
		if(val>max_){
			max_=val;
		}
	}



	return max_;
}

template <typename T>
void BinaryTree<T>::isOrderedRecursive(Node* root_,std::vector<T>& inorder_vector) const{
	if(root_==NULL){
		return;
	}

	else{
		isOrderedRecursive(root_->left,inorder_vector);
		inorder_vector.push_back(root_->elem);

		isOrderedRecursive(root_->right,inorder_vector);

	}


}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here

    std::vector<T> inorder_vector;
    //isOrderedRecursive(root,inorder_vector);
    isOrderedRecursive(root,inorder_vector);
    if(root==NULL){
	return true;
    }

    if(root->left==NULL &&  root->right==NULL){


	return true;


	}

    for(int i=0; i<(int) inorder_vector.size();i++){
	//std::cout<<inorder_vector[i]<<std::endl;

     }

    for(int i=0;i<(int) inorder_vector.size()-1;i++){
	//std::cout<<inorder_vector[i]<<" "<<inorder_vector[i+1]<<std::endl;
	if(inorder_vector[i]>=inorder_vector[i+1]){
		return false;
	}
    }

	return true;


}
























/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths,std::vector<T> path,Node* root_) const{
	if(root_==NULL){
		return;
	}

	if(root_->left==NULL    && root_->right==NULL){
		path.push_back(root_->elem);
		paths.push_back(path);
	} else{
		path.push_back(root_->elem);
		getPaths(paths,path,root_->left);
		getPaths(paths,path,root_->right);


	}
}

template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    // your code here
	std::vector<T> path;

	getPaths(paths,path,root);

}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */

template <typename T>
int BinaryTree<T>::sumDistances(int distance,Node* root_) const{
	if(root_==NULL){
			return 0;
	}

	return 1+distance+sumDistances(1+distance,root_->left)+sumDistances(1+distance,root_->right);
}

template <typename T>
int BinaryTree<T>::sumDistances() const
{
	return sumDistances(-1,root);
}
