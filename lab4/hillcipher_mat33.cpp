#include <bits/stdc++.h>

using namespace std;

// encryption and decryption of hill cipher for 3*3 matrices

void getKeyMatrix(string keyText, int keyMatrix[][3])
{
    int value = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            keyMatrix[i][j] = (keyText[value] % 97);
            value++;
        }
    }
}

void encryptMessage(int messageMatrix[][1], int cipherMatrix[][1], int keyMatrix[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            cipherMatrix[i][j] = 0;

            for (int x = 0; x < 3; x++)
            {
                cipherMatrix[i][j] += (keyMatrix[i][x] * messageMatrix[x][j]);
            }

            cipherMatrix[i][j] = (cipherMatrix[i][j] % 26);
        }
    }
}

int findMultiplicativeInverse(int a)
{
    a = a % 26;
    int n = 26;

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
        t1 += 26;
    }
    return t1;
}

void inverseOfMatrix(int keyMatrix[][3])
{
    int determinant =
        (keyMatrix[0][0]) * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) - (keyMatrix[0][1]) * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[2][0] * keyMatrix[1][2]) + (keyMatrix[0][2]) * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[2][0] * keyMatrix[1][1]);

    int mul = findMultiplicativeInverse(determinant);

    int adj[3][3];

    adj[0][0] = keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1];
    adj[0][1] = -(keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0]);
    adj[0][2] = keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0];

    adj[1][0] = -(keyMatrix[0][1] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][1]);
    adj[1][1] = keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0];
    adj[1][2] = -(keyMatrix[0][0] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][0]);

    adj[2][0] = keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1];
    adj[2][1] = -(keyMatrix[0][0] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][0]);
    adj[2][2] = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];

    swap(adj[0][1], adj[1][0]);
    swap(adj[0][2], adj[2][0]);
    swap(adj[1][2], adj[2][1]);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int value = mul * adj[i][j] % 26;

            while (value < 0)
            {
                value += 26;
            }

            keyMatrix[i][j] = value;
        }
    }
}

void decryptMessage(int cipherMatrix[][1], int keyMatrix[][3], int decryptedPlainText[][1])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            decryptedPlainText[i][j] = 0;

            for (int x = 0; x < 3; x++)
            {
                decryptedPlainText[i][j] += (keyMatrix[i][x] * cipherMatrix[x][j]);
            }

            while (decryptedPlainText[i][j] < 0)
            {
                decryptedPlainText[i][j] += 26;
            }

            decryptedPlainText[i][j] = (decryptedPlainText[i][j]) % 26;
        }
    }
}

void HillCipher(string plainText, string keyText)
{
    int keyMatrix[3][3], messageMatrix[3][1], cipherMatrix[3][1];

    getKeyMatrix(keyText, keyMatrix);

    for (int i = 0; i < 3; i++)
        messageMatrix[i][0] = plainText[i] % 97;

    encryptMessage(messageMatrix, cipherMatrix, keyMatrix);

    string cipherText;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            cipherText += (cipherMatrix[i][j] + 97);
        }
    }

    cout << "encrypted cipher text is: " << cipherText << endl;

    inverseOfMatrix(keyMatrix);

    int decryptedPlainText[3][1];

    decryptMessage(cipherMatrix, keyMatrix, decryptedPlainText);

    string decryptedPlainTextString;

    for (int i = 0; i < 3; i++)
    {
        decryptedPlainTextString += (decryptedPlainText[i][0] + 97);
    }

    cout << "decrypted plain text from encrypted cipher text is: " << decryptedPlainTextString << endl;
}

int main()
{
    string plainText, keyText;

    cout << "enter the plain text: ";
    cin >> plainText;

    cout << "enter the key text: ";
    cin >> keyText;

    HillCipher(plainText, keyText);

    return 0;
}
