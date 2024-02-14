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
void solve(int a, int n)
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
    cout << "the multiplicative inverse of given number " << a << " is "
         << t1 << endl;
}
int main()
{
    // write a program to find multiplicative inverse of a given number
    int a, n;
    cout << "enter number whose multiplicative inverse you want to find:";
    cin >> a;
    cout << "enter the mod value: ";
    cin >> n;
    if (gcd(a, n) == 1)
    {

        solve(a, n);
    }
    else
    {
        cout << "multiplicative inverse is not possible because numbers are not prime or coprime " << endl;
    }
    return 0;
}