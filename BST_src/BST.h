/*
 * BST.h
 *
 *  Created on: May 9, 2014
 *      Author: Fernando
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <stack>
#include <queue>
#include "BSTNode.h"
using namespace std;

template<typename T>
class BST {

public:
	BST();
	~BST();
	void insert(T data_in);
	void access(T data_in);
	void remove(T data_in);
	void print();
	void print_bfs();
private:
	BSTNode<T> *root;
	BSTNode<T> * _insert(T data_in, BSTNode<T> *node_in);
	BSTNode<T> * _access(T data_in, BSTNode<T> *node_in);
	BSTNode<T> * _remove(T data_in, BSTNode<T> **node_in);
	BSTNode<T> ** _find_successor(BSTNode<T> **node_in);
	void _print_preorder(BSTNode<T> *current);
	void _print_inorder(BSTNode<T> *current);
	void _print_postorder(BSTNode<T> *current);
	void _print_bfs(BSTNode<T> *current);
};

template<typename T>
BST<T>::BST() {
	root = NULL;
}

template<typename T>
BST<T>::~BST() {
	delete root;
}

/*
 * PUBLIC
 */

template<typename T>
void BST<T>::insert(T data_in) {
	BSTNode<T> *n = _insert(data_in, root);
	if (root == NULL) {
		root = n;
	}
}

template<typename T>
void BST<T>::access(T data_in) {
	_access(data_in, root);
}

template<typename T>
void BST<T>::remove(T data_in) {
	_remove(data_in, &root);
}

template<typename T>
void BST<T>::print() {
	BSTNode<T> *current = root;

	if (current == NULL) {
		cout << "Empty tree" << endl;
	} else {
		_print_preorder(current);
		_print_inorder(current);
		_print_postorder(current);
	}

}

template<typename T>
void BST<T>::print_bfs() {
	BSTNode<T> *current = root;

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
BSTNode<T> * BST<T>::_insert(T data_in, BSTNode<T> *node_in) {
	// Recursively traverse tree until we reach NULL and then insert there
	if (node_in == NULL) {
		cout << "Element inserted" << endl;
		return new BSTNode<T>(data_in);
	} else {
		if (data_in < node_in->data) {
			node_in->left = _insert(data_in, node_in->left);
		} else if (data_in > node_in->data) {
			node_in->right = _insert(data_in, node_in->right);
		} else if (data_in == node_in->data) {
			cout << "Element already present" << endl;
		} else {
			cout << "Unknown error on line " << __LINE__ << endl;
		}
		return node_in;
	}
}

template<typename T>
BSTNode<T> * BST<T>::_access(T data_in, BSTNode<T> *node_in) {
	// Similar to insert, but we don't do anything with the found node
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
BSTNode<T> * BST<T>::_remove(T data_in, BSTNode<T> **node_in) {
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
				BSTNode<T> **successor = _find_successor(&(*node_in));
				// Swap the data of node to be "deleted" with the successor's data
				(*node_in)->data = (*successor)->data;
				// Now we can delete the successor
				return _remove((*successor)->data, successor);
			}
		} else if (data_in < (*node_in)->data) {
			return _remove(data_in, &(*node_in)->left);
		} else {
			return _remove(data_in, &(*node_in)->right);
		}
		return *node_in;
	}
}


/*
 * UTILITY
 */

template<typename T>
BSTNode<T> ** BST<T>::_find_successor(BSTNode<T> **node_in) {
	// Our successor of the input node is the next largest element in the right subtree
	BSTNode<T> **tmp = &(*node_in)->right;
	while ((*tmp)->left != NULL) {
		tmp = &(*tmp)->left;
	}
	return tmp;
}

/*
 * PRINT FUNCTIONS
 */

template<typename T>
void BST<T>::_print_preorder(BSTNode<T> *current) {
	stack<BSTNode<T> *> s;
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
void BST<T>::_print_inorder(BSTNode<T> *current) {
	stack<BSTNode<T> *> s;
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
void BST<T>::_print_postorder(BSTNode<T> *current) {
	stack<BSTNode<T> *> s1, s2;
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
void BST<T>::_print_bfs(BSTNode<T> *current) {
	queue<BSTNode<T> *> q;
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

#endif /* BST_H_ */
