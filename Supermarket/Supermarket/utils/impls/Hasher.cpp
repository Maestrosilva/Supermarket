#include "..//headers//Hasher.h"

String Hasher::hash(const String& str) {
    int seed = 1234;
    String hash;
    const String hexDigits = "0123456789ABCDEF";
    char xorChar = str.getChar(seed % str.getSize());
    for (size_t i = 0; i < str.getSize(); i++) {
        char x = str.getChar(i) ^ xorChar;
        hash.append(hexDigits[(x >> 4) & 0xF]);
        hash.append(hexDigits[x & 0xF]);
    }
    return hash;
}

String Hasher::encrypt(const String& str) {
    String output = str;
    for (size_t i = 0; i < output.getSize(); ++i) {
        char c = output[i] ^ key;
        if (c == '\n') {
            c = ' ';
        }
        output[i] = c;
    }
    return output;
}

String Hasher::decrypt(const String& str) {
    String output = str;
    for (size_t i = 0; i < output.getSize(); ++i) {
        char c = output[i];
        c = c ^ key;
        if (c == '\n') {
            c = ' ';
        }
        output[i] = c;
    }
    return output;
}