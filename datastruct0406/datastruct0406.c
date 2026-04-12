#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 101

typedef struct {
    int degree;
    float coef[MAX_DEGREE];
} polynomial;

int N = 100;

int exp2idx(int exp) {
    return N - exp;
}

int idx2exp(int idx) {
    return N - idx;
}

// Zero()
polynomial Zero() {
    polynomial p;
    int i;
    p.degree = -1;
    for (i = 0; i <= N; i++)
        p.coef[i] = 0;
    return p;
}

// print()
void print(polynomial p) {
    int i;
    int exp;
    float coef;
    for (i = 0; i < MAX_DEGREE; i++) {
        if (p.coef[i] != 0) {
            coef = p.coef[i];
            exp = idx2exp(i);
            if (coef >= 0)
                printf("+");
            printf("%f x^%d ", coef, exp);
        }
    }
    printf("\n");
}

// IsZero()
int IsZero(polynomial p) {
    int i;
    for (i = 0; i < MAX_DEGREE; i++) {
        if (p.coef[i] != 0)
            return 0;
    }
    return 1;
}

// Coef()
float Coef(polynomial p, int expon) {
    return p.coef[exp2idx(expon)];
}

// LeadExp()
int LeadExp(polynomial p) {
    int i;
    for (i = 0; i < MAX_DEGREE; i++) {
        if (p.coef[i] != 0)
            return idx2exp(i);
    }
    return -1;
}

// Attach()
polynomial Attach(polynomial p, float coef, int expon) {
    p.coef[exp2idx(expon)] = coef;
    if (expon > p.degree)
        p.degree = expon;
    return p;
}

// Remove()
polynomial Remove(polynomial p, int expon) {
    p.coef[exp2idx(expon)] = 0;
    return p;
}

// SingleMult()
polynomial SingleMult(polynomial p, float coef, int expon) {
    polynomial pd;
    int i;
    int exp;
    pd = Zero();
    for (i = 0; i < MAX_DEGREE; i++) {
        if (p.coef[i] != 0) {
            exp = idx2exp(i) + expon;
            if (exp <= N)
                pd.coef[exp2idx(exp)] += p.coef[i] * coef;
        }
    }
    return pd;
}

// Add()
polynomial Add(polynomial p, polynomial q) {
    polynomial pd;
    int i;
    pd = Zero();
    for (i = 0; i < MAX_DEGREE; i++)
        pd.coef[i] = p.coef[i] + q.coef[i];
    pd.degree = (p.degree > q.degree) ? p.degree : q.degree;
    return pd;
}

// Multiply()
polynomial Multiply(polynomial p, polynomial q) {
    polynomial pd;
    int i, j;
    int exp;
    pd = Zero();
    for (i = 0; i < MAX_DEGREE; i++) {
        if (p.coef[i] != 0) {
            for (j = 0; j < MAX_DEGREE; j++) {
                if (q.coef[j] != 0) {
                    exp = idx2exp(i) + idx2exp(j);
                    if (exp <= N)
                        pd.coef[exp2idx(exp)] += p.coef[i] * q.coef[j];
                }
            }
        }
    }
    return pd;
}

int main() {
    polynomial a, b, result;

    // A(x) = x^2 + 2x + 3
    a = Zero();
    a.degree = 2;
    a.coef[exp2idx(2)] = 1;
    a.coef[exp2idx(1)] = 2;
    a.coef[exp2idx(0)] = 3;

    // B(x) = 4x^2 + 5x + 6
    b = Zero();
    b.degree = 2;
    b.coef[exp2idx(2)] = 4;
    b.coef[exp2idx(1)] = 5;
    b.coef[exp2idx(0)] = 6;

    printf("A: "); print(a);
    printf("B: "); print(b);

    printf("IsZero(A): %d\n", IsZero(a));
    printf("Coef(A, 2): %f\n", Coef(a, 2));
    printf("LeadExp(A): %d\n", LeadExp(a));

    result = Attach(a, 4, 3);
    printf("Attach(A, 4, 3): "); print(result);

    result = Remove(a, 1);
    printf("Remove(A, 1): "); print(result);

    result = SingleMult(a, 2, 1);
    printf("SingleMult(A, 2, 1): "); print(result);

    result = Add(a, b);
    printf("Add(A, B): "); print(result);

    result = Multiply(a, b);
    printf("Multiply(A, B): "); print(result);

    return 0;
}