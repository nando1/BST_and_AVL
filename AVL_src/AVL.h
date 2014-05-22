/*
 * AVL.h
 *
 *  Created on: May 16, 2014
 *      Author: Fernando
 */

#ifndef AVL_H_
#define AVL_H_

#include <iostream>
#include <stack>
#include <queue>
#include "AVLNode.h"
using namespace std;

template<typename T>
class AVL {

public:
	AVL();
	~AVL();
	void insert(T data_in);
	void access(T data_in);
	void remove(T data_in);
	void print();
	void print_bfs();

private:
	AVLNode<T> *root;
	AVLNode<T> * _insert(T data_in, AVLNode<T> *node_in);
	AVLNode<T> * _access(T data_in, AVLNode<T> *node_in);
	AVLNode<T> * _remove(T data_in, AVLNode<T> **node_in);
	AVLNode<T> * _LL(AVLNode<T> *node_in);
	AVLNode<T> * _RR(AVLNode<T> *node_in);
	AVLNode<T> * _RL(AVLNode<T> *node_in);
	AVLNode<T> * _LR(AVLNode<T> *node_in);
	AVLNode<T> * _insert_rebalance(T data_in, AVLNode<T> *node_in);
	AVLNode<T> * _remove_rebalance(AVLNode<T> *node_in);
	AVLNode<T> ** _find_successor(AVLNode<T> **node_in);
	int _height(AVLNode<T> *node_in);
	int _update_height(AVLNode<T> *node_in);
	int _balance_factor(AVLNode<T> *node_in);
	void _print_preorder(AVLNode<T> *current);
	void _print_inorder(AVLNode<T> *current);
	void _print_postorder(AVLNode<T> *current);
	void _print_bfs(AVLNode<T> *current);

};

template<typename T>
AVL<T>::AVL() {
	root = NULL;
}

template<typename T>
AVL<T>::~AVL() {
	delete root;
}

/*
 * PUBLIC
 */

template<typename T>
void AVL<T>::insert(T data_in) {
	AVLNode<T> *n = _insert(data_in, root);
	if (root == NULL) {
		root = n;
	}
}

template<typename T>
void AVL<T>::access(T data_in) {
	_access(data_in, root);
}

template<typename T>
void AVL<T>::remove(T data_in) {
	_remove(data_in, &root);
}

template<typename T>
void AVL<T>::print() {
	AVLNode<T> *current = root;

	if (current == NULL) {
		cout << "Empty tree" << endl;
	} else {
		_print_preorder(current);
		_print_inorder(current);
		_print_postorder(current);
	}

}

template<typename T>
void AVL<T>::print_bfs() {
	AVLNode<T> *current = root;

	if (current == NULL) {
		cout << "Empty tree" << endl;
	} else {
		_print_bfs(current);
	}
}

/*
 * OPERATIONS
 */

template<typename T>
AVLNode<T> *AVL<T>::_insert(T data_in, AVLNode<T> *node_in) {
	// Recursively traverse tree until we reach NULL and then insert there
	// After insertion, process each node we traversed and update height/balance
	if (node_in == NULL) {
		cout << "Element inserted" << endl;
		return new AVLNode<T>(data_in);
	} else if (data_in < node_in->data) {
		node_in->left = _insert(data_in, node_in->left);
		node_in->height = _update_height(node_in);
		node_in = _insert_rebalance(data_in, node_in);
	} else if (data_in > node_in->data) {
		node_in->right = _insert(data_in, node_in->right);
		node_in->height = _update_height(node_in);
		node_in = _insert_rebalance(data_in, node_in);
	} else if (data_in == node_in->data) {
		cout << "Element already present" << endl;
	}
	return node_in;
}

template<typename T>
AVLNode<T> *AVL<T>::_access(T data_in, AVLNode<T> *node_in) {
	// Similar to insert except we don't do anything with the found node
	if (node_in == NULL) {
		cout << "Element not found" << endl;
		return NULL;
	} else {
		if (data_in == node_in->data) {
			cout << "Element accessed" << endl;
			return node_in;
		} else if (data_in < node_in->data) {
			return _access(data_in, node_in->left);
		} else if (data_in > node_in->data) {
			return _access(data_in, node_in->right);
		} else {
			cout << "Unknown error on line " << __LINE__ << endl;
			return NULL;
		}
	}
}

template<typename T>
AVLNode<T> * AVL<T>::_remove(T data_in, AVLNode<T> **node_in) {
	// Recursively traverse tree looking for node to delete
	if (*node_in == NULL) {
		cout << "Element not found" << endl;
		return *node_in;
	} else {
		// Found node to delete. Now check which case it is
		if (data_in == (*node_in)->data) {
			cout << "Element deleted" << endl;

			// 1 Child / 0 Child case
			if ((*node_in)->right == NULL) {
				// Swap left node with now deleted parent. OK if it's NULL
				*node_in = (*node_in)->left;
			}
			// Also 1 Child / 0 Child case
			else if ((*node_in)->left == NULL) {
				// Swap right node with now deleted parent. OK if it's NULL
				*node_in = (*node_in)->right;
			}
			// 2 child case
			else {
				// Find successor of node to be deleted
				AVLNode<T> **successor = _find_successor(&(*node_in));
				// Swap the data of node to be "deleted" with the successor's data
				(*node_in)->data = (*successor)->data;
				// Now we can delete the successor
				_remove((*successor)->data, successor);
			}
		} else if (data_in < (*node_in)->data) {
			_remove(data_in, &(*node_in)->left);
		} else {
			_remove(data_in, &(*node_in)->right);
		}

		// Perform rotations if necessary
		*node_in = _remove_rebalance(*node_in);

		return *node_in;
	}
}

/*
 * ROTATIONS
 */

template<typename T>
AVLNode<T> * AVL<T>::_LL(AVLNode<T> *node_in) {
	// Rotate
	AVLNode<T> *tmp1, *tmp2;
	tmp1 = node_in->left;
	if (tmp1 == NULL) {
		return node_in;
	}
	tmp2 = tmp1->right;
	tmp1->right = node_in;
	node_in->left = tmp2;

	// Handle case where we rotate and have a new root
	if (node_in == root) {
		root = tmp1;
	}

	// Update heights
	node_in->height = _update_height(node_in);
	tmp1->height = _update_height(tmp1);

	return tmp1;
}

template<typename T>
AVLNode<T> * AVL<T>::_RR(AVLNode<T> *node_in) {
	// Rotate
	AVLNode<T> *tmp1, *tmp2;
	tmp1 = node_in->right;
	if (tmp1 == NULL) {
		return node_in;
	}
	tmp2 = tmp1->left;
	tmp1->left = node_in;
	node_in->right = tmp2;

	// Handle case where we rotate and have a new root
	if (node_in == root) {
		root = tmp1;
	}

	// Update heights
	node_in->height = _update_height(node_in);
	tmp1->height = _update_height(tmp1);

	return tmp1;
}

template<typename T>
AVLNode<T> * AVL<T>::_RL(AVLNode<T> *node_in) {
	node_in->right = _LL(node_in->right);
	return _RR(node_in);
}

template<typename T>
AVLNode<T> * AVL<T>::_LR(AVLNode<T> *node_in) {
	node_in->left = _RR(node_in->left);
	return _LL(node_in);
}

/*
 * UTILITY FUNCTIONS
 */

template<typename T>
AVLNode<T> *AVL<T>::_insert_rebalance(T data_in, AVLNode<T> *node_in) {
	// Check if rotations are necessary
	int bf = _balance_factor(node_in);
	// LL Case
	if ((bf > 1) && (data_in < node_in->left->data)) {
		return _LL(node_in);
	}
	// RR Case
	if ((bf < -1) && (data_in > node_in->right->data)) {
		return _RR(node_in);
	}
	// LR Case
	if ((bf > 1) && (data_in > node_in->left->data)) {
		node_in->left = _RR(node_in->left);
		return _LL(node_in);
	}
	// RL Case
	if ((bf < -1) && (data_in < node_in->right->data)) {
		node_in->right = _LL(node_in->right);
		return _RR(node_in);
	}
	return node_in;
}

template<typename T>
AVLNode<T> *AVL<T>::_remove_rebalance(AVLNode<T> *node_in) {
	if (node_in != NULL) {
		node_in->height = _update_height(node_in);
		int bf = _balance_factor(node_in);

		// Left Left Case
		if (bf > 1 && _balance_factor(node_in->left) >= 0)
			node_in = _LL(node_in);

		// Left Right Case
		if (bf > 1 && _balance_factor(node_in->left) < 0) {
			node_in->left = _RR(node_in->left);
			node_in = _LL(node_in);
		}

		// Right Right Case
		if (bf < -1 && _balance_factor(node_in->right) <= 0)
			node_in = _RR(node_in);

		// Right Left Case
		if (bf < -1 && _balance_factor(node_in->right) > 0) {
			node_in->right = _LL(node_in->right);
			node_in = _RR(node_in);
		}
	}
	return node_in;
}

template<typename T>
AVLNode<T> ** AVL<T>::_find_successor(AVLNode<T> **node_in) {
	// Our successor of the input node is the next largest element in the right subtree
	AVLNode<T> **tmp = &(*node_in)->right;
	while ((*tmp)->left != NULL) {
		tmp = &(*tmp)->left;
	}
	return tmp;
}

template<typename T>
int AVL<T>::_height(AVLNode<T> *node_in) {
	// Utility function to get height properly even if node is null
	if (node_in == NULL) {
		return -1;
	}
	return node_in->height;
}

template<typename T>
int AVL<T>::_update_height(AVLNode<T> *node_in) {
	// Utility function to compute new height
	if (node_in == NULL) {
		return -1;
	}
	return 1 + max(_height(node_in->left), _height(node_in->right));
}

template<typename T>
int AVL<T>::_balance_factor(AVLNode<T> *node_in) {
	// Utility function to compute balance factor
	if (node_in == NULL) {
		return 0;
	}
	return _height(node_in->left) - _height(node_in->right);
}

/*
 * PRINT FUNCTIONS
 */

template<typename T>
void AVL<T>::_print_preorder(AVLNode<T> *current) {
	stack<AVLNode<T> *> s;
	s.push(current);

	while (!s.empty()) {
		current = s.top();
		s.pop();
		cout << current->data << " ";
		if (current->right != NULL) {
			s.push(current->right);
		}
		if (current->left != NULL) {
			s.push(current->left);
		}
	}
	cout << endl;
}

template<typename T>
void AVL<T>::_print_inorder(AVLNode<T> *current) {
	stack<AVLNode<T> *> s;
	while (true) {

		while (current != NULL) {
			s.push(current);
			current = current->left;
		}

		if ((current == NULL) && !s.empty()) {
			current = s.top();
			s.pop();
			cout << current->data << " ";
			current = current->right;
		}

		if ((current == NULL) && s.empty()) {
			break;
		}
	}
	cout << endl;
}

template<typename T>
void AVL<T>::_print_postorder(AVLNode<T> *current) {
	stack<AVLNode<T> *> s1, s2;
	s1.push(current);
	while (!s1.empty()) {
		current = s1.top();
		s1.pop();
		s2.push(current);
		if (current->left != NULL) {
			s1.push(current->left);
		}
		if (current->right != NULL) {
			s1.push(current->right);
		}
	}
	while (!s2.empty()) {
		current = s2.top();
		s2.pop();
		cout << current->data << " ";
	}

	cout << endl;
}

template<typename T>
void AVL<T>::_print_bfs(AVLNode<T> *current) {
	queue<AVLNode<T> *> q;
	while (current != NULL) {
		cout << current->data << " ";
		if (current->left != NULL) {
			q.push(current->left);
		}
		if (current->right != NULL) {
			q.push(current->right);
		}
		if (!q.empty()) {
			current = q.front();
			q.pop();
		} else {
			break;
		}
	}
	cout << endl;
}

#endif /* AVL_H_ */
