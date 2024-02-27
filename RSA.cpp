#include <bits/stdc++.h>
#define int int64_t

using namespace std;

int findMultiplicativeInverse(int a, int phin)
{
    a = a % phin;
    int n = phin;

    int r1 = n, r2 = a, r, t1 = 0, t2 = 1, t;

    while (r2 > 0)
    {
        int q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }

    while (t1 < 0)
    {
        t1 += phin;
    }
    return t1;
}

int square_and_multiply(int a, int x, int n)
{
    int temp = x;
    string str;

    while (temp > 0)
    {
        int rem = temp % 2;
        str += to_string(rem);
        temp = temp / 2;
    }

    int y = 1;
    for (auto i : str)
    {
        if (i == '1')
        {
            y = (y * a) % n;
        }
        a = (a * a) % n;
    }
    return y;
}

bool miller_rabin_algorithm(int n)
{
    int z = n;
    z -= 1;

    int k = 0, m;

    while (z % 2 == 0)
    {
        k++;
        z /= 2;
    }
    m = z;

    int a = 2 + rand() % (n - 3);

    int b = square_and_multiply(a, m, n);

    if (b % n == 1)
    {
        return true;
    }

    for (int i = 0; i <= k - 1; i++)
    {
        if (b % n == n - 1)
        {
            return true;
        }
        else
        {
            int y = pow(b, 2);
            b = y % n;
        }
    }
    return false;
    // cout << k << " " << m << endl ;
}

int gcd(int a, int b)
{
    if (a < b)
    {
        return gcd(b, a);
    }
    else if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

signed main()
{
    int p = 9839, q = 4831;

    while (!miller_rabin_algorithm(p) || !miller_rabin_algorithm(q))
    {
        p = rand() % 1000;
        p = rand() % 1000;
    }

    int n = p * q;

    int phin = (p - 1) * (q - 1);

    int random = 13;

    while (gcd(random, phin) != 1)
    {
        random = 2 + rand() % (phin - 2);
    }

    int d = findMultiplicativeInverse(random, phin);
    // cout << d << endl;

    int plaintext;
    cout << "enter the plain text: ";
    cin >> plaintext;

    int ciphertext = square_and_multiply(plaintext, random, n);

    cout << "encrypted cipher text from plain text is: " << ciphertext << endl;

    int decryptedplaintext = square_and_multiply(ciphertext, d, n);

    cout << "decrypted plain text from cipher text is: " << decryptedplaintext << endl;

    return 0;
}
