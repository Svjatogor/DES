#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <regex>
#include <algorithm>
#include <iterator>

#define MAX_SIZE 40000

using namespace std;

// indexes for initial permutation array
int init_permutation_array[64] =
        {
                58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
                61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
        };

// indexes for expansion function
int expansion_indexes[48] =
        {
                32, 1, 2, 3, 4, 5,
                4, 5, 6, 7, 8, 9,
                8, 9, 10, 11, 12, 13,
                12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21,
                20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29,
                28, 29, 30, 31, 32, 1
        };

// S transformation array
int s_transformation_arr[8][3][15] = {};

void convert_bitset_to_str(string& str, const bitset<MAX_SIZE>& bit_str);

void convert_str_to_bitset(bitset<MAX_SIZE>& bit_str, const string& str);

bitset<32> feistel_function(const bitset<32>&right_part, const bitset<48> key);

vector<string> split(const string& input, const string regex);

int main() {
    string input_text = "fuck";
    const size_t str_size = sizeof(input_text);
    bitset<MAX_SIZE> input_bits;
    // init s transformation array
    ifstream infile("s_transformation");
    if (!infile)
        std::cerr << "Could not open the file!" << std::endl;
    int i = 0;
    int j = 0;
    string line;
    std::vector<string> b_arr;
    string f, e;
    while (getline(infile, line)) {
        i++;
        b_arr = split(line, "\t");
        f = b_arr[0];
        e = b_arr[b_arr.size() - 1];
    }
    // conversion data to bits array
    convert_str_to_bitset(input_bits, input_text);

    /* DES algorithm */
    // add empty bits
    const size_t encrypt_size = 2 * str_size - 64 * (str_size / 64);
    bitset<MAX_SIZE> encrypt_bits;
    // copy from input data
    for (int i = 0; i < encrypt_size; i ++) {
        if (i < str_size) {
            encrypt_bits[i] = input_bits[i];
        } else {
            encrypt_bits[i] = 0;
        }
    }
    // initial permutation
    // make copy for job
    bitset<MAX_SIZE> origin_bits (encrypt_bits);
    for (int i = 0; i < encrypt_size; i++) {
        encrypt_bits[i] = origin_bits[init_permutation_array[i]];
    }
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

bitset<32> feistel_function(const bitset<32>&right_part, const bitset<48> key) {
    bitset<32> result_bits;
    // expansion function
    bitset<48> exapns_bits;
    for (int i = 0; i < 48; i++) {
        exapns_bits[i] = right_part[expansion_indexes[i]];
    }
    // XOR
    exapns_bits ^= key;

}

vector<std::string> split(const string& input, const string regex) {
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator
            first{input.begin(), input.end(), re, -1},
            last;
    return {first, last};
}


