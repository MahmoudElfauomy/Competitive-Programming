class Sparse_table
{
    vector<vector<int>> sp;
    int sz, n;
    void build()
    {
        for (int i = 1; i <= sz; i++)
        {
            for (int j = 0; j + (1 << (i)) - 1 < n; j++)
            {
                sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

public:
    Sparse_table(vector<int> &v)
    {
        n = v.size();
        sz = __lg(n);
        sp = vector<vector<int>>(sz + 1, vector<int>(n));
        for (int i = 0; i < n; i++)
            sp[0][i] = v[i];
        build();
    }
    int query(int l, int r)
    {
        int n = __lg(r - l + 1);
        return min(sp[n][l], sp[n][r - (1 << n) + 1]);
    }
};
