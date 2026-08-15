//الغرض منه إنك تقارن هل عنصرين/رنجين فيهم نفس الـ multiset من العناصر في 
//O(1) تقريبًا لكل Query بعد O(n) preprocessing.
std::mt19937_64 rng ( std::chrono::system_clock::now().time_since_epoch().count()) ;
ll rand ( ll l , ll r )
{
    return uniform_int_distribution<ll>( l , r )(rng) ;
}
struct permutation_hashing
{
    ll a , b , c , d , e ;
    permutation_hashing ( ll aa , ll bb , ll cc , ll dd , ll ee )
    {
        a = aa ;
        b = bb ; 
        c = cc ; 
        d = dd ; 
        e = ee ;
    }
    permutation_hashing ( )
    {
        a = rand ( 1 , 1e9 ) ;
        b = rand ( 1 , 1e9 ) ;
        c = rand ( 1 , 1e9 ) ;
        d = rand ( 1 , 1e9 ) ;
        e = rand ( 1 , 1e9 ) ;
    }
    permutation_hashing operator+( permutation_hashing tmp )
    {
        return permutation_hashing ( a + tmp.a , b + tmp.b , c + tmp.c , d + tmp.d , e + tmp.e ) ;
    }
    permutation_hashing operator-( permutation_hashing tmp )
    {
        return permutation_hashing ( a - tmp.a , b - tmp.b , c - tmp.c , d - tmp.d , e - tmp.e ) ;
    }
    bool operator==( permutation_hashing tmp )
    {
        return ( a == tmp.a && b == tmp.b && c == tmp.c && d == tmp.d && e == tmp.e ) ;
    }
    bool operator<(const permutation_hashing& tmp) const
    {
        if (a != tmp.a) return a < tmp.a ;
        if (b != tmp.b) return b < tmp.b ;
        if (c != tmp.c) return c < tmp.c ;
        if (d != tmp.d) return d < tmp.d ;
        return e < tmp.e ;
    }
};
/*==============================================*/
void Captain()
{
    ll n , q ; cin >> n >> q ;
    permutation_hashing v[n+1] , vv[n+1] ;
    
    v[0] = vv[0] = permutation_hashing ( 0 , 0 , 0 , 0 , 0 ) ;

    map < ll , permutation_hashing > mp ;
    for ( int i = 1 ; i <= n ; i ++ )
    {
        ll x ; cin >> x ;
        if ( !mp.count(x) )
        {
            mp[x] = permutation_hashing() ;
        }

        v[i] = mp[x] ;
        v[i] = v[i] + v[i-1] ;
    }

    for ( int i = 1 ; i <= n ; i ++ )
    {
        ll x ; cin >> x ;
        if ( !mp.count(x) )
        {
            mp[x] = permutation_hashing() ;
        }

        vv[i] = mp[x] ;
        vv[i] = vv[i] + vv[i-1] ;
    }

    while ( q -- )
    {
        ll l , r , L , R ; 
        cin >> l >> r >> L >> R ;

        if ( v[r] - v[l-1] == vv[R] - vv[L-1] ) 
        cout << "Yes" << el ;
        else 
        cout << "No" << el ;
    }
}
