struct AHO
{
    int N, P;
    const int A = 26;
    vector<vector<int>> next;
    vector<int> link, out_link;
    vector<vector<int>> out;
    /*
    link : longest suffix valid
    out_link : nearest suffix pattern
    out : store indexes that end at node u
    */
    AHO() : N(0), P(0) { node(); }
    int node()
    {
        next.emplace_back(A, 0);
        link.emplace_back(0); 
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }
    inline int get(char c)
    {
        return c - 'a';
    }
    void add_pattern(const string T, int idx)
    {
        int u = 0;
        for (auto c : T)
        {
            if (!next[u][get(c)])
                next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(idx);
    }
    void compute() //////////////////////////////// REMEMBER
    {
        queue<int> q;
        for (q.push(0); !q.empty();)
        {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c)
            {
                int v = next[u][c];
                if (!v)
                    next[u][c] = next[link[u]][c];
                else
                {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }
    int advance(int u, char c)
    {
        while (u && !next[u][get(c)])
            u = link[u];
        u = next[u][get(c)];
        return u;
    }
    string smallest(int L)
    {
        string res;
        int u = 0;
        for (int i = 0; i < L; i++)
        {
            for (int c = 0; c < 26; c++)
            {
                int v = next[u][c];
                if (out[v].empty())
                {
                    res.push_back(char('a' + c));
                    u = v;
                    break;
                }
            }
        }
        return res;
    }
};
/*

    int q;
    AHO ah;
    cin >> q;
    string s[q];
    for (int i = 0; i < q; i++)
        {
        cin >> s[i];
        ah.add_pattern(s[i], i);
        }
        ah.compute();
        int u = 0;
        for (int i = 0; i < x.size(); i++)
        {
            char it = x[i];
            u = ah.advance(u, it);
            for (int v = u; v != 0; v = ah.out_link[v])
            {
                for (auto itt : ah.out[v])
                {
                    ans[itt].push_back(i - s[itt].size() + 1);
                }
            }
        }
            
*/
