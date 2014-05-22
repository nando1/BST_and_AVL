/*
 * BSTNode.h
 *
 *  Created on: May 9, 2014
 *      Author: Fernando
 */

#ifndef BSTNODE_H_
#define BSTNODE_H_

#include<iostream>
using namespace std;

template<typename T>
class BSTNode {
public:
	BSTNode();
	BSTNode(T data_in);
	~BSTNode();
	T data;
	BSTNode *left;
	BSTNode *right;
};

template<typename T>
BSTNode<T>::BSTNode() {
	data = NULL;
	left = NULL;
	right = NULL;
}


template<typename T>
BSTNode<T>::BSTNode(T data_in) {
	data = data_in;
	left = NULL;
	right = NULL;
}

template<typename T>
BSTNode<T>::~BSTNode() {
	delete left;
	delete right;
}

#endif /* BSTNODE_H_ */
