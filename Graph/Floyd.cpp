ll dis[M][M] ;

for ( int i = 1 ; i <= M ; i ++ )
{
    for ( int j = 1 ; j <= M ; j ++ )
    {
        if ( i == j ) dis[i][j] = 0 ;
        else dis[i][j] = INF ;
    }
} 

for ( int k = 1 ; k <= M ; k ++ ) 
{
    for ( int i = 1 ; i <= M ; i ++ ) 
    {
        for ( int j = 1 ; j <= M ; j ++ ) 
        {
            if ( dis[i][k] < INF && dis[k][j] < INF ) 
            {
                dis[i][j] = min ( dis[i][j] , dis[i][k] + dis[k][j] ) ;
            }
        }
    }
}
