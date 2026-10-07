struct Dinic 
{
    struct Edge 
    {
        int to ;
        int rev ;
        ll flow ;
        ll cap ;
    };

    struct FlowPath 
    {
        ll flow ;
        vector<int> path ;
    };

    int n ;
    vector < int > lvl, ptr ;
    vector < vector < Edge > > adj ;
    vector < ll > flows ;

    Dinic (int n) : n(n), lvl(n + 1), ptr(n + 1), adj(n + 1) {}

    void add_edge ( int u , int v , ll c = 1 , bool directed = true ) 
    {
        adj[u].push_back({v, (int)adj[v].size(), 0, c}) ;
        adj[v].push_back({u, (int)adj[u].size() - 1, 0, (directed ? 0 : c) }) ;
    }

    bool bfs ( int s , int t ) 
    {
        fill ( lvl.begin() , lvl.end() , -1 ) ;
        queue < int > q ;
        q.push(s) ;
        lvl[s] = 0 ;

        while (!q.empty()) 
        {
            int u = q.front() ;
            q.pop() ;

            for (auto &[to, rev, flow, cap] : adj[u]) 
            {
                if ( cap - flow > 0 && lvl[to] == -1 ) 
                {
                    lvl[to] = lvl[u] + 1 ;
                    q.push(to) ;
                }
            }
        }
        return lvl[t] != -1 ;
    }

    ll dfs ( int u , int t , ll pushed ) 
    {
        if (pushed == 0) return 0 ;
        if (u == t) return pushed ;

        for ( int &cid = ptr[u] ; cid < (int)adj[u].size() ; cid ++ ) 
        {
            Edge &e = adj[u][cid] ;

            if ( e.cap - e.flow == 0 ) continue ;
            if ( lvl[e.to] != lvl[u] + 1 ) continue ;


            ll tr = dfs( e.to , t , min ( pushed , e.cap - e.flow ) ) ;
            if (tr > 0) 
            {
                e.flow += tr ;
                adj[e.to][e.rev].flow -= tr ;

                return tr ;
            }
        }
        return 0 ;
    }

    ll max_flow( int s , int t ) 
    {
        ll tot = 0 ;

        flows.clear() ;

        while (bfs(s, t)) 
        {
            fill( ptr.begin() , ptr.end() , 0 ) ;

            while ( ll pushed = dfs(s, t, 1e18) ) 
            {
                tot += pushed ;
                flows.push_back(pushed) ;
            }
        }
        return tot ;
    }

    // ترجع 1 لكل عقدة تنتمي إلى جانب المصدر بعد القطع
    vector < bool > get_cut_nodes ( int s ) 
    {
        vector < bool > visited( n + 1 , false ) ;
        queue < int > q ;
        q.push(s) ;
        visited[s] = true ;

        while (!q.empty()) 
        {
            int u = q.front() ;
            q.pop() ;

            for (auto &e : adj[u]) 
            {
                if (e.cap - e.flow > 0 && !visited[e.to]) 
                {
                    visited[e.to] = true ;
                    q.push(e.to) ;
                }
            }
        }

        return visited ;
    }

    vector < pair < int , int > > get_min_cut_edges(int s) 
    {
        vector < bool > in_S = get_cut_nodes(s) ;
        vector < pair < int , int > > cut_edges ;

        for ( int u = 0 ; u <= n ; u ++ ) 
        {
            if (!in_S[u]) continue ;

            for ( auto &e : adj[u] ) 
            {
                if (!in_S[e.to] && e.cap > 0) 
                {
                    cut_edges.push_back({ u , e.to }) ;
                }
            }
        }
        return cut_edges ;
    }

   
    vector < FlowPath > get_flow_paths ( int s , int t ) 
    {
        vector < vector < Edge > > adj_copy = adj ;
        vector < FlowPath > paths ;

        while (true) 
        {
            vector < int > parent(n + 1, -1) ;
            vector < int > edge_idx(n + 1, -1) ;
            queue < int > q ;

            q.push(s) ;
            while (!q.empty()) 
            {
                int u = q.front() ;
                q.pop() ;
                if (u == t) break ;

                for (int i = 0 ; i < (int)adj_copy[u].size() ; i ++ ) 
                {
                    auto &e = adj_copy[u][i] ;
                    if ( e.flow > 0 && parent[e.to] == -1 ) 
                    {
                        parent[e.to] = u ;
                        edge_idx[e.to] = i ;
                        q.push(e.to) ;
                    }
                }
            }

            if (parent[t] == -1) break ;

            ll path_flow = 1e18 ;
            int curr = t ;
            while (curr != s) 
            {
                int p = parent[curr] ;
                int idx = edge_idx[curr] ;
                path_flow = min ( path_flow , adj_copy[p][idx].flow ) ;
                curr = p ;
            }

            vector < int > current_path ;
            curr = t ;
            while (curr != s) 
            {
                current_path.push_back(curr) ;
                int p = parent[curr] ;
                int idx = edge_idx[curr] ;
                adj_copy[p][idx].flow -= path_flow ;
                curr = p ;
            }
            current_path.push_back(s) ;
            reverse(current_path.begin(), current_path.end()) ;

            paths.push_back({path_flow, current_path}) ;
        }

        return paths ;
    }
};

/*
ll n , m , K , SS ;
// K = n * m ; // main
//SS = 2 * K + 1 ; // main
int in (int i, int j) 
{
    return 1 + (i * m + j) ;
};

int out (int i, int j) 
{
    return 1 + K + (i * m + j) ;
};
*/