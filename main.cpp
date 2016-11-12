#include <iostream>
#include <string>
#include <bitset>
#define MAX_SIZE 40000

using namespace std;

int main() {
    string input_text = "fuck";
    const size_t str_size = sizeof(input_text);
    bitset<str_size> input_bits;

    // conversion from string to bitset
    for (int i = 0; i < input_text.length(); ++i) {
        char c = input_text[i];
        for (int j = 7; j >= 0 && c; --j) {
            if (c & 0x1) {
                input_bits.set(8 * i + j);
            }
            c >>= 1;
        }
    }

    // conversion from bitset to string
    string out_str = "";
    for (int i = 0; i < str_size; i+=8) {
        bitset<8> bit_char;
        int q = 0;
        for (int j = 7; j >=0; j--) {
            bit_char[q] = input_bits[i + j];
            q++;
        }
        out_str += char(bit_char.to_ulong());
    }
    cout << out_str;

    /* DES algorithm */
    // add empty bits
    const size_t encrypt_size = 2 * str_size - 64 * ( str_size/64 );
    bitset<encrypt_size> encrypt_bits;
    // copy from input data
    for (int i = 0; i < encrypt_size; i++) {
        if (i < str_size) {
            encrypt_bits[i] = input_bits[i];
        } else {
            encrypt_bits[i] = 0;
        }
    }
    // initial permutation

    return 0;
}
