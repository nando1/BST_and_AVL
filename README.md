BST and AVL Tree
================

This repository contains BST and AVL Tree implementations that I made for CS130A at UCSB in the Spring 2014 quarter. Part of the assignment involved doing an analysis of the performance of these two data structures. I timed various operations with different input sizes and I plotted this data to get an idea of input size vs execution time. The PDF of the full report is located in the repo, but here are some sample runs:

<em>BST with Random Insertions, Accesses, and Deletions</m>
![BST](bst_random.png?raw=true)

---

<em>AVL Tree with Insertions, Accesses, and Deletions all in Increasing Order</em>
![AVL](avl_increasing.png?raw=true)


How to Use
==========

Open up your terminal and type the following:

    make
    
To test the BST:

    ./bst < test.txt
    
Expected output for BST:

    Empty tree
    Element inserted
    Element inserted
    Element inserted
    Element inserted
    Element inserted
    Element accessed
    50 40 10 20 60 
    10 20 40 50 60 
    20 10 40 60 50 
    Element inserted
    50 40 10 20 15 60 
    10 15 20 40 50 60 
    15 20 10 40 60 50 
    Element already present
    Element inserted
    50 40 10 20 15 30 60 
    10 15 20 30 40 50 60 
    15 30 20 10 40 60 50 
    Element deleted
    50 10 20 15 30 60 
    10 15 20 30 50 60 
    15 30 20 10 60 50 
    Element inserted
    Element inserted
    50 10 20 15 30 40 60 70 
    10 15 20 30 40 50 60 70 
    15 40 30 20 10 70 60 50 
    Element not found
    50 10 20 15 30 40 60 70 
    10 15 20 30 40 50 60 70 
    15 40 30 20 10 70 60 50
    
To test the AVL Tree:

    ./avl < test.txt
    
Expected output for AVL Tree:

    Empty tree
    Element inserted
    Element inserted
    Element inserted
    Element inserted
    Element inserted
    Element accessed
    50 20 10 40 60 
    10 20 40 50 60 
    10 40 20 60 50 
    Element inserted
    20 10 15 50 40 60 
    10 15 20 40 50 60 
    15 10 40 60 50 20 
    Element already present
    Element inserted
    20 10 15 50 40 30 60 
    10 15 20 30 40 50 60 
    15 10 30 40 60 50 20 
    Element deleted
    20 10 15 50 30 60 
    10 15 20 30 50 60 
    15 10 30 60 50 20 
    Element inserted
    Element inserted
    20 10 15 50 30 40 60 70 
    10 15 20 30 40 50 60 70 
    15 10 40 30 70 60 50 20 
    Element not found
    20 10 15 50 30 40 60 70 
    10 15 20 30 40 50 60 70 
    15 10 40 30 70 60 50 20 
