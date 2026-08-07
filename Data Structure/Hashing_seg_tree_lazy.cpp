const ll b1 = 127 , b2 = 131 ;
const ll mod1 = 1e9 + 7 , mod2 = 1e9 + 9 ;
vector < ll > pw1(N) , pw2(N) ;
vector < ll > sum1(N) , sum2(N) ;

void init()
{
    pw1[0] = pw2[0] = 1 ;
    for ( int i = 1 ; i < N ; i ++ )
    {
        pw1[i] = 1LL * pw1[i-1] * b1 % mod1 ;
        pw2[i] = 1LL * pw2[i-1] * b2 % mod2 ;
    }

    sum1[0] = sum2[0] = 1 ;
    for ( int i = 1 ; i < N ; i ++ )
    {
        sum1[i] = ( sum1[i-1] + pw1[i] ) % mod1  ;
        sum2[i] = ( sum2[i-1] + pw2[i] ) % mod2 ;
    }
}

class segment_tree_lazy
{
private:

    struct node
    {
        ll h1 = 0 ;
        ll h2 = 0 ;
        ll len = 0 ;
        int lazy = 0 ;
        bool is_lazy = false ;
        
        void apply_build ( ll lx , ll rx , ll val ) 
        {
            h1 = val % mod1 ;
            h2 = val % mod2 ;
            len = 1 ;
            lazy = 0 ;
            is_lazy = false ;
        }

        void apply_lazy ( ll lx , ll rx , ll val ) 
        {
            h1 = (val * ( sum1[(rx - lx)] )) % mod1 ;
            h2 = (val * ( sum2[(rx - lx)] )) % mod2 ;
            lazy = val ;
            is_lazy = true ;
        }

        void merge ( node L , node R )
        {
            h1 = ( ( L.h1 * pw1[R.len] ) % mod1 + R.h1 % mod1 ) % mod1 ;
            h2 = ( ( L.h2 * pw2[R.len] ) % mod2 + R.h2 % mod2 ) % mod2 ;

            len = R.len + L.len ;
        }
    };

    ll sz = 1 ; 
    vector < node > seg ;

    void propagate ( ll x , ll lx , ll rx )
    {
        if ( !seg[x].is_lazy || ( lx == rx ) ) return ;

        ll left_child = ( (2 * x) + 1 ) ; 
        ll right_child = ( (2 * x) + 2 ) ; 
        ll mid = ( lx + rx ) / 2 ;

        seg[left_child].apply_lazy( lx , mid , seg[x].lazy ) ;
        seg[right_child].apply_lazy( mid + 1 , rx , seg[x].lazy ) ;

        seg[x].lazy = 0 ;
        seg[x].is_lazy = false ;
    }
    
    void build ( ll x , ll lx , ll rx , string & s )
    {
        if ( lx == rx )
        {
            if ( lx < (ll)s.size() )
            {
                seg[x].apply_build ( lx , rx , s[lx] - '0' ) ;
            }
            return ;
        }

        ll left_child = ( (2 * x) + 1 ) ; 
        ll right_child = ( (2 * x) + 2 ) ; 
        ll mid = ( lx + rx ) / 2 ;

        build ( left_child , lx , mid , s ) ;
        build ( right_child , mid + 1 , rx , s ) ;

        seg[x].merge ( seg[left_child] , seg[right_child] ) ;
    }

    void update ( ll x , ll lx , ll rx , ll l , ll r , ll val ) 
    {
        if ( lx > r || rx < l ) return ;
        if ( lx >= l && rx <= r )
        {
            seg[x].apply_lazy ( lx , rx , val ) ;
            return ;
        }
        propagate ( x , lx , rx ) ;

        ll left_child = ( (2 * x) + 1 ) ; 
        ll right_child = ( (2 * x) + 2 ) ; 
        ll mid = ( lx + rx ) / 2 ;
        
        update ( left_child , lx , mid , l , r , val ) ;
        update ( right_child , mid + 1 , rx , l , r , val ) ;
        
        seg[x].merge( seg[left_child] , seg[right_child] ) ;
    }

    node query ( ll x , ll lx , ll rx , ll l , ll r )
    {
        if ( lx > r || rx < l ) return node() ;
        if ( lx >= l && rx <= r ) return seg[x] ;
        
        propagate( x , lx , rx ) ;

        ll left_child = ( (2 * x) + 1 ) ; 
        ll right_child = ( (2 * x) + 2 ) ; 
        ll mid = ( lx + rx ) / 2 ;

        node L = query ( left_child , lx , mid , l , r ) ;
        node R = query ( right_child , mid + 1 , rx , l , r ) ;

        node ans ;
        ans.merge ( L , R ) ;
        return ans ;
    }

public:
    segment_tree_lazy( string & s )
    {
        while ( sz < (ll)s.size() )
        {
            sz *= 2 ;
        }
        
        seg.assign( 2 * sz , node() ) ;

        build ( 0 , 0 , sz - 1 , s ) ;
    };
    void update ( ll l , ll r , ll val )
    {
        update ( 0 , 0 , sz - 1 , l , r , val ) ;
    }
    node query( ll l , ll r )
    {
        return query ( 0 , 0 , sz - 1 , l , r ) ;
    }
};
/*==============================================*/
void Captain()
{
    ll n ; cin >> n ;

    ll x , y ; cin >> x >> y ; 
    ll q = x + y ; 

    string s ; cin >> s ;
    segment_tree_lazy st(s) ;

    while ( q -- )
    {
        ll op , l , r , val ; 
        cin >> op >> l >> r >> val ;
        l -- , r -- ;
        if ( op == 1 ) 
        {
            st.update ( l , r , val ) ;
        }
        else 
        {
            ll d = val ;
            if ( st.query( l + d , r ).h1 == st.query (  l , r - d ).h1 && 
                 st.query( l + d , r ).h2 == st.query (  l , r - d ).h2 
                )
            YES
            else 
            NO
                
        }
    }
    
}
/*==============================================*/
void pre()
{
    init() ;
}
/*==============================================*/
//? ⠼⠁⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠘⢆
