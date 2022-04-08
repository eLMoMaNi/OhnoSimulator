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
    void Insert(Proc proc);
    void InsertSorted(Proc proc);
    void Remove();
    int Size();
};
