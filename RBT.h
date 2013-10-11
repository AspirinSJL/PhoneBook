/*
 * A0118400X
 * Shen Juanli
 * for CS3230 PJ2 @NUS
 * 2013.10
 *
 */

#ifndef __RBT_H__
#define __RBT_H__

#include <string>

using namespace std;

enum COLOR  {RED = true, BLACK = false};
enum SIDE   {LEFT, RIGHT};

typedef string KeyType;
typedef string TelType;

class RBT
{
private:
    class Node
    {
    public:
        COLOR color;
        KeyType key;
        TelType tel;
        Node* children[2];
        Node* parent;

        Node(KeyType key, TelType tel) : key(key), tel(tel), color(RED)
        {
            children[LEFT] = nil;
            children[RIGHT] = nil;
        };

        Node() : color(BLACK) {};
    };

public:
    Node* root;
    static Node* nil;

    RBT() : root(nil) {};

    inline bool isRed(class Node* node);
    inline bool isBlack(Node* node);
    inline bool hasRedChild(Node* node);
    Node* Minimum(Node* node);
    Node* Successor(Node* node);
    long Height(class Node* node);
    long Height();

    TelType Search(KeyType key);
    void Insert(KeyType key, TelType tel);
    void Delete(KeyType key);

    Node* Locate(KeyType key);
    void Rotate(Node* node, SIDE side);
    void InsertFixup(Node* node);
    void DeleteFixup(Node* node);

    void Print(class Node* node, int depth);
    void Print();
    int CheckBalance(Node* node);
    void CheckBalance();
};  

#endif // __RBT_H__