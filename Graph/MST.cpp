#define C first
#define U second.first
#define V second.second
typedef pair < int , pair < int , int > > edge ;

edge edge_list[M] ;

int n , m , q , u , v , c ;

class DSU
{
public:
    ll n ;
    int leader[N] , sz[N] ;

    DSU ( ll sz )
    {
        n = sz ;
        init() ;
    }

    void init() 
    {
        for ( int i = 0 ; i <= n ; i ++ ) 
        {
            leader[i] = i ;
            sz[i] = 1 ;
        }
    }

    int get_leader ( int u ) 
    {
        if ( u == leader[u] ) return u ;
        return leader[u] = get_leader(leader[u]) ;
    }

    void make_friends( int u , int v ) 
    {
        u = get_leader(u) ;
        v = get_leader(v) ;

        if ( u == v ) return ;

        if ( sz[u] < sz[v] ) swap( u , v ) ;
        
        leader[v] = u ;
        sz[u] += sz[v] ;
    }

    bool are_friends( int u , int v ) 
    {
        return (get_leader(u) == get_leader(v)) ;
    }
} ;
void Captain()
{
    cin >> n >> m ;

    for ( int i = 0 ; i < m ; i ++ )
    {
        cin >> u >> v >> c ;
        edge_list[i] = { c , { u , v } } ;
    }

    DSU d(n) ;

    sort ( edge_list , edge_list + m ) ;

    ll cost = 0 , counter = 0 ;
    vector < edge > mst ;

    for ( int i = 0 ; i < m ; i ++ )
    {
        if ( !d.are_friends ( edge_list[i].U , edge_list[i].V ) )
        {
            d.make_friends ( edge_list[i].U , edge_list[i].V ) ;

            cost += edge_list[i].C ;
            counter ++ ;

            mst.push_back ( edge_list[i] ) ;
        }
    }

    if ( counter == n - 1 )
    {
        cout << cost << el ;

        for ( auto e : mst )
        {
            cout << e.U << ' ' << e.V << ' ' << e.C << el ;
        }
    }
    else
    {
        cout << "IMPOSSIBLE" << el ;
    }
}
