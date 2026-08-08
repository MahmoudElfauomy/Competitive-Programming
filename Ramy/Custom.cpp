
#include <bits/stdc++.h>
#define ll long long
#define el '\n'
#define all(v) v.begin(), v.end()
#define allr(v) v.rbegin(), v.rend()
using namespace std ;

const double PI = acos(-1.0) ;
#define ON( n , x ) ((n) | (1 << (x))) 
#define OFF( n , x ) ((n) & ~ (1 << (x))) 
#define isON( n , x ) (((n) >> (x)) & 1 ) 

int dx[] = { 0 , 0 , 1 , -1 , -1 , 1 , -1 , 1 } ;
int dy[] = { 1 , -1 , 0 , 0 , -1 , 1 , 1 , -1 } ;

/*==============================================*/
struct cmp
{
    bool operator() (tuple <int , int , int > a , tuple < int , int , int > b )
    {
        auto [ x1 , y1 , z1 ] = a ;
        auto [ x2 , y2 , z2 ] = b ;

        if ( x1 != x2 )
        return x1 < x2 ;

        if ( y1 != y2 )
        return y1 > y2 ;

        return z1 > z2 ;
    }
};
priority_queue < tuple < int , int , int > , vector < tuple < int , int , int > > , cmp > pq ;
/*==============================================*/
string getBinary( ll num , ll y ) 
{
    string ans ;
    for (int i = y - 1; i >= 0 ; -- i ) 
    {
        ans += (((num) >> (i)) & 1 ) + '0' ;
        //ans += isON( num , i ) + '0';
    }
    return ans ;
}
/*==============================================*/
string getBinary2 ( long long x )
{
    if (x == 0)
        return "0" ;

    string s ;
    while (x)
    {
        s += char((x & 1) + '0') ;
        x >>= 1 ;
    }

    reverse(s.begin(), s.end()) ;
    return s ; 
}
/*==============================================*/
ll binaryToDecimal(const string& s) 
{
    ll decimal = 0 ;
    for (char c : s) 
    {
        decimal = (decimal << 1) | (c - '0') ;
    }
    return decimal ;
}
/*==============================================*/
int number_of_ones ( ll x )
{
    return __builtin_popcount(x) ;
}
bool Knowbit(ll n , ll x )
{
    return ( n >> x ) & 1 ;  
}
ll Setbit ( ll n , ll x ) 
{
return ( n | ( 1 << x ) ) ;
}
ll Resetbit ( ll n , ll x )
{
    return  ( n & ( ~ ( 1 << x ) ) ) ;
    // or 
//  return ( n & ( -1 ^ ( 1 << x ) ) ) ;
}
ll Flip ( ll n , ll x )
{
    return ( n ^ ( 1 << x ) );
}
bool IsPowerOfTwo ( ll n )
{
    if ( n == 0 ) return 0 ; 
    return ! ( n & ( n - 1 )) ;
    // or
    // return ( __builtin_popcountl(n) == 1 ? 1 : 0) ;
}
/*==============================================*/
/*
a+b = 2(a&b) + a⊕b
a+b = a|b + a&b

a⊕b = ~(a&b) & (a∣b)

a|b = a⊕b + a&b

a⊕(a&b) = (a|b)⊕b

b⊕(a&b) = (a|b)⊕a

a⊕b = (a&b)⊕(a|b)

a-b = (a⊕(a&b))-((a|b)⊕a)

a-b = ((a|b)⊕b)-((a|b)⊕a)

a-b = (a⊕(a&b))-(b⊕(a&b))

a-b = ((a|b)⊕b)-(b⊕(a&b))
*/
