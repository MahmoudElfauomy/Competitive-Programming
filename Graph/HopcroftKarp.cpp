struct HopcroftKarp
{
    int n;
    vector<vector<int>> adj;
    vector<int> mu, mv, dist;
    // mu is left set is match with right set
    // mv is right set is match with left set

    HopcroftKarp(int n, int m) : n(n), adj(n), mu(n, -1), mv(m, -1), dist(n) {}

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
    }

    bool bfs()
    {
        queue<int> q;
        for (int u = 0; u < n; ++u)
        {
            if (mu[u] == -1)
            {
                dist[u] = 0;
                q.push(u);
            }
            else
            {
                dist[u] = -1;
            }
        }
        bool found = false;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : adj[u])
            {
                if (mv[v] == -1)
                {
                    found = true;
                }
                if (mv[v] != -1 && dist[mv[v]] == -1)
                {
                    dist[mv[v]] = dist[u] + 1;
                    q.push(mv[v]);
                }
            }
        }
        return found;
    }

    bool dfs(int u)
    {
        for (int v : adj[u])
        {
            if (mv[v] == -1 || (dist[mv[v]] == dist[u] + 1 && dfs(mv[v])))
            {
                mu[u] = v;
                mv[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching()
    {
        int res = 0;
        while (bfs())
        {
            for (int u = 0; u < n; ++u)
            {
                if (mu[u] == -1 && dfs(u))
                {
                    res++;
                }
            }
        }
        return res;
    }
    pair<vector<int>, vector<int>> min_vertex_cover()
    {
        max_matching();
        int m = mv.size();
        vector<bool> visited_left(n, false);
        vector<bool> visited_right(m, false);
        queue<int> q;
        for (int u = 0; u < n; ++u)
        {
            if (mu[u] == -1)
            {
                visited_left[u] = true;
                q.push(u);
            }
        }
        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v : adj[u])
            {
                if (!visited_right[v])
                {
                    visited_right[v] = true;
                    if (mv[v] != -1 && !visited_left[mv[v]])
                    {
                        visited_left[mv[v]] = true;
                        q.push(mv[v]);
                    }
                }
            }
        }
        vector<int> left_cover, right_cover;
        for (int u = 0; u < n; ++u)
        {
            if (!visited_left[u])
            {
                left_cover.push_back(u);
            }
        }
        for (int v = 0; v < m; ++v)
        {
            if (visited_right[v])
            {
                right_cover.push_back(v);
            }
        }
        return {left_cover, right_cover};
    }
};
