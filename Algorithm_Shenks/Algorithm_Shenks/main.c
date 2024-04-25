#include <stdio.h>
#include <math.h>

int legendre_symbol(int a, int p) {
    int ls = (int)pow(a, (p - 1) / 2) % p;
    return ls == p - 1 ? -1 : ls;
}

int tonelli_shanks(int a, int p) {
    if (legendre_symbol(a, p) != 1) {
        return -1; // no square root exists
    }

    int q = p - 1;
    int s = 0;
    while (q % 2 == 0) {
        q /= 2;
        s++;
    }

    if (s == 1) {
        int x = (int)pow(a, (p + 1) / 4) % p;
        return x;
    }

    int z = 2;
    while (legendre_symbol(z, p) != -1) {
        z++;
    }

    int c = (int)pow(z, q) % p;
    int r = (int)pow(a, (q + 1) / 2) % p;
    int t = (int)pow(a, q) % p;

    int m = s;
    while (1) {
        if (t == 1) {
            return r;
        }

        int i = 0;
        int tt = t;
        while (tt != 1) {
            tt = (tt * tt) % p;
            i++;
        }

        int b = (int)pow(c, pow(2, m - i - 1)) % p;
        r = (r * b) % p;
        t = (t * b * b) % p;
        c = (b * b) % p;
        m = i;
    }
}

int main() {
    int a, p;
    printf("Enter the number whose square root you want to find: ");
    scanf_s("%d", &a);
    printf("Enter the prime number: ");
    scanf_s("%d", &p);

    int sqrt_a = tonelli_shanks(a, p);
    if (sqrt_a == -1) {
        printf("No square root exists.\n");
    }
    else {
        printf("Square root of %d mod %d is: %d\n", a, p, sqrt_a);
    }

    return 0;
}