// O(N^0.25)
using u64 = unsigned long long ;

mt19937_64 rng(1337) ;

u64 mul_mod(u64 a, u64 b, u64 m) {
    return (u64)((__int128)a * b % m) ;
}

u64 power_1e18(u64 base, u64 exp, u64 mod) {
    u64 res = 1 ;
    base %= mod ;
    while (exp > 0) {
        if (exp % 2 == 1) res = mul_mod(res, base, mod) ;
        base = mul_mod(base, base, mod) ;
        exp /= 2 ;
    }
    return res ;
}

bool isPrime_1e18(u64 n) {
    if (n < 2) return false ;
    if (n == 2 || n == 3) return true ;
    if (n % 2 == 0 || n % 3 == 0) return false ;

    int k = 0 ;
    u64 d = n - 1 ;
    while ((d & 1) == 0) {
        d >>= 1 ;
        k++ ;
    }

    static const u64 bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37} ;
    for (u64 a : bases) {
        if (n <= a) break ;
        u64 x = power_1e18(a, d, n) ;
        if (x == 1 || x == n - 1) continue ;
        bool composite = true ;
        for (int r = 1 ; r < k ; r++) {
            x = mul_mod(x, x, n) ;
            if (x == n - 1) {
                composite = false ;
                break ;
            }
        }
        if (composite) return false ;
    }
    return true ;
}

u64 pollard_rho(u64 n) {
    if (n % 2 == 0) return 2 ;
    if (isPrime_1e18(n)) return n ;

    u64 x = 2, y = 2, d = 1, c = 1 ;
    auto f = [&](u64 x, u64 n, u64 c) {
        return (mul_mod(x, x, n) + c) % n ;
    } ;

    while (d == 1) {
        x = f(x, n, c) ;
        y = f(f(y, n, c), n, c) ;
        u64 diff = (x > y) ? (x - y) : (y - x) ;
        d = std::gcd(diff, n) ;
        if (d == n) {
            x = rng() % (n - 2) + 2 ;
            y = x ;
            c = rng() % (n - 1) + 1 ;
            d = 1 ;
        }
    }
    return d ;
}

void get_factors_helper(u64 n, vector<u64>& factors) {
    if (n == 1) return ;
    if (isPrime_1e18(n)) {
        factors.push_back(n) ;
        return ;
    }
    u64 divisor = pollard_rho(n) ;
    get_factors_helper(divisor, factors) ;
    get_factors_helper(n / divisor, factors) ;
}

vector<u64> prime_factors_1e18(u64 n) {
    vector<u64> factors ;
    get_factors_helper(n, factors) ;
    sort(factors.begin(), factors.end()) ;
    return factors ;
}
/*==============================================*/
void Captain()
{
    u64 n = 1e17 ;
    vector < u64 > v = prime_factors_1e18(n) ;

    for ( auto it : v ) 
    cout << it << ' ' ;
}
