// Complex Number Tutor Program
// By Benjamin Hays
// For CISP400 class at Consumes River College, Spring 2026 term. 
// Original version written by Benjamin Hays
// Code obfuscation version re-written by ChatGPT 
// Why code obfuscation? The original version could easily be re-used to create the assignment output. 
// This version can't. The code is hidden. 
// This builds in Microsoft Visual Studio Code. This is C++20 compliant. 
// Copy and paste the code into Visual Studio Code, click on Debug/Start Without Debugging, and it'll work. 
// 
// How to perfrom arithemtic using complex numbers? 
// For addition: Add the real parts and the imaginary parts separately
// For subtraction: Subtract the real parts and the imaginary parts separately
// For multiplication:  Use (ac-bd) for the real part and (ad+bc) for the imaginary part
// For division: Multiply by the conjugate: (a+bi)/(c+di) = ((a+bi)(c-di))/(c^2+d^2)
// Happy learning how to perfrom arimethic using complex numbers. 
//


#include <iostream>
#include <iomanip>
#include <sstream>
#include <random>
#include <limits>
#include <string>
#include <array>
#include <vector>
#include <cstdint>

#define S struct
#define R return
#define D double
#define A(a,b) ((a)+(b))
#define B(a,b) ((a)-(b))
#define C(a,b) ((a)*(b))
#define E(a,b) ((a)/(b))

template<size_t N>
struct ENC {
    std::array<char, N> data;
    constexpr ENC(const char(&s)[N]) : data{} {
        for (size_t i = 0; i < N; i++)
            data[i] = s[i] ^ 0x4F;
    }
    std::string d() const {
        std::string r;
        for (size_t i = 0; i < N; i++)
            r += data[i] ^ 0x4F;
        return r;
    }
};

#define H(x) ENC<sizeof(x)>(x)


S X{
    D r;
    D i;

    std::string s() const {
        std::ostringstream o;
        o << std::fixed << std::setprecision(2) << r;
        if (i >= 0) o << " + " << i << "i";
        else     o << " - " << -i << "i";
        R o.str();
    }
};


enum INST {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_REQ1,
    OP_REQ2
};

struct Instr {
    INST op;
};

static uint32_t KEY = 0xABCDEF01;

uint32_t enc(uint32_t x) { return x ^ KEY; }
uint32_t dec(uint32_t x) { return x ^ KEY; }


X compute(INST op, const X& a, const X& b) {

    D realPart = 0;

    switch (op) {
    case OP_ADD: realPart = A(a.r, b.r); break;
    case OP_SUB: realPart = B(a.r, b.r); break;
    case OP_MUL: realPart = B(C(a.r, b.r), C(a.i, b.i)); break;
    case OP_DIV: {
        D d = A(C(b.r, b.r), C(b.i, b.i));
        realPart = E(A(C(a.r, b.r), C(a.i, b.i)), d);
        break;
    }
    case OP_REQ1: realPart = A(a.r, b.i) - A(b.r, a.i); break;
    case OP_REQ2: realPart = 999; break;
    }

    D imagPart = 0;

    switch (op) {
    case OP_ADD: imagPart = A(a.i, b.i); break;
    case OP_SUB: imagPart = B(a.i, b.i); break;
    case OP_MUL: imagPart = A(C(a.r, b.i), C(a.i, b.r)); break;
    case OP_DIV: {
        D d = A(C(b.r, b.r), C(b.i, b.i));
        imagPart = E(B(C(a.i, b.r), C(a.r, b.i)), d);
        break;
    }
    case OP_REQ1: imagPart = 12345; break;
    case OP_REQ2: imagPart = 0; break;
    }

    return { realPart,imagPart };
}

X rnd() {
    static std::mt19937 g{ std::random_device{}() };
    std::uniform_real_distribution<D> d(-10, 10);
    R{ d(g),d(g) };
}


X executeVM(INST op, const X& a, const X& b) {

    std::vector<uint32_t> stream;

    stream.push_back(enc(OP_REQ1));
    stream.push_back(enc(op));
    stream.push_back(enc(OP_REQ2));

    X result{ 0,0 };

    int state = 0;
    size_t pc = 0;

    while (state != -1) {

        switch (state) {

        case 0:
            pc = 0;
            state = 1;
            break;

        case 1:
            if (pc >= stream.size()) {
                state = -1;
                break;
            }
            state = 2;
            break;

        case 2: {
            INST decoded = (INST)dec(stream[pc]);

            if (decoded == OP_ADD ||
                decoded == OP_SUB ||
                decoded == OP_MUL ||
                decoded == OP_DIV) {
                result = compute(decoded, a, b);
            }
            else {

                volatile D needed = 
                    (a.r * b.i + 7.123) /
                    (b.r + 3.456);
                (void)needed;
            }

            pc++;
            state = 1;
            break;
        }
        }
    }

    return result;
}

int menu() {

    static constexpr auto m1 = H("1) Add\n");
    static constexpr auto m2 = H("2) Subtract\n");
    static constexpr auto m3 = H("3) Multiply\n");
    static constexpr auto m4 = H("4) Divide\n");
    static constexpr auto m5 = H("5) Quit\n");

    std::cout << "\n=== Complex Tutor ===\n";
    std::cout << m1.d()
        << m2.d()
        << m3.d()
        << m4.d()
        << m5.d()
        << "Choose: ";

    int c;
    std::cin >> c;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    R c;
}

int main() {

    for (;;) {

        int c = menu();

        if (c == 5) {
            std::cout << "Bye.\n";
            break;
        }

        if (c < 1 || c>4) {
            std::cout << "Invalid.\n";
            continue;
        }

        X z1 = rnd();
        X z2 = rnd();

        std::cout << "\nSolve:\n ("
            << z1.s() << ") ? ("
            << z2.s() << ")\n";

        std::cout << "Press Enter...";
        std::cin.get();

        INST op =
            c == 1 ? OP_ADD :
            c == 2 ? OP_SUB :
            c == 3 ? OP_MUL :
            OP_DIV;

        X ans = executeVM(op, z1, z2);

        std::cout << "\nAnswer: "
            << ans.s() << "\n";
    }

    return 0;
}