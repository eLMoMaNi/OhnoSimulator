#include "proc.cpp"
struct MegaNode
{
    Proc proc;
    MegaNode *next;
    MegaNode *prev;
    int remaining;
    int origin_index; // the index in the procs vector, this is bad practice ikr.
};

class MegaList
{
    MegaNode *current = NULL;
    MegaNode *front = NULL;
    MegaNode *back = NULL;
    int size = 0;

public:
    MegaNode *GetCurrent()
    {
        return current;
    }
    int Size();
    void Insert(Proc proc);       // insert to the left
    void InsertSorted(Proc proc); // sorted by remaining time
    void Remove();                // remove current
};
