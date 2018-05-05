#include <iostream>
#include "Assert.hpp"

// -----------------------------

template<int N>
int silnia() {
    return N * silnia<N - 1>();
}

template<>
int silnia<0>() {
    return 1;
}

// -----------------------------

template<int N, int M>
struct pow {
    enum {
        val = N * pow<N, M - 1>::val
    };
};

template<int N>
struct pow<N, 0> {
    enum {
        val = 1
    };
};

// -----------------------------

template<int N>
double quick_pow(double x) {
    return ((N % 2) ? x : 1) * quick_pow<N / 2>(x * x);
}

template<>
double quick_pow<1>(double x) { return x; };

template<>
double quick_pow<0>(double x) { return 1.0; };

// -----------------------------

template<int N>
double sin(double x) {
    return sin<N - 1>(x) +
           (N % 2 ? 1 : -1) * (quick_pow<2 * N - 1>(x)) / (silnia<2 * N - 1>());
};

template<>
double sin<0>(double x) { return 0; };

// -----------------------------

template<size_t N>
double inner(double *x, double *y) {
    return inner<N - 1>(x, y) + x[N - 1] * y[N - 1];
}

template<>
double inner<0>(double *x, double *y) {
    return 0;
}

// -----------------------------

template<size_t N, typename T>
struct Dot {
    static T dot(T *x, T *y) {
        return Dot<N - 1, T>::dot(x, y) + x[N - 1] * y[N - 1];
    }
};

template<typename T>
struct Dot<0, T> {
    static T dot(T *x, T *y) {
        return 0;
    }
};

template<size_t N, typename T>
T dot(T *x, T *y) {
    return Dot<N, T>::dot(x, y);
};

// -----------------------------

template<int M, size_t I>
double matrix_v_row(double *A, double *v) {
    return inner<M>(I * M + A, v);
}

template<int N, int M>
struct MatrixV {
    static void matrix_v(double *A, double *v, double *u) {
        u[N - 1] = matrix_v_row<M, N - 1>(A, v);
        MatrixV<N - 1, M>::matrix_v(A, v, u);
    }
};

template<int M>
struct MatrixV<0, M> {
    static void matrix_v(double *A, double *v, double *u) {
    }
};

template<int N, int M>
void matrix_v(double *A, double *v, double *u) {
    MatrixV<N, M>::matrix_v(A, v, u);
}

// -----------------------------

void test() {
    Assert(1, silnia<0>());
    Assert(1, silnia<1>());
    Assert(479001600, silnia<12>());

    Assert(1, (int) (pow<2, 0>::val));
    Assert(16, (int) (pow<2, 4>::val));
    Assert(100, (int) (pow<10, 2>::val));

    Assert(1.0, quick_pow<0>(4));
    Assert(16.0, quick_pow<4>(2));
    Assert(100.0, quick_pow<2>(10));

    Assert(0.0, sin<5>(0));
    AssertLess(Abs(sin<5>(3.14 / 12) - 0.25881), 0.0005);
    AssertLess(Abs(sin<5>(3.14 / 8) - 0.38268), 0.0005);

    double a[] = {1, 2};
    double b[] = {4, 5};
    double c[] = {4, 5, 7};
    Assert(5.0, inner<2>(a, a));
    Assert(14.0, inner<2>(a, b));
    Assert(41.0, inner<2>(b, b));
    Assert(90.0, inner<3>(c, c));

    Assert(5.0, dot<2>(a, a));
    Assert(14.0, dot<2>(a, b));
    Assert(41.0, dot<2>(b, b));
    Assert(90.0, dot<3>(c, c));
    int d[] = {2, 3};
    Assert(13, dot<2>(d, d));

    double A[] =
            {2, 4,
             3, 5};
    double v[] = {2, 3};
    auto u = (double*)malloc(2);
    matrix_v<2, 2>(A, v, u);
    Assert(16.0, u[0]);
    Assert(21.0, u[1]);
    free(u);
}

int main() {
    try {
        test();
    }
    catch (AssertionException &e) {
        std::cout << e.what() << std::endl;
    }
}