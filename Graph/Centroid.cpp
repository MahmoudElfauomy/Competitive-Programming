
vector<int> ad[N];
int sub_sz[N], removed[N];
ll ans = 0;

int get_sz(int u, int p)
{
    sub_sz[u] = 1;
    for (int v : ad[u])
    {
        if (v == p || removed[v])
            continue;
        sub_sz[u] += get_sz(v, u);
    }
    return sub_sz[u];
}

int get_cent(int u, int p, int cur_sz)
{
    for (int v : ad[u])
    {
        if (v == p || removed[v])
            continue;
        if (sub_sz[v] * 2 > cur_sz)
            return get_cent(v, u, cur_sz);
    }
    return u;
}

void add(int x, int delta)
{
}

void get_ans(int u, int p)
{
    for (int v : ad[u])
    {
        if (v == p || removed[v])
            continue;
        get_ans(v, u);
    }
}

void dfs_add(int u, int p, int delta)
{
    add(u, delta);
    for (int v : ad[u])
    {
        if (v == p || removed[v])
            continue;
        dfs_add(v, u, delta);
    }
}

void decomp(int u)
{
    int cent = get_cent(u, -1, get_sz(u, -1));

    add(cent, 1);
    for (int v : ad[cent])
    {
        if (removed[v])
            continue;
        get_ans(v, cent);
        dfs_add(v, cent, 1);
    }

    add(cent, -1);
    for (int v : ad[cent])
    {
        if (removed[v])
            continue;
        dfs_add(v, cent, -1);
    }

    removed[cent] = 1;
    for (int v : ad[cent])
    {
        if (removed[v])
            continue;
        decomp(v);
    }
}
