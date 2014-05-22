/*
 * AVLNode.h
 *
 *  Created on: May 16, 2014
 *      Author: Fernando
 */

#ifndef AVLNODE_H_
#define AVLNODE_H_

#include <iostream>
using namespace std;

template<typename T>
class AVLNode {
public:
	AVLNode();
	AVLNode(T data_in);
	~AVLNode();
	T data;
	int height;
	AVLNode<T> *left;
	AVLNode<T> *right;
};

template<typename T>
AVLNode<T>::AVLNode() {
	data = NULL;
	height = 0;
	left = NULL;
	right = NULL;
}

template<typename T>
AVLNode<T>::AVLNode(T data_in) {
	data = data_in;
	height = 0;
	left = NULL;
	right = NULL;
}

template<typename T>
AVLNode<T>::~AVLNode() {
	delete left;
	delete right;
}

#endif /* AVLNODE_H_ */
