const int base1 = 37, base2 = 41, m1 = 1e9 + 7, m2 = 2e9 + 11;
int pw1[N], pw2[N];
int check_mod(ll x, ll m)
{
    if (x >= m)
        x -= m;
    return x;
}
void lets_hash()
{
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i < N; i++)
    {
        pw1[i] = (1ll * pw1[i - 1] * base1) % m1;
        pw2[i] = (1ll * pw2[i - 1] * base2) % m2;
    }
}

class Segment_Tree
{
    struct node
    {
        int pre = 0, suf = 0, len = 0;
    };

    int size = 1;
    vector<node> seg;
    node merg(node a, node b)
    {
        node ret;
        ret.pre = check_mod((1ll * a.pre * pw1[b.len]) % m1 + b.pre, m1);
        ret.suf = check_mod((1ll * b.suf * pw1[a.len]) % m1 + a.suf, m1);
        ret.len = a.len + b.len;
        return ret;
    }
    void build(int x, int lx, int rx, string &v)
    {
        if (lx == rx)
        {
            if (lx < v.size())
                seg[x].pre = v[lx] - 'a' + 1, seg[x].suf = v[lx] - 'a' + 1, seg[x].len = 1;
            return;
        }
        int mid = (lx + rx) / 2;
        int left = x * 2 + 1;
        int right = x * 2 + 2;

        build(left, lx, mid, v);
        build(right, mid + 1, rx, v);
        seg[x] = merg(seg[left], seg[right]);
    }
    void update(int x, int lx, int rx, int idx, char val)
    {
        if (lx == rx)
        {
            seg[x].pre = val - 'a' + 1, seg[x].suf = val - 'a' + 1;
            return;
        }
        int mid = (lx + rx) / 2;
        int left = x * 2 + 1;
        int right = x * 2 + 2;
        if (idx <= mid)
        {
            update(left, lx, mid, idx, val);
        }
        else
        {
            update(right, mid + 1, rx, idx, val);
        }
        seg[x] = merg(seg[left], seg[right]);
    }
    node query(int x, int lx, int rx, int l, int r)
    {
        if (l <= lx && rx <= r)
            return seg[x];
        if (rx < l || r < lx)
            return node();
        int mid = (lx + rx) / 2;
        int left = x * 2 + 1;
        int right = x * 2 + 2;
        node LEFT = query(left, lx, mid, l, r);
        node RIGHT = query(right, mid + 1, rx, l, r);

        return merg(LEFT, RIGHT);
    }

public:
    Segment_Tree(string &v)
    {
        while (size < v.size())
            size <<= 1;
        seg.assign((size << 1), node());
        build(0, 0, size - 1, v);
    }
    void update(int idx, int val)
    {
        update(0, 0, size - 1, idx, val);
    }
    node query(int l, int r)
    {
        return query(0, 0, size - 1, l, r);
    }
};
