/*
 * A0118400X
 * Shen Juanli
 * for CS3230 PJ2 @NUS
 * 2013.10
 *
 */

#include <iostream>
#include <string>
#include "RBT.h"

using namespace std;

RBT::Node* RBT::nil = new Node();

bool RBT::isRed(class Node* node)
{

    return node->color;
}

bool RBT::isBlack(class Node* node)
{

    return !(node->color);
}

bool RBT::hasRedChild(Node* node)
{
    if(isRed(node->children[LEFT]) || isRed(node->children[RIGHT]))
        return true;
    return false;
}

RBT::Node* RBT::Minimum(Node* node)
{
    while(node->children[LEFT] != nil)
        node = node->children[LEFT];

    return node;
}

RBT::Node* RBT::Successor(Node* node)
{
    if(node->children[RIGHT] != nil)
        return Minimum(node->children[RIGHT]);

    Node* parent = node->parent;
    while(parent != nil && node == parent->children[RIGHT])
    {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

long RBT::Height(Node* node)
{
    if(node == nil) return 0;

    return max(Height(node->children[LEFT]), Height(node->children[RIGHT])) + 1;
}

long RBT::Height()
{

    return Height(this->root);
}

TelType RBT::Search(KeyType key)
{
    Node* node = Locate(key);

    if(node != nil)
        return node->tel;
    return "-1";
}

void RBT::Insert(KeyType key, TelType tel)
{
    Node* track = nil;
    Node* current = this->root;

    while(current != nil)
    {
        track = current;

        if(key == current->key)
        {
            current->tel = tel;
            return;
        }
        else
        {
            if(key < current->key)
                current = current->children[LEFT];
            else
                current = current->children[RIGHT];    
        }      
    }

    Node* node = new Node(key, tel);
    node->parent = track;
    if(node->parent == nil)
        this->root = node;
    else if(key < track->key)
        track->children[LEFT] = node;
    else
        track->children[RIGHT] = node;

    // cout << "inserted!!" << endl;
    InsertFixup(node);
}

void RBT::Delete(KeyType key)
{
    Node* node = Locate(key);
    if(node == nil)
        return;

    Node* victim = nil;
    Node* replace = nil;

    if((node->children[LEFT] == nil) || (node->children[RIGHT] == nil))
    {
        victim = node;         
    }
    else
    {
        victim = Successor(node);
        node->key = victim->key;
        node->tel = victim->tel;        
    }

    if(victim->children[LEFT])
        replace = victim->children[LEFT];
    else
        replace = victim->children[RIGHT];

    if(replace != nil)
        replace->parent = victim->parent;

    if(victim->parent == nil)
        this->root = replace;
    else
    {
        if(victim == victim->parent->children[LEFT])
            victim->parent->children[LEFT] = replace;
        else
            victim->parent->children[RIGHT] = replace;
    }

    if(isBlack(victim))
        DeleteFixup(replace);

    // cout << "deleted!!" << endl;

    delete victim;
}

RBT::Node* RBT::Locate(KeyType key)
{
    Node* current = this->root;
    while(current != nil && current->key != key)
    {
        if(key < current->key)
            current = current->children[LEFT];
        else
            current = current->children[RIGHT];
    }

    return current;
}

void RBT::Rotate(Node* node, SIDE Side)
{
    // cout << "to rotate" << endl;
    SIDE sidE = (Side == LEFT ? RIGHT : LEFT);
    Node* oldChild = node->children[sidE];
    
    node->children[sidE] = oldChild->children[Side];
    if(node->children[sidE] != nil)
        node->children[sidE]->parent = node;

    oldChild->parent = node->parent;
    if(oldChild->parent == nil)
        this->root = oldChild;
    else if(node == node->parent->children[Side])
        node->parent->children[Side] = oldChild;
    else
        node->parent->children[sidE] = oldChild;

    oldChild->children[Side] = node;
    node->parent = oldChild;
}

void RBT::InsertFixup(Node* node)
{
    while(isRed(node->parent))
    {
        SIDE Side, sidE;
        Node* grand = node->parent->parent;
        if(node->parent == grand->children[LEFT])
        {
            Side = LEFT;
            sidE = RIGHT;
        }
        else
        {
            Side = RIGHT;
            sidE = LEFT;
        }

        Node* uncle = grand->children[sidE];

        if(isRed(uncle))
        {
            // case 1
            node->parent->color = BLACK;
            uncle->color = BLACK;
            grand->color = RED;

            node = grand;
        }
        else
        {
            if(node == node->parent->children[sidE])
            {
                // case 2
                node = node->parent;
                Rotate(node, Side);   
            }

            // case 3
            node->parent->color = BLACK;
            grand->color = RED;
            Rotate(grand, sidE);
        }
    }

    this->root->color = BLACK;
}

void RBT::DeleteFixup(Node* node)
{
    // cout << "to fixup delete" << endl;
    while(node != this->root && isBlack(node))
    {
        SIDE Side, sidE;
        if(node == node->parent->children[LEFT])
        {
            Side = LEFT;
            sidE = RIGHT;
        }
        else
        {
            Side = RIGHT;
            sidE = LEFT;
        }

        Node* sibling = node->parent->children[sidE];
        
        if(isRed(sibling))
        {
            // case 1
            sibling->color = BLACK;
            node->parent->color = RED;
            Rotate(node->parent, Side);
            sibling = node->parent->children[sidE];
        }

        if(isBlack(sibling->children[LEFT]) && isBlack(sibling->children[RIGHT]))
        {
            // case 2
            sibling->color = RED;
            node = node->parent;
        }
        else
        {
            if(isBlack(sibling->children[sidE]))
            {
                // case 3
                sibling->children[Side]->color = BLACK;
                sibling->color = RED;
                Rotate(sibling, sidE);
                sibling = node->parent->children[sidE];
            }

            // case 4
            sibling->color = node->parent->color;
            node->parent->color = BLACK;
            sibling->children[sidE]->color = BLACK;
            Rotate(node->parent, Side);
            node = this->root;
        }
    }
    // cout << "fixed!!" << endl;
    node->color = BLACK;
}

void RBT::Print(class Node* node, int depth)
{
    // root is at left

    if(node->children[RIGHT] != nil)
        Print(node->children[RIGHT], depth + 1);

    string aTab = "\t";
    string margin = "";

    for(int i = 0; i < depth; i++)
        margin += aTab;

    cout << margin << "(" << node->key << ")\n";

    if(node->children[LEFT] != nil)
        Print(node->children[LEFT], depth + 1);
}

void RBT::Print()
{
    cout << "===========Below is the tree: =============\n";

    if(this->root == nil)
        cout << "No Tree built!\n";
    else
        Print(this->root, 0);

    cout << "===========Above is the tree. =============\n\n";
}

int RBT::CheckBalance(Node* node)
{
    if(node == nil) 
        return 1;

    if(isRed(node) and hasRedChild(node))
    {
        cout << "ERROR: red-violation at node [" << node->key << "=" << (isRed(node) ? "r" : "b") << "]\n";
    }

    int lBlackHeight = CheckBalance(node->children[LEFT]);
    int rBlackHeight = CheckBalance(node->children[RIGHT]);

    if(lBlackHeight != rBlackHeight)
    {
        cout << "ERROR: black height violation at node [" << node->key << "=" << (isRed(node) ? "r" : "b") << "]\n";
    }

    if(isBlack(node)) return lBlackHeight + 1;

    return lBlackHeight;
}

void RBT::CheckBalance()
{
    cout << "Checking balance of the tree (OK if no error appears):\n";
    CheckBalance(this->root);
    cout << "Checking balance of the tree (OK if no error appears):DONE!\n";
}