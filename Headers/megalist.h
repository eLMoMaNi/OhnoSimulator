#ifndef MEGALIST_H
#define MEGALIST_H

#include "proc.h"

struct MegaNode
{
    Proc proc;
    MegaNode *next;
    MegaNode *prev;

    int remaining;
    int origin_index; // The index for the process in the procs vector, this is bad practice ikr.

    MegaNode(Proc proc, int remaining, int origin_index);
};

class MegaList
{
    MegaNode *current = NULL;
    MegaNode *front = NULL;
    MegaNode *back = NULL;

    int size = 0;

public:
    ~MegaList();

    // Returns the current MegaNode's pointer in the MegaList
    MegaNode *GetCurrent();

    // Returns the MegaList's current size
    int Size();

    // Sets current to the next MegaNode, sets it to back if current MegaNode is front
    void Next();

    // Sets current to the previous MegaNode, sets it to front if current MegaNode is back
    void Prev();

    // Insert a MegaNode to the left of the current MegaNode
    void Insert(MegaNode *node);

    // Inserts a MegaNode into a sorted MegaList based on the remaining time
    void InsertSorted(MegaNode *node);

    // Inserts a MegaNode to the back of the MegaList
    void InsertBack(MegaNode *node);

    // Removes the current MegaNode and assigns a new one based on the value of the argument, defaults to the next one
    void Remove(bool forward);
};

#endif
