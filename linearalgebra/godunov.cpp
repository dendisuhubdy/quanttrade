/*************************************************************************
	> File Name: godunov.cpp
	> Author: Dendi Suhubdy 
	> Mail: dasuhubd@ncsu.edu
	> Created Time: Thu Dec 31 16:08:53 2015
 ************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

template <class V, class I>
class DoubleSweep
{
    // The Balayage method from godunov 
private:
    // The Vectors
    Vector<V,I> a, b, c, f;
    V left;
    V right;

public:
    // all the public stuff
    DoubleSweep(const Vector<V,I>& lower,
               const Vector<V,I>& diagonal,
               const Vector<V,I>& upper,
               const Vector<V,I>& RHS,
               const V& bc_left,
               const V& bc_right);
};

template <class V, class I, class AS>
Vector<V,I> DoubleSweep<V,I>::solve()
{
    size_t N = a.Size() + 1;

    Vector<V, I> U(N+1,0);
    /* 
     * start index = 0; this vector will
     * contain the result
     */

    U[0] = left;
    u[N] = right;

    Vector <V,I> L(N, 0);
    L[0] = 0.0;

    int j = 0;

    for (j= L.MinIndex() + 1; j <= L.MaxIndex(); j++)
    {
        L[j] = (-c[j]) / (b[j] + (a[j] * L[j-1]));
    }

    Vector<V,I> K(N, 0);
    K[0] = left;

    for(j = K.MinIndex() + 1; j <= K.MaxIndex(); j++)
    {
        K[j] = (f[j] - (a[j] * K[j-1])) / (b[j] + (a[j] * L[j-1]));
    }

    for (j = N - 1; j >= 1; j--)
    {
        U[j] = (L[j] * U[j + 1]) + K[j];
    }
    return U;
}

int main(void)
{
    J = 10;
    h = 1.0 / double(J);
    Vector<double, int> A2(J-1, 1,1.0);
    Vector<double, int> B2(J-1, 1, -2.0 + (h*h));
    Vector<double, int> C2(J-1, 1, 1,0);
    Vector<double, int> R2(J-1,1,0.0);
    R2[R2.MaxIndex()] = -1.0;

    LHS = 0.0;
    RHS = 1.0;

    DoubleSweep<double, int> doubleSweepSolver(A2, B2, C2, LHS, RHS);
    Vector<double, int> ResultDS = doubleSweepSolver.solve();
    print(ResultDS);
}

