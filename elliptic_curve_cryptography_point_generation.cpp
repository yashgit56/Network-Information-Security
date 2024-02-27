#include <bits/stdc++.h>

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
            cout << "for x = " << x << " generated points are: "
                 << " ( " << x << " , " << y1 << " )  and ( " << x << " , " << y2 << " ) " << endl;
        }
        else if (square_and_multiply(w, (p - 1) / 2, p) == p - 1)
        {
            cout << "for x = " << x << " generated points not possible " << endl;
        }
        x++;
    }
}

int main()
{
    // finding points on the elliptic curve
    int a, b;
    cout << "enter the value of parameters a and b: ";
    cin >> a >> b;

    int p;
    cout << "enter the large prime number: ";
    cin >> p;

    vector<pair<int, int>> curve_points;

    elliptic_curve_points(a, b, p, curve_points);

    cout << "curve points generated on the curve are: ";
    for (auto i : curve_points)
    {
        cout << " ( " << i.first << " , " << i.second << " ) , ";
    }

    return 0;
}
