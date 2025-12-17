#include <iostream>
#include <string_view>


enum class SymbolClass: unsigned {
    Upper,
    Lower,
    Digit,
    Punct,
    Other
};

static void print(SymbolClass k) {
    switch (k) {
        case SymbolClass::Upper: std::cout << "Capital letter\n"; break;
        case SymbolClass::Lower: std::cout << "Line letter\n"; break;
        case SymbolClass::Digit: std::cout << "Digit\n"; break;
        case SymbolClass::Punct: std::cout << "Punctuation\n"; break;
        default:           std::cout << "Other symbol\n"; break;
    }
}

int main() {
    char ch;
    while (std::cin.get(ch)) {
        unsigned uc = static_cast<unsigned char>(ch);
        if (uc < 32 || uc > 127) {
            print(SymbolClass::Other);
            continue;
        }

        switch (ch) {

#if defined(__GNUC__) || defined(__clang__)
            case 'A' ... 'Z':
                print(SymbolClass::Upper);
                break;

            case 'a' ... 'z':
                print(SymbolClass::Lower);
                break;

            case '0' ... '9':
                print(SymbolClass::Digit);
                break;
#else
            // python-generated
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
            case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
            case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
            case 'V': case 'W': case 'X': case 'Y': case 'Z':
                print(SymbolClass::Upper);
                break;

            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
            case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
            case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
            case 'v': case 'w': case 'x': case 'y': case 'z':
                print(SymbolClass::Lower);
                break;

            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                print(SymbolClass::Digit);
                break;
#endif

            case '!': case '"': case '#': case '$': case '%': case '&': case '\'':
            case '(': case ')': case '*': case '+': case ',': case '-': case '.':
            case '/': case ':': case ';': case '<': case '=': case '>': case '?':
            case '@': case '[': case '\\': case ']': case '^': case '_': case '`':
            case '{': case '|': case '}': case '~':
                print(SymbolClass::Punct);
                break;

            [[unlikely]] default:
                print(SymbolClass::Other);
                break;
        }
    }

    return 0;
}
