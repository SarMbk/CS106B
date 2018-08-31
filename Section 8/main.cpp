#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "treemap.h"
using namespace std;



/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct nodeT
{
    string key;
    struct nodeT* left;
    struct nodeT* right;
};


/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct nodeT* newNode(string key)
{
    struct nodeT* node = (struct nodeT*) malloc(sizeof(struct nodeT));
    node->key  = key;
    node->left  = nullptr;
    node->right = nullptr;
    return(node);
}


/* Function: TreeEqual
 * Usage: if (TreeEqual(t1, t2)) ...
 * -------------------------------
 * Function takes in two trees and returns whether they are equal (i.e.
 * have the same structure and values).*/
bool TreeEqual(nodeT *t1, nodeT *t2)
{
      if ((t1 == nullptr) && (t2 == nullptr))
            return true;
      if ((t1 == nullptr) || (t2 == nullptr))
            return false;
      return ((t1->key == t2->key) &&
              TreeEqual(t1->left, t2->left) &&
              TreeEqual(t1->right, t2->right));
}


void treePrint(nodeT *t){
    if (t != nullptr){
        treePrint(t->left);
        cout << t->key << endl;
        treePrint(t->right);
    }
}


/* Function: IsLeaf
 * Usage: if (IsLeaf(node)) ...
 * ---------------------------
 * Function returns whether a tree is a leaf.
 * A tree is considered a leaf if its two children are
 * both NULL.
 */
bool IsLeaf(nodeT *node){
      return((node->left == nullptr) && (node->right == nullptr));
}


/* Function: TrimLeaves
 * Usage: TrimLeaves(tree)
 * -----------------------
 * This function removes all of the leaves from the passed in binary
 * tree. The basic strategy is to recursively trim the trees.  Either
 * the current tree itself is a leaf, and we need to delete it from the
 * tree, or we need to recursively trim its left and right subtrees.
 */
void TrimLeaves(nodeT * & tree)
{
  if (tree != nullptr){
    if (IsLeaf(tree)){
        delete tree;
        tree = NULL;
    }
    else{
       TrimLeaves(tree->left);
       TrimLeaves(tree->right);
    }
  }
}


/*
 * Function: TreeHeight
 * Usage: TreeHeight(tree)
 * -----------------------------
 * Function returns the height of the passed in tree.
 */
int TreeHeight(nodeT *tree){
    if (tree == nullptr){
        return 0;
    } else{
        return (1 + max(TreeHeight(tree->left), TreeHeight(tree->right)));
    }
}


/* Function: IsBalanced
 * Usage: IsBalanced(tree)
 * -----------------------------
 * Function returns whether the passed in tree is balanced, meaning
 * that the height of its left and right subtree differ by no more
 * than one and that the left and right subtrees are themselves
 * balanced.
 */
bool IsBalanced(nodeT *tree){
    if (tree == nullptr){
      return true;
    } else{
        return((abs(TreeHeight(tree->left)-TreeHeight(tree->right)) <= 1)
               && IsBalanced(tree->left)
               && IsBalanced(tree->right));
    }
}



/* Main method testing all the functions */
int main()
{
    struct nodeT *root1 = newNode("one");
    root1->left = newNode("two");
    root1->right = newNode("three");
    root1->left->left  = newNode("four");
    root1->left->right = newNode("five");
    root1->left->right->left = newNode("six");

    struct nodeT *root2 = newNode("one");
    root2->left = newNode("two");
    root2->right = newNode("three");
    root2->left->left = newNode("four");
    root2->left->right = newNode("five");

    treePrint(root1);
    cout << endl;
    treePrint(root2);

    if(TreeEqual(root1, root2))
        cout <<"Both trees are identical." << endl << endl;
    else
        cout << "Trees are not identical." << endl << endl;

    struct nodeT *root3 = newNode("Jan");
    root3->left = newNode("Cindy");
    root3->right = newNode ("Marsha");
    root3->left->left = newNode("Bobby");
    root3->left->right = newNode("Greg");
    root3->right->right = newNode("Peter");
    root3->right->right->right = newNode("Tiger");

    treePrint(root3); cout << endl;
    TrimLeaves(root3);
    treePrint(root3);

    cout << endl;
    cout << TreeHeight(root1) << endl;
    cout << TreeHeight(root2) << endl;
    cout << boolToString(IsBalanced(root1)) << endl;
    cout << boolToString(IsBalanced(root2)) << endl;

    return 0;
}

