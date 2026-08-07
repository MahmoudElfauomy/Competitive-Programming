int n , q ;
int blk ;
int timer ;
int cur ;
int ans[N] ;
vector < int > adj[N] ;
vector < int > in(N) , out(N) , flat(2 * N) ;
vector < int > val(N) ;
vector < int > depth(N) ;

const ll LOG = 20 ;
int up[N][LOG] ;

void dfs ( int u , int p )
{
    in[u] = ++ timer ;
    flat[timer] = u ;

    up[u][0] = p ;

    for ( int i = 1 ; i < LOG ; i++ )
    up[u][i] = up[ up[u][i-1] ][i-1] ;

    for ( auto v : adj[u] )
    {
        if ( v == p ) continue ;

        depth[v] = depth[u] + 1 ;
        dfs( v , u ) ;
    }

    out[u] = ++ timer ;
    flat[timer] = u ;
}

int kth_ancestor ( int u , int k )
{
    for ( int bit = 0 ; bit < LOG ; bit ++ )
    {
        if ( ( k >> bit ) & 1 )
        {
            u = up[u][bit] ;
        }
    }

    return u ;
}

int lca ( int u , int v )
{
    if ( depth[u] < depth[v] )
    swap ( u , v ) ;

    int k = depth[u] - depth[v] ;
    u = kth_ancestor ( u , k ) ;

    if ( u == v ) return u ;

    for ( int j = LOG - 1 ; j >= 0 ; j -- )
    {
        if ( up[u][j] != up[v][j] )
        {
            u = up[u][j] ;
            v = up[v][j] ;
        }
    }

    return up[u][0] ;
}


struct Query
{
    int l , r , idx , extra ;

    bool operator < ( const Query &other ) const
    {
        if ( l / blk != other.l / blk ) return l < other.l ;

        if ( ( l / blk ) & 1 ) return r > other.r ;

        return r < other.r ;
    }
};

vector < Query > query ;

bool vis[N] ;

void add ( int node )
{
    // update answer
}

void remove ( int node )
{
    // update answer
}

void Toggle ( int node )
{
    if ( vis[node] ) remove(node) ;
    else add(node) ;

    vis[node] ^= 1 ;
}


void MO ()
{
    blk = sqrt(timer) ;
    sort( all(query) ) ;

    int L = 1 ;
    int R = 0 ;

    for ( auto q : query )
    {
        while ( L > q.l ) Toggle(flat[--L]) ;
        while ( R < q.r ) Toggle(flat[++R]) ;
        while ( L < q.l ) Toggle(flat[L++]) ;
        while ( R > q.r ) Toggle(flat[R--]) ;

        if ( q.extra )
        Toggle(q.extra) ;

        ans[q.idx] = cur ;

        if ( q.extra )
        Toggle(q.extra) ;
    }
}

int main ()
{
    cin >> n >> q ;

    for ( int i = 1 ; i <= n ; i ++ )
    cin >> val[i] ;

    for ( int i = 1 ; i < n ; i ++ )
    {
        int u , v ;
        cin >> u >> v ;

        adj[u].push_back(v) ;
        adj[v].push_back(u) ;
    }

    dfs( 1 , 0 ) ;

    for ( int i = 0 ; i < q ; i ++ )
    {
        int u , v ;
        cin >> u >> v ;

        if ( in[u] > in[v] )
        swap ( u , v ) ;

        int LC = lca(u , v) ;

        if ( LC == u )
        {
            query.push_back ( { in[u] , in[v] , i , 0 } ) ;
        }
        else
        {
            query.push_back ( { out[u] , in[v] , i , LC } ) ;
        }
    }

    MO() ;

    for ( int i = 0 ; i < q ; i ++ )
    cout << ans[i] << el ;
}
