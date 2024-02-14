#include <bits/stdc++.h>

using namespace std;

// program to implement elgamal crypto system

// for finding multiplicative inverse of a given number
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

// square and multiply which is used to calculate a^x mod n
// it is used while encryption and decryption of plain text
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

// check random number generated that is prime or not
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
}

int eulerTotient(int n)
{
    int result = n;

    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            result -= result / i;
            while (n % i == 0)
            {
                n /= i;
            }
        }
    }
    if (n > 1)
    {
        result -= result / n;
    }

    return result;
}

void findPrimitiveRoots(int n, vector<int> &primitiveRoots)
{
    int phin = eulerTotient(n);

    vector<vector<int>> matrix(n - 1, vector<int>(n - 1));

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            matrix[i - 1][j - 1] = square_and_multiply(i, j, n);
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        int order = -1;
        for (int j = 0; j < n - 1; j++)
        {
            if (matrix[i][j] == 1)
            {
                order = j + 1;
                break;
            }
        }
        if (order == phin)
        {
            primitiveRoots.push_back(i + 1);
        }
    }
}

int main()
{
    srand(time(NULL));

    int M;
    cout << "enter the message (numeric) : ";
    cin >> M;

    int p;

    do
    {
        p = rand() % 10000;
    } while (!miller_rabin_algorithm(p));

    vector<int> primitiveRoots;

    // generating all primitive roots for generated large prime number
    findPrimitiveRoots(p, primitiveRoots);

    // select random primitive root for encryption and decryption
    int e1 = primitiveRoots[(rand() % primitiveRoots.size())];

    // selecting random value of d such that 1 <= d <= p-2
    int d = 1 + rand() % (p - 2);

    int e2 = square_and_multiply(e1, d, p);

    // public key and private key from this are:
    cout << "public key: ( " << e1 << " , " << e2 << " , " << p << " )" << endl;
    cout << "private key: ( " << d << " ) " << endl;

    // elgamal encryption
    // c1 = e1^r mod p , c2 = (e2^r * m) mod p , r is random integer from <Zp*, x>

    int r = 1 + rand() % (p - 1);

    int c1 = square_and_multiply(e1, r, p);

    int c2 = (square_and_multiply(e2, r, p) * (M % p)) % p;

    cout << "cipher text generated for message " << M << " is : " << c1 << " and " << c2 << endl;

    // elgamal decryption
    // M = [c2 * (c1^d)^(-1)] mod p

    int temp = square_and_multiply(c1, d, p);

    int decryptedM = ((c2 % p) * (findMultiplicativeInverse(temp, p) % p)) % p;

    cout << "decrypted plain text from cipher text is: " << decryptedM << endl;

    return 0;
}
