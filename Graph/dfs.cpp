//!!!!!!!!!!!!!!!!!! is_cyclic !!!!!!!!!!!!!!!!!!
ll n , m , u , v ;
vector < int > adj[N] ;
bool vis[N] ;
bool is_cyclic ( int u , int p = -1 )
{
    vis[u] = true ;
    for ( auto v : adj[u] )
    {
        if ( vis[v] && v != p ) return true ;
        else if ( !vis[v] )
        {
            if ( is_cyclic ( v , u ) ) 
            return true ;
        }
    }
    return false ;
}
//!!!!!!!!!!!!!!!!!! is_cyclic_and_path !!!!!!!!!!!!!!!!!!
// find cycle and path
ll n , m , u , v ;
vector < int > adj[N] ;
bool vis[N] ;

int parent[N] ;
vector < int > ans ;
bool is_cyclic ( int u , int p = -1 )
{
    vis[u] = true ;
    parent[u] = p ;
    for ( auto v : adj[u] )
    {
        if ( v == p ) continue ;

        if ( vis[v] ) 
        {
            ans.push_back(v) ; 
            ll pa = u ;
            while ( pa != v )
            {
                ans.push_back(pa) ; 
                pa = parent[pa] ;
            }
            ans.push_back(v) ;
            reverse(all(ans)) ;
            return 1 ;
        }
        else if ( !vis[v] )
        {
            if ( is_cyclic ( v , u ) ) 
            return true ;
        }

    }
    return false ;
}
//!!!!!!!!!!!!!!!!!! mark all nodes in cycles !!!!!!!!!!!!!!!!!!
ll n , m , u , v ;
vector < int > adj[N] ;
bool vis[N] ;
bool in_cycle[N] ;
int parent[N] ;
vector < int > ans ;
void cycles ( int u , int p = -1 )
{
    vis[u] = true ;
    parent[u] = p ;
    for ( auto v : adj[u] )
    {
        if ( v == p ) continue ;
 
        if ( vis[v] )
        {
            ll pa = u ;
            while ( !in_cycle[pa] ) 
            {
                in_cycle[pa] = 1 ;
                if ( pa == v ) break ;
                pa = parent[pa] ;
            }
        }
        else if ( !vis[v] )
        {
            cycles ( v , u ) ;
        }
    }
}
//!!!!!!!!!!!!!!!!!! is_cyclic__directed !!!!!!!!!!!!!!!!!!
ll n , m , u , v ;
vector < int > adj[N] ;
int vis[N] ;
const int NOT_VISITED = 0 , IN_PROGRESS = 1 , VISITED = 2 ;
bool is_cyclic_directed ( int u )
{
    vis[u] = IN_PROGRESS ;
    for ( auto v : adj[u] )
    {
        if ( vis[v] == NOT_VISITED )
        {
            if ( is_cyclic_directed (v) )
            {
                return true ;
            }
        }
        else if ( vis[v] == IN_PROGRESS ) return true ; 
         
    }
    vis[u] = VISITED ; 
    return false ; 
}
//!!!!!!!!!!!!!!!!!! topological sort !!!!!!!!!!!!!!!!!!
ll n , m , u , v ;
vector < int > adj[N] ;
bool vis[N] ;
void topol ( int u )
{
    vis[u] = true ;
    for ( auto v : adj[u] )
    {
        if ( !vis[v] ) topol(v) ;
    }
    cout << u << ' ' ;
}
//!!!!!!!!!!!!!!!!!!!!!!odd cycle!!!!!!!!!!!!!!!!!!!!!!!!
vector<int> adj[N];
int color[N];

bool dfs(int u, int c)
{
    color[u] = c;

    for (int v : adj[u])
    {
        if (color[v] == 0)
        {
            if ( dfs ( v , c == 1 ? 2 : 1 ) )
                return 1 ;
        }
        else if (color[v] == color[u])
        {
            return 1;
        }
    }

    return 0;
}
