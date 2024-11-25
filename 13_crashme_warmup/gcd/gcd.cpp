#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>

int Gcd(int a, int b) {
    while (a * b != 0) {
        auto rem = a % b;
        a = b;
        b = rem;
    }
    return std::max(a, b);
}

int TryRead(std::ifstream& in) {
    if (int x = 0; in >> x) {
        return x;
    }
    std::cout << "Fail on reading\n";
    std::exit(0);  // NOLINT(concurrency-mt-unsafe)
}

int main() {
    std::ifstream in("13_crashme_warmup/gcd/input.txt");
    if (!in) {
        std::cout << "Bad file path\n";
        std::exit(0);  // NOLINT(concurrency-mt-unsafe)
    }
    auto a = TryRead(in);
    auto b = TryRead(in);
    if ((a <= 0) || (b <= 0)) {
        std::cout << "Numbers should be positive\n";
        return 0;
    }

    auto gcd1 = Gcd(a, b);
    auto gcd2 = std::gcd(a, b);
    if (gcd1 != gcd2) {
        std::cout << "Shit happens\n";
        return 1;
    }
    std::cout << "Try again...\n";
}
