#include <exception>
using namespace std;

// DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {
private:
    struct Mat {
        int i;
        int j;
        TElem elem;
    };

    struct BSTNode {
        Mat info;
        int left;
        int right;
        int parent;
    };

    BSTNode *array;
    int linesNr;
    int colsNr;
    int root;
    int capacity;
    int firstEmpty;

    bool relation(int i1, int j1, int i2, int j2) const;
    int allocate();
    void deallocate(int position);
    int minimum(int node) const;
    void removeNode(int node);

public:
    Matrix(int nrLines, int nrCols);
    int nrLines() const;
    int nrColumns() const;
    TElem element(int i, int j) const;
    TElem modify(int i, int j, TElem e);
    ~Matrix();

    void resize(int newLines, int newCols);
};