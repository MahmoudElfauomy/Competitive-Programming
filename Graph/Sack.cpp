int sub_sz[N], heavy[N];
vector<int> ad[N];
void pre_heavy(int u, int p) //////////// Call it First
{
    sub_sz[u] = 1;
    int mx = 0;
    for (auto v : ad[u])
    {
        if (v == p)
            continue;
        pre_heavy(v, u);
        sub_sz[u] += sub_sz[v];
        if (sub_sz[mx] < sub_sz[v])
        {
            mx = v;
        }
    }
    heavy[u] = mx;
}
void update(int node, int val)
{
}

void collect(int u, int p, int val)
{
    update(u, val);
    for (auto v : ad[u])
    {
        if (v == p)
            continue;
        collect(v, u, val);
    }
}
void dfs(int u, int p, int big)
{
    for (auto v : ad[u])
    {
        if (v == p || heavy[u] == v)
            continue;
        dfs(v, u, 0);
    }
    // add to DS
    if (heavy[u])
    {
        dfs(heavy[u], u, 1);
    }
    update(u, 1);
    for (auto v : ad[u])
    {
        if (v == p || heavy[u] == v)
            continue;
        collect(v, u, 1);
    }

    // answer query

    // remove from DS
    // if (!big)
    //     collect(u, p, -1);
}
