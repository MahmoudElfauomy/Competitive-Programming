
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

/*
============================================================
                 ARITHMETIC SEQUENCE (AP)
============================================================

AP:
a, a+d, a+2d, a+3d, ...

a  = first term
d  = common difference
n  = number of terms
*/

// ----------------------------------------------------------
// 1. Find the nth term
// a_n = a + (n-1) * d
// ----------------------------------------------------------
ll AP_nth(ll a, ll d, ll n) {
    return a + (n - 1) * d;
}


// ----------------------------------------------------------
// 2. Find common difference from two consecutive terms
// d = a[i+1] - a[i]
// ----------------------------------------------------------
ll AP_difference(ll x, ll y) {
    return y - x;
}


// ----------------------------------------------------------
// 3. Find common difference from two arbitrary terms
//
// a_i = a + (i-1)d
// a_j = a + (j-1)d
//
// d = (a_j - a_i) / (j-i)
// ----------------------------------------------------------
ll AP_difference_from_two_terms(ll ai, ll aj, ll i, ll j) {
    return (aj - ai) / (j - i);
}


// ----------------------------------------------------------
// 4. Find first term
//
// a_n = a + (n-1)d
// a = a_n - (n-1)d
// ----------------------------------------------------------
ll AP_first_term(ll an, ll d, ll n) {
    return an - (n - 1) * d;
}


// ----------------------------------------------------------
// 5. Sum of first n terms
//
// S_n = n/2 * [2a + (n-1)d]
// ----------------------------------------------------------
i128 AP_sum128(ll a, ll d, ll n) {
    return (i128)n * (2 * (i128)a + (i128)(n - 1) * d) / 2;
}

ll AP_sum(ll a, ll d, ll n) {
    return (ll)AP_sum128(a, d, n);
}


// ----------------------------------------------------------
// 6. Sum using first and last term
//
// S = n/2 * (first + last)
// ----------------------------------------------------------
i128 AP_sum_first_last128(ll first, ll last, ll n) {
    return (i128)n * ((i128)first + last) / 2;
}

ll AP_sum_first_last(ll first, ll last, ll n) {
    return (ll)AP_sum_first_last128(first, last, n);
}


// ----------------------------------------------------------
// 7. Find number of terms
//
// last = first + (n-1)d
//
// n = (last-first)/d + 1
// ----------------------------------------------------------
ll AP_number_of_terms(ll first, ll last, ll d) {
    return (last - first) / d + 1;
}


// ----------------------------------------------------------
// 8. Sum from position l to r
//
// number of terms = r-l+1
// sum = count * (a_l + a_r) / 2
// ----------------------------------------------------------
i128 AP_range_sum128(ll al, ll ar, ll l, ll r) {
    ll cnt = r - l + 1;
    return (i128)cnt * ((i128)al + ar) / 2;
}

ll AP_range_sum(ll al, ll ar, ll l, ll r) {
    return (ll)AP_range_sum128(al, ar, l, r);
}


// ----------------------------------------------------------
// 9. Sum of consecutive integers [l, r]
//
// l + (l+1) + ... + r
// ----------------------------------------------------------
i128 sum_consecutive128(ll l, ll r) {
    ll cnt = r - l + 1;
    return (i128)cnt * ((i128)l + r) / 2;
}

ll sum_consecutive(ll l, ll r) {
    return (ll)sum_consecutive128(l, r);
}


// ----------------------------------------------------------
// 10. Check if 3 numbers form an AP
//
// b-a = c-b
// equivalent to:
// 2*b = a+c
// ----------------------------------------------------------
bool isAP3(ll a, ll b, ll c) {
    return (i128)2 * b == (i128)a + c;
}


// ----------------------------------------------------------
// 11. Find missing middle AP term
//
// a, x, c
//
// x = (a+c)/2
// ----------------------------------------------------------
ll AP_middle(ll a, ll c) {
    return (a + c) / 2;
}


// ----------------------------------------------------------
// 12. Check if x belongs to AP
//
// a, a+d, a+2d, ...
// ----------------------------------------------------------
bool belongsToAP(ll a, ll d, ll x) {

    if (d == 0)
        return x == a;

    // d > 0
    if (d > 0) {
        if (x < a)
            return false;

        return (x - a) % d == 0;
    }

    // d < 0
    if (x > a)
        return false;

    return (a - x) % (-d) == 0;
}


// ----------------------------------------------------------
// 13. Get index of x in AP
//
// x = a + (n-1)d
//
// n = (x-a)/d + 1
// ----------------------------------------------------------
ll AP_index(ll a, ll d, ll x) {
    return (x - a) / d + 1;
}


// ----------------------------------------------------------
// 14. Insert k arithmetic means between A and B
//
// Total gaps = k+1
// d = (B-A)/(k+1)
// ----------------------------------------------------------
vector<ll> insertArithmeticMeans(ll A, ll B, ll k) {

    ll d = (B - A) / (k + 1);

    vector<ll> ans;

    for (ll i = 0; i <= k + 1; i++) {
        ans.push_back(A + i * d);
    }

    return ans;
}


// ----------------------------------------------------------
// 15. AP from first term and difference
// ----------------------------------------------------------
vector<ll> buildAP(ll a, ll d, ll n) {

    vector<ll> ans(n);

    for (ll i = 0; i < n; i++) {
        ans[i] = a + i * d;
    }

    return ans;
}


/*
============================================================
                 GEOMETRIC SEQUENCE (GP)
============================================================

GP:
a, ar, ar², ar³, ...

a = first term
r = common ratio
n = number of terms
*/


// ----------------------------------------------------------
// 16. Fast power without modulo
//
// Use only when result fits in integer type.
// ----------------------------------------------------------
i128 power128(ll a, ll n) {

    i128 result = 1;
    i128 base = a;

    while (n > 0) {

        if (n & 1)
            result *= base;

        base *= base;
        n >>= 1;
    }

    return result;
}


// ----------------------------------------------------------
// 17. nth term of GP
//
// a_n = a * r^(n-1)
// ----------------------------------------------------------
i128 GP_nth128(ll a, ll r, ll n) {
    return (i128)a * power128(r, n - 1);
}

ll GP_nth(ll a, ll r, ll n) {
    return (ll)GP_nth128(a, r, n);
}


// ----------------------------------------------------------
// 18. Find ratio from consecutive terms
//
// r = b/a
//
// For integer ratio, divisible is expected.
// ----------------------------------------------------------
ll GP_ratio(ll a, ll b) {
    return b / a;
}


// ----------------------------------------------------------
// 19. Check if 3 numbers form a GP
//
// b/a = c/b
//
// Avoid division:
//
// b² = ac
// ----------------------------------------------------------
bool isGP3(ll a, ll b, ll c) {
    return (i128)b * b == (i128)a * c;
}


// ----------------------------------------------------------
// 20. Find middle GP term
//
// b² = ac
//
// For positive values:
// b = sqrt(a*c)
//
// Integer version:
// ----------------------------------------------------------
ll GP_middle(ll a, ll c) {
    return sqrtl((long double)a * c);
}


// ----------------------------------------------------------
// 21. Finite GP sum
//
// S_n = a * (r^n - 1)/(r-1)
//
// Special case:
// r = 1 => n*a
// ----------------------------------------------------------
i128 GP_sum128(ll a, ll r, ll n) {

    if (n == 0)
        return 0;

    if (r == 1)
        return (i128)a * n;

    i128 rn = power128(r, n);

    return (i128)a * (rn - 1) / (r - 1);
}

ll GP_sum(ll a, ll r, ll n) {
    return (ll)GP_sum128(a, r, n);
}


// ----------------------------------------------------------
// 22. Product of first n GP terms
//
// a * ar * ar² * ... * ar^(n-1)
//
// = a^n * r^(n(n-1)/2)
// ----------------------------------------------------------
i128 GP_product128(ll a, ll r, ll n) {

    i128 part1 = power128(a, n);

    i128 exponent = (i128)n * (n - 1) / 2;

    // exponent can be larger than ll
    // This simple helper assumes exponent fits reasonably.
    i128 result = 1;
    i128 base = r;

    while (exponent > 0) {

        if (exponent & 1)
            result *= base;

        base *= base;
        exponent >>= 1;
    }

    return part1 * result;
}


// ----------------------------------------------------------
// 23. Infinite GP sum
//
// S = a/(1-r)
//
// Valid only when |r| < 1
//
// This version uses long double.
// ----------------------------------------------------------
long double GP_infinite_sum(long double a, long double r) {

    if (fabsl(r) >= 1.0L) {
        throw runtime_error("Infinite GP does not converge.");
    }

    return a / (1.0L - r);
}


// ----------------------------------------------------------
// 24. Build GP
//
// a, ar, ar², ...
//
// Integer version.
// ----------------------------------------------------------
vector<ll> buildGP(ll a, ll r, ll n) {

    vector<ll> ans;

    ll current = a;

    for (ll i = 0; i < n; i++) {

        ans.push_back(current);

        current *= r;
    }

    return ans;
}


// ----------------------------------------------------------
// 25. Insert k geometric means
//
// A, ?, ?, B
//
// A * r^(k+1) = B
//
// r = root(k+1, B/A)
//
// Floating-point version.
// ----------------------------------------------------------
long double GP_ratio_insert(
    long double A,
    long double B,
    ll k
) {
    return powl(B / A, 1.0L / (k + 1));
}


// ----------------------------------------------------------
// 26. Insert geometric means
//
// Floating-point version.
// ----------------------------------------------------------
vector<long double> insertGeometricMeans(
    long double A,
    long double B,
    ll k
) {

    long double r =
        powl(B / A, 1.0L / (k + 1));

    vector<long double> ans;

    long double current = A;

    for (ll i = 0; i <= k + 1; i++) {

        ans.push_back(current);

        current *= r;
    }

    return ans;
}


/*
============================================================
                  MODULAR ARITHMETIC
============================================================
*/


// ----------------------------------------------------------
// 27. Fast power modulo
//
// a^n % MOD
// O(log n)
// ----------------------------------------------------------
ll modPow(ll a, ll n, ll MOD) {

    a %= MOD;

    ll result = 1 % MOD;

    while (n > 0) {

        if (n & 1)
            result = (i128)result * a % MOD;

        a = (i128)a * a % MOD;

        n >>= 1;
    }

    return result;
}


// ----------------------------------------------------------
// 28. Modular inverse
//
// Works when gcd(a, MOD) = 1.
// Usually used when MOD is prime.
//
// a^(-1) = a^(MOD-2) mod MOD
// ----------------------------------------------------------
ll modInversePrime(ll a, ll MOD) {

    return modPow(a, MOD - 2, MOD);
}


// ----------------------------------------------------------
// 29. AP sum modulo MOD
//
// S = n/2 * (2a+(n-1)d)
//
// IMPORTANT:
// We divide by 2 safely by making one factor even
// BEFORE taking modulo.
// ----------------------------------------------------------
ll AP_sum_mod(
    ll a,
    ll d,
    ll n,
    ll MOD
) {

    ll x = n;
    ll y =
        (2 % MOD +
         ((n - 1) % MOD) * (d % MOD)) % MOD;

    // We need to divide the original product by 2.
    // Better to divide n or the bracket before modulo.

    ll N = n;
    ll D = 2 * a + (n - 1) * d;

    if (N % 2 == 0)
        N /= 2;
    else
        D /= 2;

    N %= MOD;
    D %= MOD;

    return (i128)N * D % MOD;
}


// ----------------------------------------------------------
// 30. GP sum modulo MOD
//
// S = a * (r^n - 1)/(r-1)
//
// Requires inverse of (r-1) modulo MOD.
//
// Only valid when gcd(r-1, MOD) = 1.
// ----------------------------------------------------------
ll GP_sum_mod(
    ll a,
    ll r,
    ll n,
    ll MOD
) {

    if (n == 0)
        return 0;

    if (r % MOD == 1) {
        return (i128)(a % MOD) * (n % MOD) % MOD;
    }

    ll numerator =
        (modPow(r, n, MOD) - 1 + MOD) % MOD;

    ll denominator =
        (r - 1 + MOD) % MOD;

    ll inverse =
        modInversePrime(denominator, MOD);

    return (i128)(a % MOD)
        * numerator % MOD
        * inverse % MOD;
}


/*
============================================================
                     PREFIX SUM AP
============================================================
*/


// ----------------------------------------------------------
// 31. AP prefix sum
//
// a_i = a + (i-1)d
//
// prefix(n) = sum of first n terms
// ----------------------------------------------------------
i128 AP_prefix128(ll a, ll d, ll n) {

    return (i128)n *
        (2 * (i128)a + (i128)(n - 1) * d) / 2;
}


// ----------------------------------------------------------
// 32. AP range sum using prefix sums
// ----------------------------------------------------------
i128 AP_range_by_prefix128(
    ll a,
    ll d,
    ll l,
    ll r
) {

    return AP_prefix128(a, d, r)
        - AP_prefix128(a, d, l - 1);
}


/*
============================================================
                 CHECKING ARRAYS
============================================================
*/


// ----------------------------------------------------------
// 33. Check whether an entire array is AP
// ----------------------------------------------------------
bool isArrayAP(const vector<ll>& a) {

    int n = a.size();

    if (n <= 2)
        return true;

    ll d = a[1] - a[0];

    for (int i = 2; i < n; i++) {

        if ((i128)a[i] - a[i - 1] != d)
            return false;
    }

    return true;
}


// ----------------------------------------------------------
// 34. Check whether an entire array is GP
//
// Uses multiplication instead of division.
//
// a[i] / a[i-1] = constant
//
// => a[i]^2 = a[i-1] * a[i+1]
//
// This works for normal non-pathological cases.
// ----------------------------------------------------------
bool isArrayGP(const vector<ll>& a) {

    int n = a.size();

    if (n <= 2)
        return true;

    // Handle a[0] == 0 separately.
    if (a[0] == 0) {

        for (ll x : a) {
            if (x != 0)
                return false;
        }

        return true;
    }

    for (int i = 1; i + 1 < n; i++) {

        if ((i128)a[i] * a[i]
            != (i128)a[i - 1] * a[i + 1]) {

            return false;
        }
    }

    return true;
}


/*
============================================================
          AP / GP SPECIAL IDENTITIES
============================================================
*/


// ----------------------------------------------------------
// 35. Arithmetic mean
// ----------------------------------------------------------
long double arithmeticMean(long double a, long double b) {
    return (a + b) / 2.0L;
}


// ----------------------------------------------------------
// 36. Geometric mean
// ----------------------------------------------------------
long double geometricMean(long double a, long double b) {
    return sqrtl(a * b);
}


// ----------------------------------------------------------
// 37. AP middle term using indices
//
// If i+j = 2*k:
//
// a_i + a_j = 2*a_k
// ----------------------------------------------------------
ll AP_middle_index(
    ll ai,
    ll aj
) {
    return (ai + aj) / 2;
}


// ----------------------------------------------------------
// 38. GP middle term using values
//
// b² = ac
// ----------------------------------------------------------
long double GP_middle_value(
    long double a,
    long double c
) {
    return sqrtl(a * c);
}


/*
============================================================
                   EXAMPLES
============================================================
*/

int main() {

    // ------------------------------------------------------
    // AP examples
    // ------------------------------------------------------

    ll a = 3;
    ll d = 5;

    cout << "AP 10th term = "
        << AP_nth(a, d, 10) << '\n';

    cout << "AP sum first 10 = "
        << AP_sum(a, d, 10) << '\n';

    cout << "AP difference = "
        << AP_difference(3, 8) << '\n';

    cout << "Is 3,8,13 AP? "
        << isAP3(3, 8, 13) << '\n';


    // ------------------------------------------------------
    // GP examples
    // ------------------------------------------------------

    ll ga = 2;
    ll r = 3;

    cout << "GP 5th term = "
        << GP_nth(ga, r, 5) << '\n';

    cout << "GP sum first 5 = "
        << GP_sum(ga, r, 5) << '\n';

    cout << "Is 2,6,18 GP? "
        << isGP3(2, 6, 18) << '\n';


    // ------------------------------------------------------
    // Consecutive sum
    // ------------------------------------------------------

    cout << "Sum [1,100] = "
        << sum_consecutive(1, 100) << '\n';


    // ------------------------------------------------------
    // Modular GP
    // ------------------------------------------------------

    const ll MOD = 998244353;

    cout << "1 + 2 + ... + 2^100 mod MOD = "
        << GP_sum_mod(1, 2, 101, MOD)
        << '\n';


    // ------------------------------------------------------
    // Check an entire array
    // ------------------------------------------------------

    vector<ll> ap = {
        2, 5, 8, 11, 14
    };

    vector<ll> gp = {
        2, 6, 18, 54, 162
    };

    cout << "Array is AP? "
        << isArrayAP(ap) << '\n';

    cout << "Array is GP? "
        << isArrayGP(gp) << '\n';


    // ------------------------------------------------------
    // Infinite GP
    // ------------------------------------------------------

    cout << fixed << setprecision(10);

    cout << "Infinite GP sum = "
        << (double)GP_infinite_sum(1.0L, 0.5L)
        << '\n';


    return 0;
}
