struct DSU
{
private:
    int comp, mxSi;
    vector<int> par, siz, mxNo;
    vector<pair<int, int>> lst;

public:
    DSU(int n): par(n + 1), mxNo(n + 1), siz(n + 1, 1)
    {
        comp = n, mxSi = 0;
        iota(par.begin(), par.end(), 0);
        mxNo = par;
    }

    int getRoot(int u)
    {
        if (par[u] == u) { return u; }
        return par[u] = getRoot(par[u]);
    }

    void merge(int u, int v)
    {
        u = getRoot(u), v = getRoot(v);
        if (u == v) { return; }
        if (siz[u] > siz[v]) { swap(u, v); }
        lst.push_back({v, siz[u]});
        par[u] = v;
        siz[v] += siz[u];
        mxSi = max(mxSi, siz[v]);
        mxNo[v] = max(mxNo[v], mxNo[u]);
        comp--;
    }

    bool sameRoot(int u, int v) { return getRoot(u) == getRoot(v); }

    void rollBack()
    {
        auto [v, oldsz] = lst.back();
        lst.pop_back();
        int u = par[v];
        par[v] = v;
        siz[u] = oldsz;
    }
};
