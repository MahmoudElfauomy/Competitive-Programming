class DSU
{
public:
    ll n ;
    vector < int > leader , sz , mn , mx ;
    stack < array < int , 7 > > st ;
    int cnt = 0 ;

    DSU ( ll siz )
    {
        n = siz ;
        cnt = n ;

        leader.resize(n+1) ;
        sz.resize(n+1) ;
        mn.resize(n+1) ;
        mx.resize(n+1) ;

        init() ;
    }

    void init()
    {
        for ( int i = 0 ; i <= n ; i ++ )
        {
            leader[i] = i ;
            sz[i] = 1 ;
            mn[i] = i ;
            mx[i] = i ;
        }
    }

    int get_leader ( int u )
    {
        if ( u == leader[u] ) return u ;
        return get_leader(leader[u]) ;
    }

    void make_friends ( int u , int v )
    {
        u = get_leader(u) ;
        v = get_leader(v) ;

        if ( u == v )
        {
            st.push({-1,-1,-1,-1,-1,-1,-1}) ;
            return ;
        }

        if ( sz[u] < sz[v] ) swap(u , v) ;

        st.push({
            u ,
            v ,
            sz[u] ,
            mn[u] ,
            mx[u] ,
            leader[v] ,
            cnt
        }) ;

        cnt -- ;

        leader[v] = u ;
        sz[u] += sz[v] ;
        mn[u] = min(mn[u] , mn[v]) ;
        mx[u] = max(mx[u] , mx[v]) ;
    }

    bool are_friends ( int u , int v )
    {
        return get_leader(u) == get_leader(v) ;
    }

    void rollback ( int k )
    {
        while ( k -- && !st.empty() )
        {
            auto [u , v , sz_u , mn_u , mx_u , pa_v , prev_cnt] = st.top() ;
            st.pop() ;

            if ( u == -1 ) continue ;

            sz[u] = sz_u ;
            mn[u] = mn_u ;
            mx[u] = mx_u ;
            leader[v] = pa_v ;
            cnt = prev_cnt ;
        }
    }
};

ll n , m , q ;
struct Query
{
    ll l , r , idx ;
};
pair < int , int > edges[N] ;
int ans[N] ;
int blk_sz ; // in main = sqrt(n) 
vector < Query > Buckets[450] ;

int main()
{
    cin >> n >> m >> q ;
    for ( int i = 0 ; i < m ; i ++ )
    cin >> edges[i].first >> edges[i].second ;

    blk_sz = sqrt(m) ;
    
    for ( int i = 0 ; i < q ; i ++ )
    {
        ll l , r ; cin >> l >> r ;
        l -- , r -- ;
        
        Buckets[l / blk_sz].push_back({l , r , i}) ; 
    }
    
    ll num_of_buckets = ( m + blk_sz - 1 ) / blk_sz ;
    for ( int i = 0 ; i < num_of_buckets ; i ++ )
    {
        sort( all(Buckets[i]) , [&] ( const Query & a , const Query & b ) -> bool {
            return a.r < b.r ;
        });

        DSU d(n) ;

        ll base = ( i + 1 ) * blk_sz ;
        ll r = base ;
        for ( auto &  qu : Buckets[i] )
        {
            while ( r <= qu.r )
            {
                d.make_friends ( edges[r].first , edges[r].second ) ;
                r ++ ;
            }
            int temp = 0 ;
            int L = qu.l;
            while ( L <= min(base - 1 , qu.r) )
            {
                d.make_friends(edges[L].first , edges[L].second) ;
                L ++ ;
                temp ++ ;
            }
            
            ans[qu.idx] = d.cnt ;
            d.rollback(temp) ;
        }
    }

    for ( int i = 0 ; i < q ; i ++ ) 
    cout << ans[i] << el ;

    for ( int i = 0 ; i < num_of_buckets ; i ++ )
    Buckets[i].clear() ;
}
