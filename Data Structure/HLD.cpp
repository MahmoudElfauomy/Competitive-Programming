struct HLD
{
    vector<int> sub_sz, heavy, par, dep, id, head;
    int timer = 0;
    HLD(int n, vector<vector<int>> &ad)
    {
        sub_sz = vector<int>(n + 1);
        head = vector<int>(n + 1);
        heavy = vector<int>(n + 1);
        id = vector<int>(n + 1);
        par = vector<int>(n + 1);
        dep = vector<int>(n + 1);

        pre(1, 0, ad);
        head[1] = 1;
        flat(1, 0, ad);
    }

    void pre(int u, int p, const vector<vector<int>> &ad)
    {
        sub_sz[u] = 1;
        int mx = 0;
        for (auto v : ad[u])
        {
            if (v == p)
                continue;
            dep[v] = dep[u] + 1;
            pre(v, u, ad);
            par[v] = u;
            sub_sz[u] += sub_sz[v];
            if (sub_sz[mx] < sub_sz[v])
            {
                mx = v;
            }
        }
        heavy[u] = mx;
    }
    void flat(int u, int p, const vector<vector<int>> &ad)
    {
        id[u] = timer++;
        if (heavy[u])
            head[heavy[u]] = head[u], flat(heavy[u], u, ad);
        for (auto v : ad[u])
        {
            if (v == p || heavy[u] == v)
                continue;
            head[v] = v;
            flat(v, u, ad);
        }
    }

    vector<pair<int, int>> get_ranges(int u, int v)
    {
        vector<pair<int, int>> qu;
        while (true)
        {
            if (head[u] == head[v])
            {
                if (dep[u] > dep[v])
                    swap(u, v);
                qu.push_back({id[u], id[v]});
                return qu;
            }
            else
            {
                if (dep[head[u]] > dep[head[v]])
                    swap(u, v);
                qu.push_back({id[head[v]], id[v]});
                v = par[head[v]];
            }
        }
    }
};
////////////////////////////////////////// in  main

 HLD hl(n, ad);
 vector<int> v(n + 1);
 for (int i = 1; i <= n; i++)
        v[hl.id[i]] = a[i];
