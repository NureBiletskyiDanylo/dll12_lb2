#include <Dll12.h>// Include rsa.h for function declarations
#include <iostream> // Include the necessary header for std::cout, std::endl


using namespace std;
std::string encryptRSA_in(const std::string& data, int e, int n);
void generateRSAKeys_in(int& d, int& e, int& n);
int getRandomNumber(int min, int max);
int gcd(int a, int b);
std::string decryptRSA_in(const std::string& encryptedData, int d, int n);
unsigned long int pow_custom(char c, int n);
unsigned long int modExp(unsigned long int base, unsigned long int exp, unsigned long int mod);
//int main() {
//
//    srand(time(NULL)); 
//
//
//    int d0, e0, n0;
//    generateRSAKeys_in(d0, e0, n0);
//    cout << d0 << " - d0; " << e0 << " - e0; " << n0 << " - n0; ";
//
//    for (int i = 0; i < 5; ++i) {
//
//        std::string data = "data";
//
//
//        std::string e0t = encryptRSA_in(data, e0, n0);
//
//
//        std::string d0e0t = decryptRSA_in(e0t, d0, n0);
//
//
//        if (d0e0t != data) {
//            std::cout << "Error: d0e0t not equal data[" << i << "]" << std::endl;
//        }
//        else {
//            std::cout << "d0e0t = data[" << i << "]" << std::endl;
//        }
//    }
//
//    return 0;
//}
//
//
//
//
//void generateRSAKeys_in(int& d, int& e, int& n) {
//    int p = getRandomNumber(200, 500); // Increase the range for p
//    int q = getRandomNumber(200, 500); // Increase the range for q
//    n = p * q;  // number n
//    int phi = (p - 1) * (q - 1); // number phi
//    e = getRandomNumber(2, phi - 1); // generate random E
//    while (gcd(e, phi) != 1) {
//        e = getRandomNumber(2, phi - 1);    // check if E is a coprime of phi
//    }
//    d = 1;
//    while ((d * e) % phi != 1) {
//        d++; // fill d with the value that fits the formula
//    }
//}
//
//int getRandomNumber(int min, int max) {
//    return rand() % (max - min + 1) + min;
//}
//
//int gcd(int a, int b) {
//    while (b != 0) {
//        int temp = b;
//        b = a % b;
//        a = temp;
//    }
//    return a;
//}
//
//std::string encryptRSA_in(const std::string& data, int e, int n) {
//    std::string encryptedData = "";
//    for (char c : data) {
//        unsigned long int encryptedChar = modExp(c, e, n);
//        std::cout << encryptedChar;
//        encryptedData += std::to_string(encryptedChar) + " ";
//    }
//    return encryptedData;
//}
//
//std::string decryptRSA_in(const std::string& encryptedData, int d, int n) {
//    std::string decryptedData = "";
//    size_t pos = 0;
//    while (pos < encryptedData.length()) {
//        size_t spacePos = encryptedData.find(' ', pos);
//        if (spacePos == std::string::npos) {
//            spacePos = encryptedData.length();
//        }
//        std::string encryptedCharStr = encryptedData.substr(pos, spacePos - pos);
//        unsigned long int encryptedChar = std::stoul(encryptedCharStr); // Use unsigned long int to avoid overflow
//        unsigned long int decryptedChar = modExp(encryptedChar, d, n); // Use modular exponentiation
//        decryptedData += static_cast<char>(decryptedChar);
//        pos = spacePos + 1;
//    }
//    return decryptedData;
//}
//
//
//unsigned long int modExp(unsigned long int base, unsigned long int exp, unsigned long int mod) {
//    unsigned long int result = 1;
//    base = base % mod;
//    while (exp > 0) {
//        if (exp % 2 == 1)
//            result = (result * base) % mod;
//        exp = exp >> 1;
//        base = (base * base) % mod;
//    }
//    return result;
//}

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

std::string encryptRSA_in(const std::string& data, int e, int n);
std::string decryptRSA_in(const std::string& encryptedData, int d, int n);
void generateRSAKeys_in(int& d, int& e, int& n);
int getRandomNumber(int min, int max);
int gcd(int a, int b);
unsigned long int modExp(unsigned long int base, unsigned long int exp, unsigned long int mod);

int main() {

    srand(time(NULL));

    int d0, e0, n0;
    generateRSAKeys_in(d0, e0, n0);
    std::cout << d0 << " - d0; " << e0 << " - e0; " << n0 << " - n0; ";

    std::string data = "data";

    std::string e0t = encryptRSA_in(data, e0, n0);

    std::string d0e0t = decryptRSA_in(e0t, d0, n0);

    if (d0e0t != data) {
        std::cout << "Error: d0e0t not equal data" << std::endl;
    }
    else {
        std::cout << "d0e0t = data" << std::endl;
    }

    return 0;
}

std::string encryptRSA_in(const std::string& data, int e, int n) {
    std::string encryptedData = "";
    const int blockSize = 2; // Set the block size
    for (size_t i = 0; i < data.length(); i += blockSize) {
        std::string block = data.substr(i, blockSize);
        unsigned long int encryptedBlock = 0;
        for (char c : block) {
            encryptedBlock = (encryptedBlock * 256) + c; // Combine characters into one large number
        }
        unsigned long int encryptedChar = modExp(encryptedBlock, e, n);
        encryptedData += std::to_string(encryptedChar) + " ";
    }
    return encryptedData;
}

std::string decryptRSA_in(const std::string& encryptedData, int d, int n) {
    std::string decryptedData = "";
    const int blockSize = 2; // Set the block size
    size_t pos = 0;
    while (pos < encryptedData.length()) {
        size_t spacePos = encryptedData.find(' ', pos);
        if (spacePos == std::string::npos) {
            spacePos = encryptedData.length();
        }
        std::string encryptedCharStr = encryptedData.substr(pos, spacePos - pos);
        unsigned long int encryptedChar = std::stoul(encryptedCharStr); // Use unsigned long int to avoid overflow
        unsigned long int decryptedBlock = modExp(encryptedChar, d, n); // Use modular exponentiation
        std::string decryptedBlockStr;
        while (decryptedBlock != 0) {
            char c = decryptedBlock & 0xFF; // Extract characters from decrypted block
            decryptedBlockStr = c + decryptedBlockStr;
            decryptedBlock >>= 8;
        }
        decryptedData += decryptedBlockStr;
        pos = spacePos + 1;
    }
    return decryptedData;
}


void generateRSAKeys_in(int& d, int& e, int& n) {
    int p = getRandomNumber(50, 100); // number p
    int q = getRandomNumber(50, 100); // number q
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

unsigned long int modExp(unsigned long int base, unsigned long int exp, unsigned long int mod) {
    unsigned long int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

unsigned long int pow_custom(char c, int n) {
    unsigned long int result = c;
    for (int i = n - 1; i > 0; i--) {
        result *= c;
    }
    return result;
}