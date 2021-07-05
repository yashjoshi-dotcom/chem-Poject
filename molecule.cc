#include "molecule.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cassert>
#include <cmath>

using namespace std;
void Molecule::print_geom()
{
    for (int i = 0; i < natom; i++)
        printf("%d %8.5f %8.5f %8.5f\n", zvals[i], geom[i][0], geom[i][1], geom[i][2]);
}

double Molecule::bond(int a, int b)
{
    return sqrt((geom[a][0] - geom[b][0]) * (geom[a][0] - geom[b][0]) + (geom[a][1] - geom[b][1]) * (geom[a][1] - geom[b][1]) + (geom[a][2] - geom[b][2]) * (geom[a][2] - geom[b][2]));
}

// Returns the value of the unit vector between atoms a and b
// in the cart direction (cart=0=x, cart=1=y, cart=2=z)
double Molecule::unit(int cart, int a, int b)
{
    return -(geom[a][cart] - geom[b][cart]) / bond(a, b);
}

// Returns the angle between atoms a, b, and c in radians 
double Molecule::angle(int a, int b, int c)
{
    return acos(unit(0, b, a) * unit(0, b, c) + unit(1, b, a) * unit(1, b, c) + unit(2, b, a) * unit(2, b, c));
}

Molecule::Molecule(const char *filename, int q)
{
    charge = q;

    // open filename
    std::ifstream is(filename);
    assert(is.good());

    // read the number of atoms from filename
    is >> natom;

    // allocate space
    zvals = new int[natom];
    geom = new double *[natom];
    for (int i = 0; i < natom; i++)
        geom[i] = new double[3];

    for (unsigned int i = 0; i < natom; i++)
        is >> zvals[i] >> geom[i][0] >> geom[i][1] >> geom[i][2];

    is.close();
}   
Molecule::~Molecule()
{
    delete[] zvals;
    for (int i = 0; i < natom; i++)
        delete[] geom[i];
    delete[] geom;
}
void Molecule::translate(double x, double y, double z)
{
    for (int i = 0; i < natom; i++)
    {
        geom[i][0] += x;
        geom[i][1] += y;
        geom[i][2] += z;
    }
}   
