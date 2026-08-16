// set val , mx_sub_sum
struct node
    {
        ll pref = 0 ;
        ll suff = 0 ;
        ll sum = 0 ;
        ll sub = 0 ;
        ll lazy = 0 ;
        bool is_lazy = false ;
        
        void apply_build ( ll lx , ll rx , ll val ) 
        {
            sum  = val ;
            if ( val > 0 )
            {
                pref = suff = sub = sum ;
            }
            else
            {
                pref = suff = sub = 0 ;
            }
 
            lazy = 0 ;
            is_lazy = false ;
        }
 
        void apply_lazy ( ll lx , ll rx , ll val ) 
        {
            sum = val * ( rx - lx + 1 ) ;
 
            if ( val > 0 )
            {
                pref = suff = sub = sum ;
            }
            else 
            {
                pref = suff = sub = 0 ;
            }
 
            lazy = val ;
            is_lazy = true ;
        }
 
        void merge ( node L , node R )
        {
            sum  = L.sum + R.sum ;
            pref = max ( L.pref , L.sum + R.pref ) ;
            suff = max ( R.suff , R.sum + L.suff ) ;
            sub  = max ( { L.sub , R.sub , L.suff + R.pref } ) ;
        }
    };

//=====================================================================
// lazy_set _ & _ add 
  struct node
  {
    ll sum = 0 ;
    ll lazy_add = 0 ;
    ll lazy_set = 0 ;
    bool is_lazy = false ;
    bool is_set = false ;
    
    void apply_build ( ll lx , ll rx , ll val ) 
    {
      sum = val ;
      lazy_add = 0 ;
      lazy_set = 0 ;
      is_lazy = false ;
      is_set = false ;
    }

    void apply_lazy ( ll lx , ll rx , ll val , bool set_op ) 
    {
      if ( set_op )
      {
        sum = ( rx - lx + 1 ) * val ;
  
        lazy_set = val ;
        lazy_add = 0 ;
        is_set = true ;
      }
      else 
      {
        sum += ( rx - lx + 1 ) * val ;
        
        if ( is_set ) lazy_set += val ;
        else lazy_add += val ;
      }
      is_lazy = true ;
    }

    void merge ( node L , node R )
    {
      sum = L.sum + R.sum ;
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

    if ( seg[x].is_set )
    {
      seg[left_child].apply_lazy( lx , mid , seg[x].lazy_set , 1 ) ;
      seg[right_child].apply_lazy( mid + 1 , rx , seg[x].lazy_set , 1 ) ;
    }
    
    if ( seg[x].lazy_add )
    {
      seg[left_child].apply_lazy( lx , mid , seg[x].lazy_add , 0 ) ;
      seg[right_child].apply_lazy( mid + 1 , rx , seg[x].lazy_add , 0 ) ;
    }

    seg[x].lazy_add = 0 ;
    seg[x].lazy_set = 0 ;
    seg[x].is_lazy = false ;
    seg[x].is_set = false ;
  }

  void update ( ll x , ll lx , ll rx , ll l , ll r , ll val ) 
  {
    if ( lx > r || rx < l ) return ;
    if ( lx >= l && rx <= r )
    {
      bool set_op = (op == 2) ;
      seg[x].apply_lazy ( lx , rx , val , set_op ) ;
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
