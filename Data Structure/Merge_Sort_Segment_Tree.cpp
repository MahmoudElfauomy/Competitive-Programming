class segment_tree_merge_sort
{
private:
    struct node
    {
        vector<int> vec;
        void apply(int lx, int rx, int val)
        {
            vec = {val};
        }

        void merge(node a, node b)
        {
            auto &A = a.vec;
            auto &B = b.vec;
            int i = 0, j = 0;
            while (i < A.size() && j < B.size())
            {
                if (A[i] <= B[j])
                {
                    vec.push_back(A[i++]);
                }
                else
                {
                    vec.push_back(B[j++]);
                }
            }
            vec.insert(vec.end(), A.begin() + i, A.end());
            vec.insert(vec.end(), B.begin() + j, B.end());
        }
    };

    int size = 1;
    vector<node> seg;

    void build(int x, int lx, int rx, vector<int> &v)
    {
        if (lx == rx)
        {
            if (lx < (int)v.size())
            {
                seg[x].apply(lx, rx, v[lx]);
            }
            return;
        }
        int mid = (rx + lx) / 2;
        int left = 2 * x + 1;
        int right = 2 * x + 2;
        build(left, lx, mid, v);
        build(right, mid + 1, rx, v);
        seg[x].merge(seg[left], seg[right]);
    }

    int query(int x, int lx, int rx, int l, int r, int a, int b)
    {
        if (l <= lx && rx <= r)
        {
            auto &v = seg[x].vec;
            return upper_bound(v.begin(), v.end(), b) - lower_bound(v.begin(), v.end(), a);
        }
        if (lx > r || l > rx)
        {
            return 0;
        }
        int mid = (rx + lx) / 2;
        int left = 2 * x + 1;
        int right = 2 * x + 2;
        return query(left, lx, mid, l, r, a, b) + query(right, mid + 1, rx, l, r, a, b);
    }

public:
    segment_tree_merge_sort(vector<int> &v)
    {
        while (size < (int)v.size())
        {
            size *= 2;
        }
        seg.assign(2 * size, node());
        build(0, 0, size - 1, v);
    }

    int query(int l, int r, int x, int y)
    {
        return query(0, 0, size - 1, l, r, x, y);
    }
};
