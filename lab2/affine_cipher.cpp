#include <iostream>
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
int multiplicative_inverse(int a, int n)
{
    int r1 = n, r2 = a, q, r, t;
    int t1 = 0, t2 = 1;
    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        r2 = r;
        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }
    while (t1 < 0)
    {
        t1 += n;
    }
    return t1;
}
int main()
{
    // write a program to find affine cipher
    string plaintext, ciphertext;
    cout << "enter the plain text: ";
    cin >> plaintext;
    int k1, k2;
    cout << "enter the key value pair (k1, k2) :";
    cin >> k1 >> k2;

    // encryption
    for (int i = 0; i < plaintext.size(); i++)
    {
        int value = plaintext[i] - 'a';
        ciphertext += (value * k1 + k2) % 26 + 'a';
    }
    cout << "corresponding cipher text given to plain text will be " << ciphertext << endl;
    int ans;
    if (gcd(k1, 26) == 1)
    {
        ans = multiplicative_inverse(k1, 26);
    }
    else
    {
        cout << "multiplicative inverse of k1 is not possible" << endl;
        exit(0);
    }
    // decryption
    string decryptedText;
    for (int i = 0; i < ciphertext.size(); i++)
    {
        int value = ((ciphertext[i] - 'a') - k2);
        int final = ans * value;
        while (final < 0)
        {
            final += 26;
        }
        decryptedText += final % 26 + 'a';
    }
    cout << "decrypted text will be " << decryptedText << endl;
    return 0;
}