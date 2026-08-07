vector<int> deg(N);
class Bridges
{
    /*
       bridge is an edge if i remove it the graph will be unconnected
    */
    vector<bool> vis;
    vector<int> low;
    void dfs(int u, int p)
    {
        vis[u] = 1;
        for (auto v : ad[u])
        {
            if (v == p)
                continue;
            if (vis[v])
            {
                low[u] = min(low[u], deg[v]);
                continue;
            }
            deg[v] = deg[u] + 1;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > deg[u])
            {
                // edge between u and v is bridge --------
            }
        }
    }

public:
    Bridges(int n)
    {
        vis = vector<bool>(n + 1);
        low = vector<int>(n + 1, 1e9);
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                dfs(i, -1);
            }
        }
    }
};
