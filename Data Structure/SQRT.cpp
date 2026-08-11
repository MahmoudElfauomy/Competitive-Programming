const int SQ = 320 ;

vector < ll > v ;
vector < ll > blk ;
ll blk_sz ;
map < int , int > mp[SQ] ;
void build ( ll n )
{
    blk_sz = ceil ( sqrt(n) ) + 1 ;
    ll num_blks = ( n + blk_sz - 1 ) / blk_sz ;
    blk.assign ( num_blks , 0 ) ;
    for ( int i = 0 ; i < n ; i ++ )
    {
        ll idx = i / blk_sz ;
        mp[idx][v[i]] ++ ;
    }
}

void update ( ll idx , ll val )
{
    mp[idx/blk_sz][v[idx]] -- ;
    if ( mp[idx/blk_sz][v[idx]] == 0 )
    mp[idx/blk_sz].erase(v[idx]) ;

    v[idx] = val ;
    mp[idx/blk_sz][v[idx]] ++ ;
}

ll query ( ll l , ll r , ll val )
{
    if ( l > r ) return 0 ; 
    
    ll blk_l = l / blk_sz ;
    ll blk_r = r / blk_sz ;

    ll c = 0 ;
    if ( blk_l == blk_r )
    {
        for ( int i = l ; i <= r ; i ++ )
        {
            c += ( v[i] == val ) ;
        }
    }
    else 
    {
        for ( int i = l ; i < ( blk_l + 1 ) * blk_sz ; i ++ )
        {
            c += ( v[i] == val ) ;
        }

        for ( int i = blk_l + 1 ; i < blk_r ; i ++ )
        {
            if ( mp[i].count(val) ) 
            c += mp[i][val] ;
        }

        for ( int i = blk_r * blk_sz ; i <= r ; i ++ )
        {
            c += ( v[i] == val ) ;
        }
    }

    return c ;
}
