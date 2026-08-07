
class Segment_Tree
{
    struct node
    {
    };

    int size = 1;
    vector<node> seg;
    node merg(node a, node b)
    {
    }
    void build(int x, int lx, int rx, vector<int> &v)
    {
        if (lx == rx)
        {

            return;
        }
        int mid = (lx + rx) / 2;
        int left = x * 2 + 1;
        int right = x * 2 + 2;

        build(left, lx, mid, v);
        build(right, mid + 1, rx, v);
        seg[x] = merg(seg[left], seg[right]);
    }
    void update(int x, int lx, int rx, int idx, int val)
    {
        if (lx == rx)
        {

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
    Segment_Tree(vector<int> &v)
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
