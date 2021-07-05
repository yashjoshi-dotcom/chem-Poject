#include <string>

using namespace std;

class Molecule
{
public:
    int natom;
    int charge;
    int *zvals;
    double **geom;
    string point_group;

    void print_geom();
    double bond(int atom1, int atom2);
    double angle(int atom1, int atom2, int atom3);
    double unit(int cart, int atom1, int atom2);
    void translate(double x, double y, double z);

    Molecule(const char *filename, int q);
    ~Molecule();
};
