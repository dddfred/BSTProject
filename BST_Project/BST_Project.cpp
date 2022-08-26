/*
 * BSTree.cpp
 *
 *
 */

#include "BST_Project.hpp"

template<class T>
BSTree<T>::BSTree()
{
    root = NULL;
}

template<class T>
BSTree<T>::~BSTree()
{
    destroy (root);
}

template<class T>
void BSTree<T>::destroy()
{
    destroy (root);
}

template<class T>
void BSTree<T>::destroy(node<T> *&r)
{
    if (r != NULL)
    {
        destroy(r->left);
        destroy(r->right);
        delete r;
        r = NULL;
    }
}

template<class T>
BSTree<T>::BSTree(const BSTree<T> &other)
{
    copy(root, other.root); 
}

template<class T>
const BSTree<T>& BSTree<T>::operator=(const BSTree<T> &other)
{
    if (this != &other)
    {
        if (root != NULL)
            destroy (root);
        if (other.root == NULL)
            root = NULL;
        else
            copy(root, other.root);
    }

    return *this;
}

template<class T>
void BSTree<T>::copy(node<T> *&mroot, node<T> *croot)
{
    if (croot == NULL)
        mroot = NULL;
    else
    {
        mroot = new node<T>;
        mroot->info = croot->info;
        copy(mroot->left, croot->left);
        copy(mroot->right, croot->right);
    }
}

template<class T>
bool BSTree<T>::isEmpty()
{
    return root == NULL;
}

template<class T>
void BSTree<T>::preOrder()
{
    preOrder (root);
}

template<class T>
void BSTree<T>::preOrder(node<T> *p)
{
    if (p != NULL)
    {
        cout << p->info << " ";
        preOrder(p->left);
        preOrder(p->right);
    }
}

template<class T>
void BSTree<T>::postOrder()
{
    postOrder (root);
}

template<class T>
void BSTree<T>::postOrder(node<T> *p)
{
    if (p != NULL)
    {
        postOrder(p->left);
        postOrder(p->right);
        cout << p->info << " ";
    }
}

template<class T>
void BSTree<T>::inOrder()
{
    inOrder (root);
}

template<class T>
void BSTree<T>::inOrder(node<T> *p)
{
    if (p != NULL)
    {
        inOrder(p->left);
        cout << p->info << " ";
        inOrder(p->right);
    }
}

template<class T>
void BSTree<T>::insertItem(T item)
{
    node < T > *temp;
    node < T > *p;
    node < T > *trail;

    temp = new node<T>;
    temp->info = item;
    temp->left = NULL;
    temp->right = NULL;

    if (root == NULL)
        root = temp;
    else
    {
        p = root;

        while (p != NULL)
        {
            trail = p;

            if (p->info == item)
            {
                //cout << "\nERROR: DUPLICATES ARE NOT ALLOWED" << endl;
                p->timesUsed += 1;
                delete temp;
                return;
            }
            else if (item > p->info)
                p = p->right;
            else
                p = p->left;
        }

        if (item > trail->info)
            trail->right = temp;
        else
            trail->left = temp;

    }
    temp->length = temp->info.length();
}

template<class T>
bool BSTree<T>::searchItem(T item)
{
    node < T > *p;
    bool found;

    found = false;
    p = root;

    while (!found && p != NULL)
    {
        if (item == p->info)
            found = true;
        else if (item < p->info)
            p = p->left;
        else
            p = p->right;
    }

    return found;
}

template<class T>
void BSTree<T>::deleteItem(T item)
{
    deleteItem(root, item);
}

template<class T>
void BSTree<T>::deleteItem(node<T> *&p, T item)
{
    if (p == NULL)
        cout << "ITEM NOT FOUND";
    else if (item > p->info)
        deleteItem(p->right, item);
    else if (item < p->info)
        deleteItem(p->left, item);
    else
        deleteNode(p);
}

template<class T>
void BSTree<T>::deleteNode(node<T> *&p)
{
    node < T > *q;

    q = p;

    if (p->left == NULL)
    {
        p = p->right;
        delete q;
    }
    else if (p->right == NULL)
    {
        p = p->left;
        delete q;
    }
    else
    {
        q = p->left;
        node < T > *trail = NULL;

        while (q->right != NULL)
        {
            trail = q;
            q = q->right;
        }

        p->info = q->info;

        if (trail != NULL)
            trail->right = q->left;
        else
            p->left = q->left;

        delete q;
    }

}

//dummy function
template<class T>
void BSTree<T>::printInorderIndex(char firstLetter, ofstream &output)
{
    output << setw(8) << firstLetter << right << "\n";
    printInorderIndex(root, firstLetter, output);
}

//prints out inOrder, to be used to write report
template<class T>
void BSTree<T>::printInorderIndex(node<T> *p, char firstLetter, ofstream &output)
{
    if (p != NULL)
    {
        printInorderIndex(p->left, firstLetter, output);
        if (p->info[0] == firstLetter)
        {
            output << p->info << "\n";
        }
        printInorderIndex(p->right, firstLetter, output);

    }
}

//dummy function
template<class T>
void BSTree<T>::printOften(int totalWords, ofstream &output)
{
    printOften(root, totalWords, output);
}

//counts the words that are used too often and writes to report
template<class T>
int BSTree<T>::printOften(node<T> *p, int totalWords, ofstream &output)
{
    int count = 0;
    if (p != NULL)
    {
        count += printOften(p->left, totalWords, output);
        // calculation of words used more than 5% and length greater than 3 letters
        if (p->timesUsed / static_cast<float>(totalWords) > .05 && p->length > 3)
        {
            output << count + 1 << ") " << p->info << "\n";
            count++;
        }
        count += printOften(p->right, totalWords, output);

    }
    return count;
}



// dummy function to get root pointer
template<class T>
int BSTree<T>::uniqueWordsUsed()
{
    int count = 0;
    if (root != NULL)
    {
        count = uniqueWordsTotal(root);
    }
    return count;
}

//counts total number of unique words with more than 3 letters
template<class T>
int BSTree<T>::uniqueWordsTotal(const node<T> *root)
{
    // definition of what a unique word is and times used
    int used;
    if (root->timesUsed == 1 && root->length > 3)
    {
        used = 1;
    }
    else
    {
        used = 0;
    }
    if (root->left != NULL)
    {

        used += uniqueWordsTotal(root->left);
    }
    if (root->right != NULL)
    {
        used += uniqueWordsTotal(root->right);
    }
    return used;
}

//dummy function to get root pointer
template<class T>
int BSTree<T>::uniqueWordsUsedAll()
{
    int count = 0;
    if (root != NULL)
    {
        count = uniqueWordsTotalAll(root);
    }
    return count;
}

//counts the number of unique words used in total
template<class T>
int BSTree<T>::uniqueWordsTotalAll(const node<T> *root)
{
    int used;
    if (root->timesUsed == 1)
    {
        used = 1;
    }
    else
    {
        used = 0;
    }
    if (root->left != NULL)
    {

        used += uniqueWordsTotalAll(root->left);
    }
    if (root->right != NULL)
    {
        used += uniqueWordsTotalAll(root->right);
    }
    return used;
}
