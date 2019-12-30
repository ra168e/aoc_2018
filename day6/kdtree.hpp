#ifndef KDTREE_H
#define KDTREE_H

class KDTree:
{
    private:
        int axis;
        int bound;
        KDTree *left;
        KDTree *right;
        int index;

    public:
        KDTree();
        ~KDTree();
        KDTree* getLeafLeft();
        KDTree* getLeafRight(); 
        int getIndex();
        int setIndex();
}

#endif // KDTREE_H

