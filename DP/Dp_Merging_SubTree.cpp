void dfs(int u, int p)
{
    sz[u] = 1;
    dp[u][1] = val[u]; 
    dp[u][0] = 0;    

    for (int v : adj[u])
    {
        if (v == p)
            continue;
        dfs(v, u); 
        for (int i = 0; i <= sz[u] + sz[v]; i++)
        {
            new_dp[i] = -INF;
        }
        for (int i = 0; i <= sz[u]; i++)
        { 
            for (int j = 0; j <= sz[v]; j++)
            { 
                if (dp[u][i] != -INF && dp[v][j] != -INF)
                {
                    new_dp[i + j] = max(new_dp[i + j], dp[u][i] + dp[v][j]);
                }
            }
        }
        sz[u] += sz[v];
        for (int i = 0; i <= sz[u]; i++)
        {
            dp[u][i] = new_dp[i];
        }
    }
}
/////////////////////////////////// in main
for (int u = 1; u <= n; u++)
{
   for (int i = 1; i <= sz[u]; i++) 
   {
      mx[i] = max(mx[i], dp[u][i]);
   }
}
