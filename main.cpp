#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
    string input_text = "lol";
    const size_t str_size = sizeof(input_text); // размер строки
    bitset<str_size> out_bits;

    // конвертирование строки в массив битов
    for (int i = 0; i < input_text.length(); ++i) {
        char c = input_text[i];
        for (int j = 7; j >= 0 && c; --j) {
            if (c & 0x1) {
                out_bits.set(8 * i + j);
            }
            c >>= 1;
        }
    }

    string out_str = "";
    // конвертирование массива битов в строку
    for (int i = str_size; i >= 0; i-=8) {
        bitset<8> bit_char;
        int q = 0;
        for (int j = 7; j >=0; j--) {
            bit_char[q] = out_bits[i + j];
            q++;
        }
        out_str += char(bit_char.to_ulong());
    }
    cout << out_str;

    // 
    return 0;
}
