vector<int> adj[N];

int mx_dist, mx_node;

void dfs ( int u , int p , int d )
{
    if ( d > mx_dist )
    {
        mx_dist = d ;
        mx_node = u ;
    }

    for ( auto v : adj[u] )
    {
        if(v == p) continue ;

        dfs(v, u, d + 1) ;
    }
}

int main()
{
    // DFS من أي Node
    mx_dist = -1 ;
    dfs(1, 0, 0) ;

    int A = mx_node ;

    // DFS من أبعد Node
    mx_dist = -1;
    dfs(A, 0, 0);

    cout << mx_dist << '\n' ;

}
