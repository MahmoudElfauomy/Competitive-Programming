class segment_tree_lazy
{
private:

    struct node
    {
        ll sum = 0 ;
        ll lazy = 0 ;
        bool is_lazy = false ;
        
        void apply_build ( ll lx , ll rx , ll val ) 
        {
            sum = val ;
            lazy = 0 ;
            is_lazy = false ;
        }

        void apply_lazy ( ll lx , ll rx , ll val ) 
        {
            sum += val ;
            lazy += val ;
            is_lazy = true ;
        }

        void merge ( node L , node R )
        {
            sum = ( L.sum + R.sum ) ;
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
    
    void build ( ll x , ll lx , ll rx , vector <ll>& v )
    {
        if ( lx == rx )
        {
            if ( lx < (ll)v.size() )
            {
                seg[x].apply_build ( lx , rx , v[lx] ) ;
            }
            return ;
        }

        ll left_child = ( (2 * x) + 1 ) ; 
        ll right_child = ( (2 * x) + 2 ) ; 
        ll mid = ( lx + rx ) / 2 ;

        build ( left_child , lx , mid , v ) ;
        build ( right_child , mid + 1 , rx , v ) ;

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

    //! needs max 
    //! 0 index
    // ll find_first ( ll x , ll lx , ll rx , ll l , ll r , ll val )
    // {
    //     if ( rx < l || lx > r ) return -1 ;
    //     //! lower
    //     if ( seg[x].mx < val ) return -1 ;
    //     //! upper
        // if ( seg[x].mx <= val ) return -1 ;
    //     if ( lx == rx ) return lx ;
    //     ll left_child = (2 * x) + 1 ;
    //     ll right_child = (2 * x) + 2 ;
    //     ll mid = (lx + rx) / 2 ;

    //     ll res = find_first( left_child , lx , mid , l , r , val ) ;
    //     if ( res != -1 ) return res ;
    //     return find_first( right_child , mid + 1 , rx , l , r , val ) ;
    // }

public:
    segment_tree_lazy( vector <ll>& v )
    {
        while ( sz < (ll)v.size() )
        {
            sz *= 2 ;
        }
        
        seg.assign( 2 * sz , node() ) ;

        build ( 0 , 0 , sz - 1 , v ) ;
    };
    void update ( ll l , ll r , ll val )
    {
        update ( 0 , 0 , sz - 1 , l , r , val ) ;
    }
    node query( ll l , ll r )
    {
        return query ( 0 , 0 , sz - 1 , l , r ) ;
    }
    // ll find_first( ll l , ll r , ll val )
    // {
    //     if ( l > r ) return -1 ;
    //     return find_first( 0 , 0 , sz - 1 , l , r , val ) ;
    // }
};
