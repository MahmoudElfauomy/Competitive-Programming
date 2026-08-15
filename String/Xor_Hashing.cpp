// check if the elemnt in ranges are equal and donot care about arrangement
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rand_ll(ll l, ll r)
{
    return uniform_int_distribution<ll>(l, r)(rng);
}

/*==============================================*/
//! XOR Hashing
struct xor_hashing
{
    ll val;

    xor_hashing(ll _val = 0)
    {
        val = _val;
    }

    xor_hashing operator ^ (const xor_hashing &tmp) const
    {
        return xor_hashing(val ^ tmp.val);
    }

    bool operator == (const xor_hashing &tmp) const
    {
        return val == tmp.val;
    }
};

map<ll, xor_hashing> mp;

/*==============================================*/
void Captain()
{
    ll n, q;
    cin >> n >> q;

    vector<xor_hashing> v(n + 1), vv(n + 1);

    for (int i = 1; i <= n; i++)
    {
        ll x;
        cin >> x;

        if (!mp.count(x))
            mp[x] = xor_hashing(rand_ll(1, (ll)4e18));

        v[i] = v[i - 1] ^ mp[x];
    }

    for (int i = 1; i <= n; i++)
    {
        ll x;
        cin >> x;

        if (!mp.count(x))
            mp[x] = xor_hashing(rand_ll(1, (ll)4e18));

        vv[i] = vv[i - 1] ^ mp[x];
    }

    while (q--)
    {
        ll l, r, L, R;
        cin >> l >> r >> L >> R;

        xor_hashing h1 = v[r] ^ v[l - 1];
        xor_hashing h2 = vv[R] ^ vv[L - 1];

        cout << (h1 == h2 ? "Yes\n" : "No\n");
    }
}