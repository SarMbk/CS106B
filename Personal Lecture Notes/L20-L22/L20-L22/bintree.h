#ifndef BINTREE_H
#define BINTREE_H


class binTree
{
public:
    binTree();

private:
    struct node{
        int val;
        node *left, *right;
    };
};

#endif // BINTREE_H
