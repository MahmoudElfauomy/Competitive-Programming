vector<int> ad[N];
vector<int> dep(N);
vector<vector<int>> anc(N, vector<int>(21));
void clc_anc(int u, int p)
{
    anc[u][0] = p;
    for (int i = 1; i < 21; i++)
    {
        int z = anc[u][i - 1];
        anc[u][i] = anc[z][i - 1];
    }
    for (auto v : ad[u])
    {
        if (v != p)
        {
            dep[v] = dep[u] + 1;
            clc_anc(v, u);
        }
    }
}
int get(int u, int k)
{
    if (dep[u] < k)
        return -1;
    for (int i = 20; ~i; i--)
    {
        if ((1 << i) & k)
        {
            u = anc[u][i];
        }
    }
    return u;
}
int LCA(int u, int v)
{

    if (dep[u] < dep[v])
        swap(u, v);
    u = get(u, dep[u] - dep[v]);
    if (u == v)
        return u;
    for (int i = 20; ~i; i--)
    {
        if (anc[u][i] != anc[v][i])
        {
            u = anc[u][i];
            v = anc[v][i];
        }
    }
    return anc[u][0];
}
int get_dis(int u, int v)
{
    int z = LCA(u, v);
    return dep[u] + dep[v] - 2 * dep[z];
}
