/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <algorithm>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* new_root=t->right;



		t->right=new_root->left;

    new_root->left=t;

		t=new_root;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K,class V>
int AVLTree<K,V>::balance( Node* & t){

		if(t==NULL){
				return 0;
		}

		int height_right;
    int height_left;
    if(t->right==NULL){
        height_right=-1;
    } else{
        height_right=t->right->height;
    }

		if(t->left==NULL){
			height_left=-1;
		} else{
			height_left=t->left->height;
		}

		return height_right-height_left;
}

template<class K,class V>
int AVLTree<K,V>::height_(Node* & t){
		if(t==NULL){
			return -1;
		}

		else{
			return 1+std::max(height_(t->left),height_(t->right));
		}
}

template <class K, class V>
void AVLTree<K,V>::update_height(Node*& t){

		if(t==NULL){
				return;
		}

		t->height=height_(t);

		update_height(t->left);
		update_height(t->right);

}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* new_root=t->left;



		t->left=new_root->right;

    new_root->right=t;

		t=new_root;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int height_right;
    int height_left;

    if(balance(subtree)==2){
				if(balance(subtree->right)==1){
						rotateLeft(subtree);
				} else if(balance(subtree->right)==-1){
						rotateRightLeft(subtree);
				}
		}

		if(balance(subtree)==-2){
				if(balance(subtree->left)==-1){
					rotateRight(subtree);
				} else if(balance(subtree->left)==1){
						rotateLeftRight(subtree);
				}
		}

		update_height(this->root);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}




template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here

    if(subtree==NULL){
        subtree=new Node(key,value);
    }

    if(subtree->key==key){
      return;
    }

    if(subtree->key<key){
      insert(subtree->right, key,value);
      rebalance(subtree);
    }
    else{
      insert(subtree->left,key,value);
      rebalance(subtree);
    }



}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left,key);
        rebalance(subtree);
    }
    else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
        rebalance(subtree);
    }
     else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
              Node* temp=subtree;
              subtree=NULL;
              if(temp!=NULL){
              delete temp;
              }
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* curr=subtree->left;
            while(curr->right!=NULL){
              curr=curr->right;
            }

            subtree->key=curr->key;
            subtree->value=curr->value;

            remove(subtree->left,curr->key);
            rebalance(subtree);

        } else {
            /* one-child remove */
            // your code here
            Node* temp=subtree;
            if(subtree->right != NULL){
              subtree=subtree->right;
              delete temp;
            } else{
              subtree=subtree->left;
              delete temp;
            }
        }
        // your code here
        rebalance(subtree);
    }

    rebalance(subtree);
}
