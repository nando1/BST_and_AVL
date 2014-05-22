all:
	g++ -c BST_src/BST_driver.cpp
	g++ -o bst BST_driver.o
	rm -f BST_driver.o
	g++ -c AVL_src/AVL_driver.cpp
	g++ -o avl AVL_driver.o
	rm -f AVL_driver.o