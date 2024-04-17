// Dll12.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Dll12.h"
/*
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>


int getRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


DLL12_API void generateRSAKeys(int& d, int& e, int& n) {
    int p = getRandomNumber(10, 20); // number p
    int q = getRandomNumber(10, 20); // number q
    n = p * q;  // number n
    int phi = (p - 1) * (q - 1); // number phi
    e = getRandomNumber(2, phi - 1); // generate random E
    while (gcd(e, phi) != 1) { 
        e = getRandomNumber(2, phi - 1);    // check if E is simple number with phi and if not then generate new random number
    }
    d = 1;
    while ((d * e) % phi != 1) { 
        d++; // fill d with the value that fits the formula
    }
}


DLL12_API std::string encryptRSA(const std::string& data, int e, int n) {
    std::string encryptedData = "";
    for (char c : data) {
        int encryptedChar = pow(c, e);
        std::cout << encryptedChar;
        encryptedChar %= n;
        std::cout << encryptedChar;
        encryptedData += std::to_string(encryptedChar) + " ";
    }
    return encryptedData;
}


DLL12_API std::string decryptRSA(const std::string& encryptedData, int d, int n) {
    std::string decryptedData = "";
    size_t pos = 0;
    while (pos < encryptedData.length()) {
        size_t spacePos = encryptedData.find(' ', pos);
        if (spacePos == std::string::npos) {
            spacePos = encryptedData.length();
        }
        std::string encryptedCharStr = encryptedData.substr(pos, spacePos - pos);
        int encryptedChar = std::stoi(encryptedCharStr);
        int decryptedChar = pow(encryptedChar, d);
        decryptedChar %= n;
        decryptedData += static_cast<char>(decryptedChar);
        pos = spacePos + 1;
    }
    return decryptedData;
}
*/

#include <iostream> // Include the necessary header for std::cout, std::endl

#include <vector>;
#include <set>
using namespace std;


set<int> prime; // a set will be the collection of prime numbers,



int public_key;

int private_key;

int n;


DLL12_API void primefiller()
{

    // method used to fill the primes set is seive of

    // eratosthenes(a method to collect prime numbers)

    vector<bool> seive(250, true);

    seive[0] = false;

    seive[1] = false;

    for (int i = 2; i < 250; i++) {

        for (int j = i * 2; j < 250; j += i) {

            seive[j] = false;

        }

    } // filling the prime numbers

    for (int i = 0; i < seive.size(); i++) {

        if (seive[i])

            prime.insert(i);

    }
}
// picking a random prime number and erasing that prime
// number from list because p!=q

int pickrandomprime()
{

    int k = rand() % prime.size();

    auto it = prime.begin();

    while (k--)

        it++;

    int ret = *it;

    prime.erase(it);

    return ret;
}
int gcd(int a, int b) {

    if (b == 0) {

        return a;

    }

    return gcd(b, a % b);
}

DLL12_API void setkeys()
{

    int prime1 = pickrandomprime(); // first prime number

    int prime2 = pickrandomprime(); // second prime number

    // to check the prime numbers selected

    // cout<<prime1<<" "<<prime2<<endl;

    n = prime1 * prime2;

    int fi = (prime1 - 1) * (prime2 - 1);

    int e = 2;

    while (1) {

        if (gcd(e, fi) == 1)

            break;

        e++;

    } // d = (k*Φ(n) + 1) / e for some integer k

    public_key = e;

    int d = 2;

    while (1) {

        if ((d * e) % fi == 1)

            break;

        d++;

    }

    private_key = d;
}
// to encrypt the given number

long long int encrypt(double message)
{

    int e = public_key;

    long long int encrpyted_text = 1;

    while (e--) {

        encrpyted_text *= message;

        encrpyted_text %= n;

    }

    return encrpyted_text;
}
// to decrypt the given number

long long int decrypt(int encrpyted_text)
{

    int d = private_key;

    long long int decrypted = 1;

    while (d--) {

        decrypted *= encrpyted_text;

        decrypted %= n;

    }

    return decrypted;
}
// first converting each character to its ASCII value and
// then encoding it then decoding the number to get the
// ASCII and converting it to character

DLL12_API vector<int> encoder(string message)
{

    vector<int> form;

    // calling the encrypting function in encoding function

    for (auto& letter : message)

        form.push_back(encrypt((int)letter));

    return form;
}

DLL12_API string decoder(vector<int> encoded)
{

    string s;

    // calling the decrypting function decoding function

    for (auto& num : encoded)

        s += decrypt(num);

    return s;
}

