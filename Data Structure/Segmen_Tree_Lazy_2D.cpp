#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

class segment_tree_lazy_2d
{
private:

    struct node
    {
        ll sum = 0 ;
        ll lazy = 0 ;
        bool is_lazy = false ;
        
        void apply_build ( ll val ) 
        {
            sum = val ;
            lazy = 0 ;
            is_lazy = false ;
        }

        void apply_lazy ( ll lx , ll rx , ll ly , ll ry , ll val ) 
        {
            ll count = ( rx - lx + 1 ) * ( ry - ly + 1 ) ;
            sum += count * val ;
            lazy += val ;
            is_lazy = true ;
        }

        void merge ( const node &TL , const node &TR , const node &BL , const node &BR )
        {
            sum = TL.sum + TR.sum + BL.sum + BR.sum ;
        }
    };

    ll sz_r = 1 , sz_c = 1 ; 
    vector < node > seg ;

    void propagate ( ll x , ll lx , ll rx , ll ly , ll ry )
    {
        if ( !seg[x].is_lazy || ( lx == rx && ly == ry ) ) return ;

        ll mid_x = ( lx + rx ) / 2 ;
        ll mid_y = ( ly + ry ) / 2 ;
        ll val = seg[x].lazy ;

        ll c0 = 4 * x + 1 ; // Top-Left
        ll c1 = 4 * x + 2 ; // Top-Right
        ll c2 = 4 * x + 3 ; // Bottom-Left
        ll c3 = 4 * x + 4 ; // Bottom-Right

        if ( lx <= mid_x && ly <= mid_y )
            seg[c0].apply_lazy( lx , mid_x , ly , mid_y , val ) ;

        if ( lx <= mid_x && mid_y + 1 <= ry )
            seg[c1].apply_lazy( lx , mid_x , mid_y + 1 , ry , val ) ;

        if ( mid_x + 1 <= rx && ly <= mid_y )
            seg[c2].apply_lazy( mid_x + 1 , rx , ly , mid_y , val ) ;

        if ( mid_x + 1 <= rx && mid_y + 1 <= ry )
            seg[c3].apply_lazy( mid_x + 1 , rx , mid_y + 1 , ry , val ) ;

        seg[x].lazy = 0 ;
        seg[x].is_lazy = false ;
    }

    void build ( ll x , ll lx , ll rx , ll ly , ll ry , const vector < vector <ll> >& v )
    {
        if ( lx == rx && ly == ry )
        {
            if ( lx < (ll)v.size() && ly < (ll)v[0].size() )
            {
                seg[x].apply_build ( v[lx][ly] ) ;
            }
            return ;
        }

        ll mid_x = ( lx + rx ) / 2 ;
        ll mid_y = ( ly + ry ) / 2 ;

        ll c0 = 4 * x + 1 , c1 = 4 * x + 2 , c2 = 4 * x + 3 , c3 = 4 * x + 4 ;

        if ( lx <= mid_x && ly <= mid_y )
            build ( c0 , lx , mid_x , ly , mid_y , v ) ;

        if ( lx <= mid_x && mid_y + 1 <= ry )
            build ( c1 , lx , mid_x , mid_y + 1 , ry , v ) ;

        if ( mid_x + 1 <= rx && ly <= mid_y )
            build ( c2 , mid_x + 1 , rx , ly , mid_y , v ) ;

        if ( mid_x + 1 <= rx && mid_y + 1 <= ry )
            build ( c3 , mid_x + 1 , rx , mid_y + 1 , ry , v ) ;

        seg[x].merge ( seg[c0] , seg[c1] , seg[c2] , seg[c3] ) ;
    }

    void update ( ll x , ll lx , ll rx , ll ly , ll ry , ll r1 , ll c1 , ll r2 , ll c2 , ll val ) 
    {
        if ( lx > r2 || rx < r1 || ly > c2 || ry < c1 ) return ;
        if ( lx >= r1 && rx <= r2 && ly >= c1 && ry <= c2 )
        {
            seg[x].apply_lazy ( lx , rx , ly , ry , val ) ;
            return ;
        }

        propagate ( x , lx , rx , ly , ry ) ;

        ll mid_x = ( lx + rx ) / 2 ;
        ll mid_y = ( ly + ry ) / 2 ;

        ll c0 = 4 * x + 1 , c1_idx = 4 * x + 2 , c2_idx = 4 * x + 3 , c3 = 4 * x + 4 ;

        if ( lx <= mid_x && ly <= mid_y )
            update ( c0 , lx , mid_x , ly , mid_y , r1 , c1 , r2 , c2 , val ) ;

        if ( lx <= mid_x && mid_y + 1 <= ry )
            update ( c1_idx , lx , mid_x , mid_y + 1 , ry , r1 , c1 , r2 , c2 , val ) ;

        if ( mid_x + 1 <= rx && ly <= mid_y )
            update ( c2_idx , mid_x + 1 , rx , ly , mid_y , r1 , c1 , r2 , c2 , val ) ;

        if ( mid_x + 1 <= rx && mid_y + 1 <= ry )
            update ( c3 , mid_x + 1 , rx , mid_y + 1 , ry , r1 , c1 , r2 , c2 , val ) ;

        seg[x].merge ( seg[c0] , seg[c1_idx] , seg[c2_idx] , seg[c3] ) ;
    }

    node query ( ll x , ll lx , ll rx , ll ly , ll ry , ll r1 , ll c1 , ll r2 , ll c2 )
    {
        if ( lx > r2 || rx < r1 || ly > c2 || ry < c1 ) return node() ;
        if ( lx >= r1 && rx <= r2 && ly >= c1 && ry <= c2 ) return seg[x] ;

        propagate ( x , lx , rx , ly , ry ) ;

        ll mid_x = ( lx + rx ) / 2 ;
        ll mid_y = ( ly + ry ) / 2 ;

        ll c0 = 4 * x + 1 , c1_idx = 4 * x + 2 , c2_idx = 4 * x + 3 , c3 = 4 * x + 4 ;

        node res0 , res1 , res2 , res3 ;

        if ( lx <= mid_x && ly <= mid_y )
            res0 = query ( c0 , lx , mid_x , ly , mid_y , r1 , c1 , r2 , c2 ) ;

        if ( lx <= mid_x && mid_y + 1 <= ry )
            res1 = query ( c1_idx , lx , mid_x , mid_y + 1 , ry , r1 , c1 , r2 , c2 ) ;

        if ( mid_x + 1 <= rx && ly <= mid_y )
            res2 = query ( c2_idx , mid_x + 1 , rx , ly , mid_y , r1 , c1 , r2 , c2 ) ;

        if ( mid_x + 1 <= rx && mid_y + 1 <= ry )
            res3 = query ( c3 , mid_x + 1 , rx , mid_y + 1 , ry , r1 , c1 , r2 , c2 ) ;

        node ans ;
        ans.merge ( res0 , res1 , res2 , res3 ) ;
        return ans ;
    }

public:

    segment_tree_lazy_2d ( vector < vector <ll> >& v )
    {
        ll n = v.size() ;
        ll m = n ? v[0].size() : 0 ;

        while ( sz_r < n ) sz_r *= 2 ;
        while ( sz_c < m ) sz_c *= 2 ;

        seg.assign ( 16 * sz_r * sz_c , node() ) ;

        if ( n > 0 && m > 0 )
        {
            build ( 0 , 0 , sz_r - 1 , 0 , sz_c - 1 , v ) ;
        }
    }

    segment_tree_lazy_2d ( ll n , ll m )
    {
        while ( sz_r < n ) sz_r *= 2 ;
        while ( sz_c < m ) sz_c *= 2 ;

        seg.assign ( 16 * sz_r * sz_c , node() ) ;
    }

    void update ( ll r1 , ll c1 , ll r2 , ll c2 , ll val )
    {
        if ( r1 > r2 || c1 > c2 ) return ;
        update ( 0 , 0 , sz_r - 1 , 0 , sz_c - 1 , r1 , c1 , r2 , c2 , val ) ;
    }

    node query ( ll r1 , ll c1 , ll r2 , ll c2 )
    {
        if ( r1 > r2 || c1 > c2 ) return node() ;
        return query ( 0 , 0 , sz_r - 1 , 0 , sz_c - 1 , r1 , c1 , r2 , c2 ) ;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. مصفوفة إدخال تجريبية 3x4
    vector<vector<ll>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // 2. بناء الـ Tree بالقيم الابتدائية
    segment_tree_lazy_2d seg2d(grid);

    // أ) استعلام (Query): مجموع المستطيل الممتد من (0, 0) إلى (1, 1)
    // الخلايا: (0,0)=1, (0,1)=2, (1,0)=5, (1,1)=6 -> المجموع المفروض = 14
    auto q1 = seg2d.query(0, 0, 1, 1);
    cout << "Sum from (0,0) to (1,1): " << q1.sum << "\n"; // Outputs 14

    // ب) إضافة قيمة 10 على نطاق مستطيل كامل من (0, 1) إلى (2, 2) (Range Update)
    seg2d.update(0, 1, 2, 2, 10);

    // ج) إعادة الاستعلام لنفس المنطقة لمعرفة تأثير التعديل
    auto q2 = seg2d.query(0, 0, 1, 1);
    cout << "Sum from (0,0) to (1,1) after update: " << q2.sum << "\n"; 
    // الخلايا المصابة بالتعديل (0,1) و (1,1) زادت كل منها بـ 10 -> المجموع زاد 20 وصار 34

    // د) تعديل عنصر واحد فقط (مثلاً إضافة 5 للخلية 2, 3)
    seg2d.update(2, 3, 2, 3, 5);

    // هـ) استعلام عن خلية واحدة فقط وهي (2, 3)
    auto q3 = seg2d.query(2, 3, 2, 3);
    cout << "Value at (2,3): " << q3.sum << "\n"; // Original was 12 + 5 = 17

    // و) إنشاء شجرة فارغة بحجم N x M وتحديث نطاق فيها
    ll n = 4, m = 4;
    segment_tree_lazy_2d empty_seg(n, m);
    empty_seg.update(1, 1, 3, 3, 5); // إضافة 5 لجميع خلايا المربع من (1,1) لـ (3,3)
    cout << "Sum of empty seg (0,0) to (3,3): " << empty_seg.query(0, 0, 3, 3).sum << "\n"; // 9 cells * 5 = 45

    return 0;
}
