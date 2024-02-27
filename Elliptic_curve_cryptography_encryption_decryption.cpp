#include <bits/stdc++.h>

using namespace std;

int a, b, p;

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
    int result = 1;
    while (x > 0)
    {
        if (x % 2 == 1)
            result = (result * a) % n;
        a = (a * a) % n;
        x /= 2;
    }
    return result;
}

pair<int, int> pointAddition(pair<int, int> &p1, pair<int, int> &p2)
{
    int lambda;
    pair<int, int> result;

    if (p1.first == p2.first && p1.second == -p2.second)
    {
        result = {0, 0};
    }
    else if (p1.first == p2.first && p1.second == p2.second)
    {
        lambda = ((3 * p1.first * p1.first + a) * findMultiplicativeInverse(2 * p1.second, p)) % p;
    }
    else
    {
        if (p2.first - p1.first < 0)
        {
            lambda = ((-1) * (p2.second - p1.second) * findMultiplicativeInverse((-1) * (p2.first - p1.first), p)) % p;
        }
        else
        {
            lambda = ((p2.second - p1.second) * findMultiplicativeInverse((p2.first - p1.first), p)) % p;
        }
    }

    while (lambda < 0)
    {
        lambda += p;
    }

    // cout << lambda << endl ;

    result.first = (lambda * lambda - p1.first - p2.first) % p;
    result.second = (lambda * (p1.first - result.first) - p1.second) % p;

    while (result.first < 0)
    {
        result.first += p;
    }
    while (result.second < 0)
    {
        result.second += p;
    }

    return result;
}

pair<int, int> scalarMultiply(int d, pair<int, int> &e1)
{
    pair<int, int> result = e1;

    for (int i = 1; i < d; i++)
    {
        result = pointAddition(result, e1);
    }
    return result;
}

void elliptic_curve_points(int a, int b, int p, vector<pair<int, int>> &curve_points)
{
    int x = 0;

    while (x < p)
    {
        int temp = (pow(x, 3) + a * x + b);
        int w = temp % p;

        if (square_and_multiply(w, (p - 1) / 2, p) == 1)
        {
            while (sqrt(w) * sqrt(w) != w)
            {
                w += p;
            }
            int ans = sqrt(w);
            int y1 = ans % p;
            int y2 = ans * (-1);
            while (y2 < 0)
            {
                y2 += p;
            }
            curve_points.push_back({x, y1});
            curve_points.push_back({x, y2});
            // cout << "for x = " << x << " generated points are: " <<
            //     " ( " << x << " , " << y1 << " )  and ( " << x << " , " << y2 << " ) " << endl ;
        }
        else if (square_and_multiply(w, (p - 1) / 2, p) == p - 1)
        {
            // cout << "for x = " << x << " generated points not possible " << endl ;
        }
        x++;
    }
}

int main()
{
    srand(time(NULL));

    // Input parameters
    pair<int, int> M;
    cout << "enter the original message: ";
    cin >> M.first >> M.second;

    cout << "Enter the values of parameters a, b, and p: ";
    cin >> a >> b >> p;

    // Private key
    int d;
    cout << "Enter the private key at Bob's side: ";
    cin >> d;

    // Generate curve points
    vector<pair<int, int>> curve_points;
    elliptic_curve_points(a, b, p, curve_points);

    // Select a random point from the curve
        pair<int, int>
            e1 = curve_points[rand() % curve_points.size()];
    // pair<int,int> e1 = {1,4} ;

    // Scalar multiplication
    pair<int, int> e2 = scalarMultiply(d, e1);

    // Output keys
    cout << "Generated keys at both sides are: " << endl;
    cout << "Public key: ((" << e1.first << ", " << e1.second << "), ("
         << e2.first << ", " << e2.second << "), " << p << ")" << endl;
    cout << "Private key: " << d << endl;

    // encryption in elliptic curve cryptography
    int r = rand() % 10;
    pair<int, int>  c1 = scalarMultiply(r, e1);
    pair<int, int> temp = scalarMultiply(r, e2);

    pair<int, int> c2 = pointAddition(M, temp);

    // cout << c1.first << " " << c1.second << " " << c2.first << " " << c2.second << endl ;

    // decryption in elliptic curve cryptography
        pair<int, int> scalarDecrypt = scalarMultiply(d, c1);
    scalarDecrypt.second *= -1;

    pair<int, int> decryptedPair = pointAddition(c2, scalarDecrypt);

    // cout << c2.first << " " << c2.second << " " << scalarDecrypt.first << " " << scalarDecrypt.second << endl ;
    cout << "randomly generated r is: " << r << endl;
    cout << decryptedPair.first << " " << decryptedPair.second << endl;

    return 0;
}
