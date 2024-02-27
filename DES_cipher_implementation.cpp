#include <bits/stdc++.h>
using namespace std;

string shift_left_once(string key_chunk)
{
    string shifted = "";
    for (int i = 1; i < 28; i++)
    {
        shifted += key_chunk[i];
    }
    shifted += key_chunk[0];
    return shifted;
}

string shift_left_twice(string key_chunk)
{
    string shifted = "";
    for (int i = 0; i < 2; i++)
    {
        for (int j = 1; j < 28; j++)
        {
            shifted += key_chunk[j];
        }
        shifted += key_chunk[0];
        key_chunk = shifted;
        shifted = "";
    }
    return key_chunk;
}

vector<string> generate_keys(string key)
{
    int pc1[56] = {
        57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

    int pc2[48] = {
        14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27,
        20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32};

    string perm_key = "";
    for (int i = 0; i < 56; i++)
    {
        perm_key += key[pc1[i] - 1];
    }

    string left = perm_key.substr(0, 28);
    string right = perm_key.substr(28, 28);

    vector<string> round_keys_generated;

    for (int i = 0; i < 16; i++)
    {
        if (i == 0 || i == 1 || i == 8 || i == 15)
        {
            left = shift_left_once(left);
            right = shift_left_once(right);
        }
        else
        {
            left = shift_left_twice(left);
            right = shift_left_twice(right);
        }

        string combined_key = left + right;

        string round_key = "";
        for (int i = 0; i < 48; i++)
        {
            round_key += combined_key[pc2[i] - 1];
        }
        round_keys_generated.push_back(round_key);
    }
    return round_keys_generated;
}

// function to generate initial permutation from the given 8 char text
string generateText(char c)
{
    int n = c;
    string result = "";

    while (n > 0)
    {
        result += to_string(n % 2);
        n /= 2;
    }
    while (result.size() != 8)
    {
        result.push_back('0');
    }
    reverse(result.begin(), result.end());
    return result;
}

string generateInitialPermutation(string plainText)
{
    string permutation = "";

    for (char c : plainText)
    {
        permutation += generateText(c);
    }

    return permutation;
}

string generateLeftBox(string initialPermutation)
{
    return initialPermutation.substr(32);
}

string generateRightBox(string initialPermutation)
{
    return initialPermutation.substr(0, 32);
}

string expand(string right)
{
    vector<vector<string>> rightParts;
    int count = 0;

    vector<string> temp;
    for (int i = 0; i < right.size(); i++)
    {
        count++;
        temp.push_back(to_string(right[i] - '0'));

        if (count == 4)
        {
            rightParts.push_back(temp);
            temp.clear();
            count = 0;
        }
    }
    for (int i = 0; i < rightParts.size(); i++)
    {
        if (i == rightParts.size() - 1)
        {
            rightParts[i].push_back(rightParts[0][0]);
        }
        else
        {
            rightParts[i].push_back(rightParts[i + 1][0]);
        }
    }
    for (int i = 0; i < rightParts.size(); i++)
    {
        if (i == rightParts.size() - 1)
        {
            rightParts[i].push_back(rightParts[0][0]);
        }
        else
        {
            rightParts[i].push_back(rightParts[i + 1][0]);
        }
    }
    for (int i = 0; i < rightParts.size(); i++)
    {
        string first_element = rightParts[i][0];

        for (int j = 0; j < rightParts[i].size() - 1; j++)
        {
            rightParts[i][j] = rightParts[i][j + 1];
        }
        rightParts[i][rightParts[i].size() - 1] = first_element;
    }

    string result = "";
    for (auto i : rightParts)
    {
        for (auto j : i)
        {
            result += j;
        }
    }
    return result;
}

string PerformXOR(string expansion, string key)
{
    int n = key.size() - 1;

    string ans = "";

    while (n >= 0)
    {
        if (expansion[n] == key[n])
        {
            ans = '0' + ans;
        }
        else
        {
            ans = '1' + ans;
        }
        n--;
    }
    return ans;
}

string RoundFunction(string expansion)
{
    string sBox[4][16] = {
        {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"},
        {"0010", "1100", "0100", "0001", "0111", "1010", "1011", "0110", "1000", "0105", "0011", "1111", "1101", "0000", "1110", "1001"},
        {"1110", "1011", "0010", "1100", "0100", "0111", "1101", "0001", "0105", "0000", "1111", "1010", "0011", "1001", "1000", "0110"},
        {"0100", "0010", "0001", "1011", "1010", "1101", "0117", "1000", "1111", "1001", "1100", "0105", "0110", "0011", "0000", "1110"}};

    vector<string> vect;
    string temp;
    int count = 0;
    for (int i = 0; i < expansion.size(); i++)
    {
        count++;
        temp += expansion[i];

        if (count == 6)
        {
            vect.push_back(temp);
            temp.clear();
            count = 0;
        }
    }

    string ans = "";
    for (int i = 0; i < vect.size(); i++)
    {
        int row = (vect[i][0] - '0') * 2 + (vect[i][5] - '0');
        int col = (vect[i][1] - '0') * 8 + (vect[i][2] - '0') * 4 + (vect[i][3] - '0') * 2 + (vect[i][4] - '0');

        ans += sBox[row][col];
    }
    return ans;
}

string DES_Encryption(string initialPermutation, string key)
{
    string leftPart = generateLeftBox(initialPermutation);
    string right = generateRightBox(initialPermutation);

    string expansion = expand(right);

    string rightPart = PerformXOR(expansion, key);

    string nextPart = RoundFunction(rightPart);

    string finalPart = PerformXOR(nextPart, leftPart);

    return leftPart + finalPart;
}

int main()
{
    string plainText, cipherText;

    cout << "enter the plain text ( 8 characters) : ";
    cin >> plainText;

    string initialPermutation = generateInitialPermutation(plainText);

    string key = "0111101001101100101010001001001100111001001100100010101001101011";

    vector<string> round_keys = generate_keys(key);

    for (int i = 0; i < 16; i++)
    {
        initialPermutation = DES_Encryption(initialPermutation, round_keys[i]);
        cout << "encrypted message after " << i + 1 << " round is : " << initialPermutation << endl;
    }
    return 0;
}
