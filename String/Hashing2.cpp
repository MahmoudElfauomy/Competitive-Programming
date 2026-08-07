const ll b1 = 127 , b2 = 131 ;
const ll mod1 = 1e9 + 7 , mod2 = 1e9 + 9 ;
vector < int > pw1(N) , pw2(N) ;

void init()
{
    pw1[0] = pw2[0] = 1 ;
    for ( int i = 1 ; i < N ; i ++ )
    {
        pw1[i] = 1LL * pw1[i-1] * b1 % mod1 ;
        pw2[i] = 1LL * pw2[i-1] * b2 % mod2 ;
    }
}
struct Hashing
{

    vector < pair < int , int > > pre , suf ;

    int n ;
    bool built_suf = false ;

    Hashing ( string &s , bool need_suf = false )
    {
        n = s.size() ;
        pre.resize(n) ;
        build_prefix(s) ;

        if (need_suf)
        {
            build_suffix(s) ;
            built_suf = true ;
        }
    }

    void build_prefix ( string &s )
    {
        ll h1 = 0 , h2 = 0 ;
        for (int i = 0 ; i < n ; i++)
        {
            int digit = s[i] - 'a' + 1 ;
            h1 = ( h1 * b1 + digit ) % mod1 ;
            h2 = ( h2 * b2 + digit ) % mod2 ;
            pre[i] = {h1 , h2} ;
        }
    }

    void build_suffix ( string s )
    {
        reverse ( all(s) ) ;
        suf.resize(n) ;

        ll h1 = 0 , h2 = 0 ;
        for (int i = 0 ; i < n ; i++)
        {
            int digit = s[i] - 'a' + 1 ;
            h1 = ( h1 * b1 + digit ) % mod1 ;
            h2 = ( h2 * b2 + digit ) % mod2 ;
            suf[i] = {h1 , h2} ;
        }
    }

    pair < int , int > get ( int l , int r )
    {
        auto ret = pre[r] ;
        if ( l > 0 )
        {
            ret.first = ( ret.first - 1LL * pre[l-1].first * pw1[r-l+1] % mod1 + mod1) % mod1 ;
            ret.second = ( ret.second - 1LL * pre[l-1].second * pw2[r-l+1] % mod2 + mod2) % mod2 ;
        }

        return ret ;
    }

    pair < int , int > get_rev ( int l , int r )
    {
        int rl = n - r - 1 ;
        int rr = n - l - 1 ;

        auto ret = suf[rr] ;
        if ( rl > 0 )
        {
            ret.first = (ret.first - 1LL * suf[rl-1].first * pw1[rr-rl+1] % mod1 + mod1) % mod1 ;
            ret.second = (ret.second - 1LL * suf[rl-1].second * pw2[rr-rl+1] % mod2 + mod2) % mod2 ;
        }
        return ret ;
    }

    bool is_pal(int l , int r)
    {
        if ( !built_suf ) return false ;
        return get ( l , r ) == get_rev ( l , r ) ;
    }
} ;
