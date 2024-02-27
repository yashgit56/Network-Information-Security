#include <bits/stdc++.h>
using namespace std;
int main()
{
    // monoalphabetic substitution cipher
    srand(time(0));

    string dummyText = "abcdefghijklmnopqrstuvwxyz", cipherText = "";

    vector<bool> flags(26, false);

    for (int i = 0; i < 26; i++)
    {
        int randomIndex = (65 + rand() % 26);
        while (flags[randomIndex] == true)
        {
            randomIndex = (65 + rand() % 26);
        }
        cipherText += (randomIndex);
        flags[randomIndex] = true;
    }

    cout << cipherText << endl;

    // encryption
    string plainText, convertedCipherText;
    cout << "enter the plain text: ";
    cin >> plainText;
    for (int i = 0; i < plainText.size(); i++)
    {
        convertedCipherText += cipherText[i];
    }
    cout << "converted cipher text is: " << convertedCipherText << endl;

    // decryption
    string decryptedText;
    for (int i = 0; i < convertedCipherText.size(); i++)
    {
        int idx = cipherText.find(convertedCipherText[i]);
        decryptedText += plainText[idx];
    }
    cout << decryptedText << endl;

    return 0;
}