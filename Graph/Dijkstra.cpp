//! minumim path cost between node u and anonter nodes 
const ll INF = 1e18 ;
//! O(( n + m ) log n )
ll n , m ;
vector < pair < int , ll > > adj[N] ;
vector < ll > cost( N , INF ) ;

void dijkstra ( ll start )
{
    cost[start] = 0 ;
    priority_queue < pair < ll , int > , vector < pair < ll , int > > , greater<> > pq ;

    pq.push( { 0 , start } ) ;

    while ( !pq.empty() )
    {
        auto [ c , u ] = pq.top() ;
        pq.pop() ;
        if ( c > cost[u] ) continue ;

        for ( auto [ v , w ] : adj[u] )
        {
            if ( cost[v] > c + w )
            {
                cost[v] = c + w ;
                pq.push( { cost[v] , v } ) ;
            }
        }
    }
}

int main() 
{
    cin >> n >> m ;
    for ( int i = 0 ; i < m ; i ++ ) 
    {
        int u , v ;
        ll w ;
        cin >> u >> v >> w ;
        adj[u].push_back( { v , w } ) ;
        adj[v].push_back( { u , w } ) ; 
    }

    int start ;
    cin >> start ;
    
    // fill ( all ( cost ) , INF ) ;
    dijkstra ( start ) ;

    for ( int i = 1 ; i <= n ; i ++ ) 
    {
        if ( cost[i] == INF )
        cout << "INF" << el ;
        else 
        cout << cost[i] << el ;
    }
}
