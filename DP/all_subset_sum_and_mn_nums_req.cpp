    // O ( distinct vals * mx_sum )
    //!  minumum element needed to create all subset sum
    ll n ; cin >> n ;
    ll mx_sum = 0 ;
    vector < ll > v(n) ;
    for ( auto& it : v ) cin >> it , mx_sum += it ;

    vector < ll > cnt ( mx_sum + 1 ) ;
    for ( auto it : v ) cnt[it] ++ ;

    vector < int > dp ( mx_sum + 1 , 1e9 ) ;
    dp[0] = 0 ;

    for ( int val = 1 ; val <= mx_sum ; val ++ ) 
    {
        if ( cnt[val] == 0 ) continue ;

        for ( int r = 0 ; r < val ; r ++ ) 
        {
            deque < pair < ll , ll > > dq ;
            for ( int k = 0 , sum = r ; sum <= mx_sum ; k ++ , sum += val ) 
            {
                ll x = dp[sum] - k ;

                while ( !dq.empty() && dq.back().first >= x )
                dq.pop_back() ;

                dq.push_back({ x , k }) ;

                while ( !dq.empty() && dq.front().second < k - cnt[val] )
                dq.pop_front() ;

                dp[sum] = dq.front().first + k ;
            }
        }
    }

    for ( int sum = 0 ; sum <= mx_sum ; sum ++ )
    if (dp[sum] != 1e9)
    cout << "sum = " << sum << ", min elements = " << dp[sum] << el ;
