struct BIT
{
private:
    int n;
    vector<ll> B1, B2;
    void add(vector<ll> &b, int idx, ll x)
    {
        ++idx;
        while (idx <= n)
        {
            b[idx] += x;
            idx += idx & -idx;
        }
    }
    ll sum(vector<ll> &b, int idx)
    {
        idx++;
        ll total = 0;
        while (idx > 0)
        {
            total += b[idx];
            idx -= idx & -idx;
        }
        return total;
    }
    ll prefix(ll idx)
    {
        return sum(B1, idx) * idx - sum(B2, idx);
    }

public:
    BIT(int n) : n(n)
    {
        B1.assign(n + 1, {});
        B2.assign(n + 1, {});
    }
    void update(int l, int r, ll x)
    {
        add(B1, l, x);
        add(B1, r + 1, -x);
        add(B2, l, x * (l - 1));
        add(B2, r + 1, -x * r);
    }
    ll query(int i)
    {
        return prefix(i) - prefix(i - 1);
    }
    ll query(int l, int r)
    {
        return prefix(r) - prefix(l - 1);
    }
};
