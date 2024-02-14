#include <iostream>
#define mod 26
using namespace std;
int main()
{
    // additive / shift / ceaser cipher text
    // encryption

    string plainText, cipherText = "";

    cout << "enter the plain text: ";
    cin >> plainText;

    int key, len = plainText.size(), temp;
    cout << "enter the value of key: ";
    cin >> key; // (for ceaser cipher take value as 3)
    for (int i = 0; i < len; i++)
    {
        temp = ((plainText[i] - 'a') + key) % mod;
        cipherText += ('a' + temp);
    }
    cout << "converted cipher text is: " << cipherText << endl;

    // decryption
    string decrypedPlainText;
    bool flag = false;
    int decryptedKey = -1;
    for (int i = 0; i < 26; i++)
    {
        string decrypedPlainText;
        for (int j = 0; j < len; j++)

        {
            int temp = ((cipherText[j] - 'a') - i);
            while (temp < 0)
            {
                temp += 26;
            }
            decrypedPlainText += ('a' + temp);
        }
        if (plainText == decrypedPlainText)
        {
            flag = true;
            decryptedKey = i;
        }
    }
    cout << "attacker find key to convert cipher text to plain text is: " << decryptedKey << endl;

    return 0;
}