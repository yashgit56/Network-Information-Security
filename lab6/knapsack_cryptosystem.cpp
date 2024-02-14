#include <bits/stdc++.h>
#define int long long

using namespace std;

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

int findMultiplicativeInverse(int n, int a)
{
    int r1 = a, r2 = n, t1 = 0, t2 = 1, r, t;

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
        t1 += a;
    }
    return t1;
}

signed main()
{
    srand(time(nullptr));

    int n;
    cout << "enter the size of the vector: ";
    cin >> n;

    // key generation part performed by bob
    vector<int> privateKey(n, 0);
    privateKey[0] = rand() % 100;

    privateKey[1] = privateKey[0] + 1;
    for (int i = 2; i < n; i++)
    {
        privateKey[i] = privateKey[i - 1] * i + i;
    }

    int m = 0;
    for (auto i : privateKey)
    {
        cout << i << " ";
        m += i;
    }
    cout << endl;

    int w = rand() % 100;
    while (gcd(w, m) != 1)
    {
        w = rand() % 100;
    }

    // cout << m << " " << w << endl ;

    vector<int> publicKey(n, 0), x(n, 0);
    for (int i = 0; i < n; i++)
    {
        publicKey[i] = (privateKey[i] * w) % m;
    }
    cout << endl;

    // encryption by alice
    cout << "random binary sequence generated by alice is: " << endl;
    for (int i = 0; i < n; i++)
    {
        x[i] = rand() % 2;
        cout << x[i] << " ";
    }
    cout << endl;

    int encryptedOutput = 0;
    for (int i = 0; i < n; i++)
    {
        encryptedOutput += (publicKey[i] * x[i]);
    }

    // decryption by bob

    int decryption = (findMultiplicativeInverse(w, m) * encryptedOutput) % m;

    vector<int> decrypted_x(n, 0);

    for (int i = n - 1; i >= 0; i--)
    {
        if (decryption >= privateKey[i])
        {
            decryption -= privateKey[i];
            decrypted_x[i] = 1;
        }
        else
        {
            decrypted_x[i] = 0;
        }
    }

    cout << "decrypted binary sequence by bob which is encrypted by alice is:  " << endl;
    for (auto i : decrypted_x)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
