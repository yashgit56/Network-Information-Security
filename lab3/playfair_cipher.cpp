#include <bits/stdc++.h>

using namespace std;

int main()
{
    string plainText, cipherText, keyText;

    unordered_map<int, bool> mp, mp2;

    cout << "enter the key text: ";
    cin >> keyText;

    int k = 0;

    int n = 5;
    int arr[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (k < keyText.size())
            {
                arr[i][j] = keyText[k];
                mp[keyText[k]] = true;
                k++;
            }
            else
            {
                for (int y = 0; y < 26; y++)
                {
                    if (mp[(y + 'a')] == false)
                    {
                        arr[i][j] = (y + 'a');
                        mp[(y + 'a')] = true;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << (char)arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << "enter the plain text: ";
    cin >> plainText;

    int len = plainText.size();

    for (int i = 0; i < plainText.size(); i++)
    {
        mp2[plainText[i]] = true;
    }

    if (len & 1)
    {
        for (int i = 0; i < 26; i++)
        {
            if (mp2[(i + 'a')] == false)
            {
                plainText += ('a' + i);
                break;
            }
        }
    }

    string finalText;

    for (int i = 0; i < plainText.size(); i += 2)
    {
        int first = plainText[i];
        int second = plainText[i + 1];

        int i1, j1, i2, j2;
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (arr[j][k] == first)
                {
                    i1 = j;
                    j1 = k;
                }
                if (arr[j][k] == second)
                {
                    i2 = j;
                    j2 = k;
                }
            }
        }

        if (i1 == i2)
        {
            j1 = (j1 + 1) % n;
            j2 = (j2 + 1) % n;
        }
        else if (j1 == j2)
        {
            i1 = (i1 + 1) % n;
            i2 = (i2 + 1) % n;
        }
        else
        {
            swap(j1, j2);
        }

        finalText += arr[i1][j1];
        finalText += arr[i2][j2];
    }

    cout << " encrypted cipher text from plain text based on matrix is: " << finalText << endl;

    string decryptedPlainText;

    for (int i = 0; i < finalText.size(); i += 2)
    {
        int first = finalText[i];
        int second = finalText[i + 1];

        int i1, j1, i2, j2;
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (arr[j][k] == first)
                {
                    i1 = j;
                    j1 = k;
                }
                if (arr[j][k] == second)
                {
                    i2 = j;
                    j2 = k;
                }
            }
        }

        if (i1 == i2)
        {
            j1 = (j1 - 1) % n;
            j2 = (j2 - 1) % n;
        }
        else if (j1 == j2)
        {
            i1 = (i1 - 1) % n;
            i2 = (i2 - 1) % n;
        }
        else
        {
            swap(j1, j2);
        }

        decryptedPlainText += arr[i1][j1];
        decryptedPlainText += arr[i2][j2];
    }

    cout << "decrypted plain text from final text is: " << decryptedPlainText << endl;

    return 0;
}
