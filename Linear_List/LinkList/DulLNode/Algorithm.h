#include "DNode.h"

template <typename T>
bool palindrome(DLinkList<T> L)
{
    DNode<T>* left = L.getHead()->next, *right = L.getHead()->prior;

    while (left != right && left->prior != right)
    {
        if (left->data != right->data)
            return false;
        left = left->next;
        right = right->prior;
    }
    return true;
}