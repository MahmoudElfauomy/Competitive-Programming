ll n ;
ll a[17][17] ;
ll cost[ 1 << 16 ] ;
ll dp[ 1 << 16 ] ;
ll calc ( ll mask )
{
    if ( mask == 0 ) return 0 ;
    if ( ~dp[mask] ) return dp[mask] ;

    ll ans = -1e9 ;

    for ( int sub_mask = mask ; sub_mask ; sub_mask = ( sub_mask - 1 ) & mask )
    {
        ll op = calc ( mask ^ sub_mask ) + cost[sub_mask] ;

        ans = max ( ans , op ) ;
    }

    return dp[mask] = ans ;
}
void Captain()
{
    cin >> n ; 
    for ( int i = 0 ; i < n ; i ++ )
    {
        for ( int j = 0 ; j < n ; j ++ )
        {
            cin >> a[i][j] ;
        }
    }

    for ( int mask = 0 ; mask < ( 1 << n ) ; mask ++ )
    {
        cost[mask] = 0 ;
        for ( int i = 0 ; i < n ; i ++ )
        {
            if ( ( mask >> i ) & 1 )
            {
                for ( int j = i + 1 ; j < n ; j ++ )
                {
                    if ( ( mask >> j ) & 1 )
                    {
                        cost[mask] += a[i][j] ;
                    }
                }
            }
        }
    }

    memset ( dp , -1 , sizeof dp ) ;
    cout << calc ( ( 1 << n ) - 1 ) << el ;

}
/*==============================================*/
//? ⠼⠁⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠘⢆
