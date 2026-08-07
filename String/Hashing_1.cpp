class HASH
{
private:
    static const int64_t mod = (1LL << 61) - 1;
    static int64_t base;
    vector<int64_t> pow{1}, hash{0};

    int64_t sub(int64_t a, int64_t b)
    {
        a -= b;
        if (a < 0)
            a += mod;
        return a;
    }

public:
    HASH(const auto &a)
    {
        for (int i = 0; i < a.size(); i++)
        {
            pow.push_back((__int128_t)pow[i] * base % mod);
            hash.push_back(((__int128_t)hash[i] * base + a[i]) % mod);
        }
    }

    int64_t substr(int l, int r)
    {
        return sub(hash[r + 1], (__int128_t)hash[l] * pow[r - l + 1] % mod);
    }

    int64_t merge(int64_t h1, int64_t h2, int len2)
    {
        return ((__int128_t)h1 * pow[len2] + h2) % mod;
    }
};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int64_t HASH::base = (mod >> 2) + rng() % (mod >> 1);
