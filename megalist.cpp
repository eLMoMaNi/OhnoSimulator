#include "proc.cpp"

struct MegaNode
{
    Proc proc;
    MegaNode *next;
    MegaNode *prev;

    int remaining;
    int origin_index; // The index for the process in the procs vector, this is bad practice ikr.

    MegaNode(Proc proc, int remaining, int origin_index) : proc(proc)
    {
        this->remaining = remaining;
        this->origin_index = origin_index;

        next = NULL;
        prev = NULL;
    }
};

class MegaList
{
    MegaNode *current = NULL;
    MegaNode *front = NULL;
    MegaNode *back = NULL;

    int size = 0;

public:
    ~MegaList()
    {
        MegaNode *cur = back, *prev;

        while (cur != NULL)
        {
            prev = cur;
            cur = cur->next;

            delete prev;
        }
    }

    MegaNode *GetCurrent()
    {
        return current;
    }

    int Size()
    {
        return size;
    }

    // Insert a MegaNode to the left of the current MegaNode
    void Insert(MegaNode *node)
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

    // Inserts a MegaNode into a sorted MegaList based on the remaining time
    void InsertSorted(MegaNode *node)
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

    // Inserts a MegaNode to the back of the MegaList
    void InsertBack(MegaNode *node)
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

    // Removes the current MegaNode and assigns a new one based on the value of the argument, defaults to the next one
    void Remove(bool forward = true)
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
};
