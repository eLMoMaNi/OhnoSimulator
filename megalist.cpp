#include "Headers/megalist.h"

MegaNode::MegaNode(Proc proc, int remaining, int origin_index) : proc(proc)
{
    this->remaining = remaining;
    this->origin_index = origin_index;

    next = NULL;
    prev = NULL;
}

MegaList::~MegaList()
{
    MegaNode *cur = back, *prev;

    while (cur != NULL)
    {
        prev = cur;
        cur = cur->next;

        delete prev;
    }
}

MegaNode *MegaList::GetCurrent()
{
    return current;
}

int MegaList::Size()
{
    return size;
}

void MegaList::Insert(MegaNode *node)
{
    ++size;

    if (current == NULL)
    {
        current = front = back = node;

        return;
    }

    node->next = current;
    node->prev = current->prev;
    current->prev = node;

    if (node->prev != NULL)
    {
        node->prev->next = node;
    }

    if (back->prev != NULL)
    {
        back = back->prev;
    }
}

void MegaList::InsertSorted(MegaNode *node)
{
    ++size;

    if (current == NULL)
    {
        current = front = back = node;

        return;
    }

    MegaNode *cur = back;

    while (cur != NULL)
    {
        if (node->remaining >= cur->remaining)
        {
            node->next = cur;
            node->prev = cur->prev;
            cur->prev = node;

            if (node->prev != NULL)
            {
                node->prev->next = node;
            }

            break;
        }

        cur = cur->next;
    }

    if (cur == NULL)
    {
        node->prev = front;
        front->next = node;

        front = front->next;
        current = front;
    }

    if (back->prev != NULL)
    {
        back = back->prev;
    }
}

void MegaList::InsertBack(MegaNode *node)
{
    ++size;

    if (current == NULL)
    {
        current = front = back = node;

        return;
    }

    node->next = back;
    back->prev = node;

    back = node;
}

void MegaList::Remove(bool forward)
{
    --size;

    if (current->next != NULL)
    {
        current->next->prev = current->prev;
    }
    else
    {
        front = current->prev;
    }

    if (current->prev != NULL)
    {
        current->prev->next = current->next;
    }
    else
    {
        back = current->next;
    }

    if (forward)
    {
        current = current->next;
    }
    else
    {
        current = current->prev;
    }
}