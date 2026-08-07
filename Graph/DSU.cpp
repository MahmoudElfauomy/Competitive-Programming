class DSU
{
    vector<int> root;
    vector<int> sz;

public:
    DSU(int n)
    {
        root = vector<int>(n + 2);
        sz = vector<int>(n + 2, 1);
        for (int i = 0; i < n + 2; i++)
        {
            root[i] = i;
        }
    }
    int getroot(int n)
    {
        if (n == root[n])
            return n;
        return root[n] = getroot(root[n]);
    }
    bool is_fr(int u, int v)
    {
        return getroot(u) == getroot(v);
    }

    void make_fr(int u, int v)
    {
        u = getroot(u);
        v = getroot(v);
        if (u == v)
        {
            return;
        }
        root[u] = v;
        sz[v] += sz[u];
    }
};
