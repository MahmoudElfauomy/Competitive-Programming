#include <bits/stdc++.h>
#define ll long long
#define el '\n'
#define all(v) v.begin() , v.end()
#define allr(v) v.rbegin() , v.rend()
#define YES cout << "YES" << el ;
#define NO cout << "NO" << el ;
const ll N = 2e5 + 5 , M = 1e2 + 5 , mod = 1e9 + 7 , mod2 = 998244353 , INF = 1e18 , OO = 0x3f3f3f3f ;
#define RAMY ios_base::sync_with_stdio(0) , cout.tie(0) , cin.tie(0) ;
using namespace std ;

/*==============================================*/
//! Look Down :)
/*==============================================*/

int k ;
string l , r ;
ll dp[11][82][82][2][2] ;
// sum_d = sum_digit
// sum_n = sum_num
ll calc ( int i , int sum_d , int sum_n , bool tightL , bool tightR )
{
    if ( i == r.size() )
        return ( sum_d == 0 && sum_n == 0 ) ;

    ll &ret = dp[i][sum_d][sum_n][tightL][tightR] ;

    if ( ~ret ) return ret ;

    int low = tightL ? ( l[i] - '0' ) : 0 ;
    int high = tightR ? ( r[i] - '0' ) : 9 ;

    ll ans = 0 ;

    for ( int d = low ; d <= high ; d ++ )
    {
        bool newTightL = tightL && ( d == low ) ;
        bool newTightR = tightR && ( d == high ) ;

        ans += calc
        (
            i + 1 ,
            ( sum_d + d ) % k ,
            ( sum_n * 10 + d ) % k ,
            newTightL ,
            newTightR
        ) ;
    }

    return ret = ans ;
}

void Captain()
{
    int n ;
    cin >> n ;

    for ( int tc = 1 ; tc <= n ; tc ++ )
    {
        ll L , R ;
        cin >> L >> R >> k ;

        if ( k > 81 )
        {
            cout << "Case " << tc << ": " << 0 << el ;
            continue ;
        }

        l = to_string(L) ;
        r = to_string(R) ;

        // نخليهم نفس الـ length عن طريق leading zeros في l
        while ( l.size() < r.size() )
            l = '0' + l ;

        memset(dp , -1 , sizeof dp) ;

        ll ans = calc(0 , 0 , 0 , 1 , 1) ;

        cout << "Case " << tc << ": " << ans << el ;
    }
}

/*==============================================*/
