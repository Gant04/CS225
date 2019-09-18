#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    if(root==NULL){
    return -1;
    }

    else{
	return eval(root);
    }
}

double AbstractSyntaxTree::eval(Node* root_) const{
	if(root_->elem=="*"){
		return eval(root_->left)*eval(root_->right);
	} else if(root_->elem=="/"){
		return eval(root_->left)/eval(root_->right);
	} else if(root_->elem=="+"){
		return eval(root_->left)+eval(root_->right);
	} else if(root_->elem=="-"){
		return eval(root_->left)-eval(root_->right);
	} else{
		return std::stod(root_->elem);
	}

}	
