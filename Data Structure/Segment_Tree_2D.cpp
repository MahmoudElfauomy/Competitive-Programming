#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

class segment_tree_2d
{
private:
    struct node
    {
        // قيمة افتراضية مناسبة للـ Max (في حالة الـ Sum اجعلها 0)
        ll mx = -1e18; 

        void apply(ll val)
        {
            mx = val;
        }

        void merge(const node &L, const node &R)
        {
            mx = max(L.mx, R.mx);
        }
    };

    ll sz_r = 1, sz_c = 1;
    vector<vector<node>> seg;

    void build_y(ll vx, ll lx, ll rx, ll vy, ll ly, ll ry, const vector<vector<ll>> &grid)
    {
        if (ly == ry)
        {
            if (lx == rx)
            {
                if (lx < (ll)grid.size() && ly < (ll)grid[0].size())
                {
                    seg[vx][vy].apply(grid[lx][ly]);
                }
            }
            else
            {
                ll left_x = (2 * vx) + 1;
                ll right_x = (2 * vx) + 2;
                seg[vx][vy].merge(seg[left_x][vy], seg[right_x][vy]);
            }
            return;
        }

        ll mid_y = (ly + ry) / 2;
        ll left_y = (2 * vy) + 1;
        ll right_y = (2 * vy) + 2;

        build_y(vx, lx, rx, left_y, ly, mid_y, grid);
        build_y(vx, lx, rx, right_y, mid_y + 1, ry, grid);

        seg[vx][vy].merge(seg[vx][left_y], seg[vx][right_y]);
    }

    void build_x(ll vx, ll lx, ll rx, const vector<vector<ll>> &grid)
    {
        if (lx != rx)
        {
            ll mid_x = (lx + rx) / 2;
            ll left_x = (2 * vx) + 1;
            ll right_x = (2 * vx) + 2;

            build_x(left_x, lx, mid_x, grid);
            build_x(right_x, mid_x + 1, rx, grid);
        }
        build_y(vx, lx, rx, 0, 0, sz_c - 1, grid);
    }

    void update_y(ll vx, ll lx, ll rx, ll vy, ll ly, ll ry, ll r, ll c, ll val)
    {
        if (ly == ry)
        {
            if (lx == rx)
            {
                seg[vx][vy].apply(val);
            }
            else
            {
                ll left_x = (2 * vx) + 1;
                ll right_x = (2 * vx) + 2;
                seg[vx][vy].merge(seg[left_x][vy], seg[right_x][vy]);
            }
            return;
        }

        ll mid_y = (ly + ry) / 2;
        ll left_y = (2 * vy) + 1;
        ll right_y = (2 * vy) + 2;

        if (c <= mid_y)
            update_y(vx, lx, rx, left_y, ly, mid_y, r, c, val);
        else
            update_y(vx, lx, rx, right_y, mid_y + 1, ry, r, c, val);

        seg[vx][vy].merge(seg[vx][left_y], seg[vx][right_y]);
    }

    void update_x(ll vx, ll lx, ll rx, ll r, ll c, ll val)
    {
        if (lx != rx)
        {
            ll mid_x = (lx + rx) / 2;
            ll left_x = (2 * vx) + 1;
            ll right_x = (2 * vx) + 2;

            if (r <= mid_x)
                update_x(left_x, lx, mid_x, r, c, val);
            else
                update_x(right_x, mid_x + 1, rx, r, c, val);
        }
        update_y(vx, lx, rx, 0, 0, sz_c - 1, r, c, val);
    }

    node query_y(ll vx, ll vy, ll ly, ll ry, ll c1, ll c2)
    {
        if (ly >= c1 && ry <= c2) return seg[vx][vy];
        if (ly > c2 || ry < c1) return node();

        ll mid_y = (ly + ry) / 2;
        ll left_y = (2 * vy) + 1;
        ll right_y = (2 * vy) + 2;

        node L = query_y(vx, left_y, ly, mid_y, c1, c2);
        node R = query_y(vx, right_y, mid_y + 1, ry, c1, c2);

        node ans;
        ans.merge(L, R);
        return ans;
    }

    node query_x(ll vx, ll lx, ll rx, ll r1, ll r2, ll c1, ll c2)
    {
        if (lx >= r1 && rx <= r2)
        {
            return query_y(vx, 0, 0, sz_c - 1, c1, c2);
        }
        if (lx > r2 || rx < r1) return node();

        ll mid_x = (lx + rx) / 2;
        ll left_x = (2 * vx) + 1;
        ll right_x = (2 * vx) + 2;

        node L = query_x(left_x, lx, mid_x, r1, r2, c1, c2);
        node R = query_x(right_x, mid_x + 1, rx, r1, r2, c1, c2);

        node ans;
        ans.merge(L, R);
        return ans;
    }

public:
    // Constructor 1: Initialization using 2D Vector
    segment_tree_2d(const vector<vector<ll>> &grid)
    {
        ll n = grid.size();
        ll m = n ? grid[0].size() : 0;

        while (sz_r < n) sz_r *= 2;
        while (sz_c < m) sz_c *= 2;

        seg.assign(2 * sz_r, vector<node>(2 * sz_c, node()));
        if (n > 0 && m > 0)
        {
            build_x(0, 0, sz_r - 1, grid);
        }
    }

    // Constructor 2: Initialization with empty size N x M
    segment_tree_2d(ll n, ll m)
    {
        while (sz_r < n) sz_r *= 2;
        while (sz_c < m) sz_c *= 2;

        seg.assign(2 * sz_r, vector<node>(2 * sz_c, node()));
    }

    // Update single cell (r, c) to val
    void update(ll r, ll c, ll val)
    {
        update_x(0, 0, sz_r - 1, r, c, val);
    }

    node query(ll r1, ll c1, ll r2, ll c2)
    {
        if (r1 > r2 || c1 > c2) return node();
        return query_x(0, 0, sz_r - 1, r1, r2, c1, c2) ;
    }
};

int main()
{
    vector<vector<ll>> grid = {
        {1, 3, 2, 5},
        {8, 4, 9, 1},
        {2, 6, 7, 3}
    };

    segment_tree_2d seg2d(grid);

    // 1. استعلام عن مستطيل يبدأ من (r1=0, c1=1) وينتهي عند (r2=1, c2=3)
    // النقطة الأولى: (0, 1) | النقطة الثانية: (1, 3)
    auto res1 = seg2d.query(0, 1, 1, 3);
    cout << "Max in range (0,1) to (1,3): " << res1.mx << "\n"; // Output: 9

    // 2. استعلام عن خلية واحدة فقط وهي الخلية (2, 1)
    // النقطة الأولى: (2, 1) | النقطة الثانية: (2, 1)
    auto res2 = seg2d.query(2, 1, 2, 1);
    cout << "Value at (2, 1): " << res2.mx << "\n"; // Output: 6

    seg2d.update ( 0 , 0 , 100 ) ; 
    cout << "new mx : " << seg2d.query ( 0 , 0 , 2 , 3 ).mx << endl ;



    // هـ) إنشاء Segment Tree فاضية بالحجم N x M وتعبئتها يدوياً
    ll n = 5, m = 5;
    segment_tree_2d empty_seg(n, m);
    empty_seg.update(2, 3, 100); // وضع قيمة في المكان (2, 3)
    cout << "Max in empty seg (0..0, 4..4): " << empty_seg.query(0, 0, 4, 4).mx << "\n"; // Outputs 100
    cout << "Max in empty seg (0..2, 0..2): " << empty_seg.query(0, 2, 0, 2).mx << "\n"; // Outputs -1e18

    return 0;
}
