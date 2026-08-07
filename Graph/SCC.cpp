/*
  global
*/
vector<int> ad[N], rev[N];
vector<bool> vis(N);
vector<int> comp;
void dfs(int u)
{
    vis[u] = 1;
    for (auto v : ad[u])
    {
        if (!vis[v])
        {
            dfs(v);
        }
    }
    comp.push_back(u);
}
void rev_dfs(int u)
{
    vis[u] = 1;
    for (auto v : rev[u])
    {
        if (!vis[v])
            rev_dfs(v);
    }
    comp.push_back(u);
}

/*
   in main -------
*/

int n, m;
cin >> n >> m;
for (int i = 0; i < m; i++)
{
    int a, b;
    cin >> a >> b;
    ad[a].push_back(b);
    rev[b].push_back(a);
}
for (int i = 1; i <= n; i++)
{
    if (!vis[i])
    {
        dfs(i);
    }
}
for (int i = 1; i <= n; i++)
{
    vis[i] = 0;
}
auto ord = comp;
reverse(ord.begin(), ord.end());
vector<int> id(n + 1), root;
for (auto i : ord)
{
    if (!vis[i])
    {
        comp.clear();
        rev_dfs(i);
        for (auto it : comp)
            id[it] = comp.front();
        root.push_back(comp.front());
    }
}
vector<int> dag[n + 1];
for (int i = 1; i <= n; i++)
{
    for (auto v : ad[i])
    {
        if (id[i] != id[v])
            dag[id[i]].push_back(id[v]);
    }
}
