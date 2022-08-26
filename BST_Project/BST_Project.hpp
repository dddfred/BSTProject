/*
 * BSTree.h
 *
 *  
 *
 */

#ifndef BSTREE_H_
#define BSTREE_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<class T>
struct node
{
        T info;
        node *left;
        node *right;
        int timesUsed = 1;
        int length = 0;
};

template<class T>
class BSTree
{
    private:
        node<T> *root;
        void destroy(node<T>*&);
        void preOrder(node<T>*);
        void inOrder(node<T>*);
        void postOrder(node<T>*);

        void printInorderIndex(node<T>*, char, ofstream&);
        int uniqueWordsTotal(const node<T>*);
        int printOften(node<T>*, int, ofstream&);
        int uniqueWordsTotalAll(const node<T>*);
    public:
        BSTree();
        ~BSTree();
        BSTree(const BSTree<T>&);
        const BSTree<T>& operator=(const BSTree<T>&);
        void destroy();
        void copy(node<T>*&, node<T>*);
        bool isEmpty();
        void insertItem(T);
        void deleteItem(T item);
        void deleteItem(node<T>*&, T);
        void deleteNode(node<T>*&);
        bool searchItem(T);
        void preOrder();
        void inOrder();
        void postOrder();

        void printInorderIndex(char firstLetter, ofstream&);
        int uniqueWordsUsed();
        void printOften(int, ofstream&);
        int uniqueWordsUsedAll();
};


#endif
