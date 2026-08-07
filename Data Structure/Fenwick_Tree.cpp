
class Fenwick_Tree
{

    vector<ll> rg;

public:
    int size;
    Fenwick_Tree(int n)
    {
        size = n;
        rg.resize(n + 2);
    }
    ll query(int k)
    {
        ll ret = 0;
        while (k)
        {
            ret += rg[k];
            k -= (k & -k);
        }
        return ret;
    }
    void update(int k, ll val)
    {
        while (k <= size)
        {
            rg[k] += val;
            k += (k & -k);
        }
    }
    ll query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};
