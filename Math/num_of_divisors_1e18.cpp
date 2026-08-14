// O(N^0.25)
typedef unsigned long long ull;

ull mult_mod(ull a, ull b, ull mod) {
    return (ull)((__int128)a * b % mod);
}

ull power(ull base, ull exp, ull mod) {
    ull res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = mult_mod(res, base, mod);
        base = mult_mod(base, base, mod);
        exp /= 2;
    }
    return res;
}

bool is_prime(ull n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    ull d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    static const ull bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ull a : bases) {
        if (n <= a) break;
        ull x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mult_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

ull pollard_rho(ull n) {
    if (n % 2 == 0) return 2;
    ull x = 2, y = 2, d = 1, c = 1;
    auto f = [&](ull x, ull c, ull n) {
        return (mult_mod(x, x, n) + c) % n;
    };
    while (d == 1) {
        x = f(x, c, n);
        y = f(f(y, c, n), c, n);
        ull diff = (x > y) ? (x - y) : (y - x);
        d = std::gcd(diff, n);
        if (d == n) {
            x = (rand() % (n - 2)) + 2;
            y = x;
            c = (rand() % (n - 1)) + 1;
            d = 1;
        }
    }
    return d;
}

void get_factors(ull n, map<ull, int>& factor_counts) {
    if (n == 1) return;

    static const int small_primes[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    for (int p : small_primes) {
        if (n % p == 0) {
            while (n % p == 0) {
                factor_counts[p]++;
                n /= p;
            }
        }
    }
    if (n == 1) return;

    if (is_prime(n)) {
        factor_counts[n]++;
        return;
    }

    ull divisor = pollard_rho(n);
    get_factors(divisor, factor_counts);
    get_factors(n / divisor, factor_counts);
}

ull numberOfDivisors(ull n) {
    if (n == 0) return 0;
    map<ull, int> factor_counts;
    get_factors(n, factor_counts);

    ull total_divisors = 1;
    for (auto const& [prime, count] : factor_counts) {
        total_divisors *= (count + 1);
    }
    return total_divisors;
}
/*==============================================*/
void Captain()
{
    cout << numberOfDivisors(12) << endl;                   // أرقام صغيرة جداً -> 6
    cout << numberOfDivisors(1000000) << endl;              // أرقام متوسطة -> 49
    cout << numberOfDivisors(1000000007) << endl;           // أعداد أولية -> 2
    cout << numberOfDivisors(1000000008) << endl;           // أعداد أولية -> 144
    cout << numberOfDivisors(999999999999999989ULL) << endl; // أرقام ضخمة جداً في أقل من 1ms
}
