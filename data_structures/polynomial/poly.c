#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poly.h"
#include <math.h>

// Helper function to create polynomial with all zeros
static Polynomial *init_poly(int size)
{
    Polynomial *p = malloc(sizeof(*p) + sizeof(double) * size);
    if (p == NULL)
    {
        fprintf(stderr, "Memory allocation falied\n");
        return NULL;
    }
    p->size = size;
    p->degree = p->size - 1;
    for (int i = 0; i < p->size; ++i)
    {
        p->coef[i] = 0;
    }
    return p;
}

void print_poly(const Polynomial *p)
{
    if (!p)
    {
        fprintf(stderr, "NULL Polynomial\n");
        return;
    }
    for (int i = p->degree; i >= 0; --i)
    {
        printf("%.2g", p->coef[i], i);
        if (i > 0)
        {
            i == 1 ? printf("x + ") : printf("x**%d + ", i);
        }
    }
    printf("\n");
}

// Creates polynomial from array, stores coef's in reverse order
Polynomial *poly(const double coef[], int size)
{
    if (size <= 0)
    {
        fprintf(stderr, "%s: Invalid size\n", __func__);
        return NULL;
    }

    Polynomial *p = malloc(sizeof(*p) + sizeof(double) * size);
    if (p == NULL)
    {
        fprintf(stderr, "%s: Memory allocation failed\n", __func__);
        return NULL;
    }
    p->degree = size - 1;
    p->size = size;

    // Storing polynomial coef in reverse order
    for (int i = p->size - 1; i >= 0; --i)
    {
        p->coef[i] = coef[p->degree - i];
    }

    return p;
}

static int min(int a, int b)
{
    return a < b ? a : b;
}

static int max(int a, int b)
{
    return a > b ? a : b;
}

Polynomial *add_poly(const Polynomial *p, const Polynomial *q)
{
    if (p == NULL || q == NULL)
    {
        fprintf(stderr, "%s, NULL Polynomial\n", __func__);
        return NULL;
    }

    Polynomial *r = init_poly(max(p->size, q->size));
    if (r == NULL)
    {
        fprintf(stderr, "%s, memory allocation failed\n", __func__);
        return NULL;
    }

    for (size_t i = 0; i < r->size; ++i)
    {
        r->coef[i] = (i <= p->degree ? p->coef[i] : 0) +
                     (i <= q->degree ? q->coef[i] : 0);
    }

    return r;
}

Polynomial *sub_poly(const Polynomial *p, const Polynomial *q)
{
    if (p == NULL || q == NULL)
    {
        fprintf(stderr, "%s, NULL Polynomial\n", __func__);
        return NULL;
    }

    Polynomial *r = init_poly(max(p->size, q->size));
    if (r == NULL)
    {
        fprintf(stderr, "%s, memory allocation falied\n", __func__);
        return NULL;
    }

    for (size_t i = 0; i < r->size; ++i)
    {
        r->coef[i] = (i <= p->degree ? p->coef[i] : 0) -
                     (i <= q->degree ? q->coef[i] : 0);
    }

    return r;
}

Polynomial *poly_deriv(const Polynomial *p)
{
    if (!p)
    {
        fprintf(stderr, "%s, NULL Polynomial\n", __func__);
        return NULL;
    }
    if (p->size == 1) // contant
    {
        Polynomial *r = init_poly(1);
        return r;
    }
    Polynomial *r = init_poly(p->size - 1);
    if (r == NULL)
        return NULL;
    for (int i = 1; i < p->size; ++i)
    {
        r->coef[i - 1] = p->coef[i] * i;
    }
    return r;
}

Polynomial *poly_mul(const Polynomial *p, const Polynomial *q)
{
    if (p == NULL || q == NULL)
    {
        fprintf(stderr, "%s, NULL Polynomial\n", __func__);
        return NULL;
    }

    Polynomial *r = init_poly(p->degree + q->degree + 1);
    if (r == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < p->size; ++i)
    {
        for (int j = 0; j < q->size; ++j)
        {
            r->coef[i + j] += p->coef[i] * q->coef[j];
        }
    }

    return r;
}

double eval_poly(const Polynomial *p, double x)
{
    if (!p)
    {
        fprintf(stderr, "%s, NULL polynomial\n", __func__);
        return 0;
    }
    double result = p->coef[0];
    for (int i = 1; i < p->size; ++i)
    {
        result += p->coef[i] * pow(x, i);
    }
    return result;
}

void free_poly(Polynomial **p)
{
    if (p && *p)
    {
        free(*p);
        *p = NULL;
    }
}