
#include <iostream>
#include <cmath>

using namespace std;

#include "Utils.cc"
#include "Maths.cc"
#include "Vector.cc"
#include "Vectors.cc"
#include "Particle.cc"
#include "Particles.cc"

////////////////////////////////////////////////////////////////////////////////

int main()
{
    Vector a,b;

    a.set( 3,2,1 );
    b.set( 5,6,7 );

    a.added( b ).display();
    a.scaled( 2 ).display();
}
