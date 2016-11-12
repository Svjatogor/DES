#include <iostream>
#include <string>
#include <bitset>
#define MAX_SIZE 40000

using namespace std;

void convert_bitset_to_str(string& str, const bitset<MAX_SIZE>& bit_str);

void convert_str_to_bitset(bitset<MAX_SIZE>& bit_str, const string& str);

int main() {
    string input_text = "fuck";
    const size_t str_size = sizeof(input_text);
    bitset<MAX_SIZE> input_bits;

    // conversion data to bits array
    convert_str_to_bitset(input_bits, input_text);

    /* DES algorithm */
    // add empty bits
    const size_t encrypt_size = 2 * str_size - 64 * ( str_size/64 );
    bitset<MAX_SIZE> encrypt_bits;
    // copy from input data
    for (int i = 0; i < encrypt_size; i++) {
        if (i < str_size) {
            encrypt_bits[i] = input_bits[i];
        } else {
            encrypt_bits[i] = 0;
        }
    }
    convert_bitset_to_str(input_text, encrypt_bits);
    cout << input_text;
    // initial permutation

    return 0;
}

void convert_bitset_to_str(string& str, const bitset<MAX_SIZE>& bit_str) {
    const size_t str_size = sizeof(bit_str);
    // conversion from bitset to string
    str = "";
    for (int i = 0; i < str_size; i+=8) {
        bitset<8> bit_char;
        int q = 0;
        for (int j = 7; j >=0; j--) {
            bit_char[q] = bit_str[i + j];
            q++;
        }
        str += char(bit_char.to_ulong());
    }
}

void convert_str_to_bitset(bitset<MAX_SIZE>& bit_str, const string& str) {
    // conversion from string to bitset
    for (int i = 0; i < str.length(); ++i) {
        char c = str[i];
        for (int j = 7; j >= 0 && c; --j) {
            if (c & 0x1) {
                bit_str.set(8 * i + j);
            }
            c >>= 1;
        }
    }
}

