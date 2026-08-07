vector<ll> fact, inverse;
ll fpower(ll ab, ll ba)
{
    if (!ba)
        return 1;
    ll p = fpower(ab, ba / 2);
    ll ans = (p * p) % mod;
    if (ba & 1)
        ans *= ab % mod;
    return ans % mod;
}

ll add(ll n, ll r)
{
    return ((n % mod) + (r % mod)) % mod;
}

ll sub(ll n, ll r)
{
    return ((n % mod) - (r % mod) + mod) % mod;
}

ll mul(ll n, ll r)
{
    return (n % mod) * (r % mod) % mod;
}

ll inv(ll n)
{
    return fpower(n, mod - 2) % mod;
}

ll divi(ll n, ll r)
{
    return (n % mod * inv(r)) % mod;
}

ll npr(ll n, ll r)
{
    return fact[n] * inverse[n - r] % mod;
}

ll ncr(ll n, ll r)
{
    return fact[n] * (inverse[n - r] % mod * inverse[r] % mod) % mod;
}

void pre()
{
    fact = vector<ll>(N);
    inverse = vector<ll>(N);
    fact[0] = 1;
    for (ll i = 1; i < N; i++)
        fact[i] = fact[i - 1] * i % mod;
    inverse[N - 1] = inv(fact[N - 1]);
    for (ll i = N - 2; i > -1; i--)
        inverse[i] = inverse[i + 1] * (i + 1) % mod;
}
