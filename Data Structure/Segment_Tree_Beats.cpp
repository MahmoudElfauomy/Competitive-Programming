#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SegmentTreeBeats {
private:
    static constexpr long long INF = 2e18;

    struct Node {
        long long sum, mx, secMx, mxCnt;
        long long mn, secMn, mnCnt;
        long long lazyAdd, lazySet;
        long long len; // Number of valid elements in this node
        bool hasLazySet;

        // Constructor for empty / dummy nodes
        Node() 
        {
            sum = 0;
            mx = -INF; secMx = -INF; mxCnt = 0;
            mn = INF; secMn = INF; mnCnt = 0;
            lazyAdd = 0; lazySet = 0; 
            len = 0; hasLazySet = false;
        }

        // Constructor for real leaf nodes
        Node(long long val) {
            sum = mx = mn = val;
            secMx = -INF; secMn = INF;
            mxCnt = mnCnt = 1;
            lazyAdd = lazySet = 0; 
            len = 1; hasLazySet = false;
        }
    };

    int sz;
    vector<Node> seg;

    Node merge(const Node& a, const Node& b) {
        if (a.len == 0) return b; // Ignore empty nodes
        if (b.len == 0) return a; // Ignore empty nodes

        Node ret;
        ret.len = a.len + b.len;
        ret.sum = a.sum + b.sum;

        // Merge Max properties
        if (a.mx > b.mx) {
            ret.mx = a.mx; ret.mxCnt = a.mxCnt;
            ret.secMx = max(a.secMx, b.mx);
        } else if (a.mx < b.mx) {
            ret.mx = b.mx; ret.mxCnt = b.mxCnt;
            ret.secMx = max(a.mx, b.secMx);
        } else {
            ret.mx = a.mx; ret.mxCnt = a.mxCnt + b.mxCnt;
            ret.secMx = max(a.secMx, b.secMx);
        }

        // Merge Min properties
        if (a.mn < b.mn) {
            ret.mn = a.mn; ret.mnCnt = a.mnCnt;
            ret.secMn = min(a.secMn, b.mn);
        } else if (a.mn > b.mn) {
            ret.mn = b.mn; ret.mnCnt = b.mnCnt;
            ret.secMn = min(a.mn, b.secMn);
        } else {
            ret.mn = a.mn; ret.mnCnt = a.mnCnt + b.mnCnt;
            ret.secMn = min(a.secMn, b.secMn);
        }

        return ret;
    }

    void push_set(int node, long long val) {
        if (seg[node].len == 0) return;
        seg[node].sum = val * seg[node].len;
        seg[node].mx = seg[node].mn = val;
        seg[node].secMx = -INF;
        seg[node].secMn = INF;
        seg[node].mxCnt = seg[node].mnCnt = seg[node].len;
        seg[node].lazyAdd = 0;
        seg[node].lazySet = val;
        seg[node].hasLazySet = true;
    }

    void push_add(int node, long long val) {
        if (seg[node].len == 0 || val == 0) return;
        if (seg[node].hasLazySet) {
            push_set(node, seg[node].lazySet + val);
            return;
        }
        seg[node].sum += val * seg[node].len;
        seg[node].mx += val;
        if (seg[node].secMx != -INF) seg[node].secMx += val;
        seg[node].mn += val;
        if (seg[node].secMn != INF) seg[node].secMn += val;
        seg[node].lazyAdd += val;
    }

    void push_min(int node, long long val) {
        if (seg[node].len == 0 || val >= seg[node].mx) return;
        if (seg[node].hasLazySet) seg[node].lazySet = val;
        
        seg[node].sum -= (seg[node].mx - val) * seg[node].mxCnt;
        if (seg[node].mn == seg[node].mx) seg[node].mn = val;
        if (seg[node].secMn == seg[node].mx) seg[node].secMn = val;
        seg[node].mx = val;
    }

    void push_max(int node, long long val) {
        if (seg[node].len == 0 || val <= seg[node].mn) return;
        if (seg[node].hasLazySet) seg[node].lazySet = val;

        seg[node].sum += (val - seg[node].mn) * seg[node].mnCnt;
        if (seg[node].mx == seg[node].mn) seg[node].mx = val;
        if (seg[node].secMx == seg[node].mn) seg[node].secMx = val;
        seg[node].mn = val;
    }

    void propagate(int node, int l, int r) {
        if (l == r) return;
        int L = 2 * node + 1;
        int R = 2 * node + 2;

        if (seg[node].hasLazySet) {
            push_set(L, seg[node].lazySet);
            push_set(R, seg[node].lazySet);
            seg[node].hasLazySet = false;
        } else {
            if (seg[node].lazyAdd != 0) {
                push_add(L, seg[node].lazyAdd);
                push_add(R, seg[node].lazyAdd);
                seg[node].lazyAdd = 0;
            }
            push_min(L, seg[node].mx);
            push_min(R, seg[node].mx);
            push_max(L, seg[node].mn);
            push_max(R, seg[node].mn);
        }
    }

    void build(int l, int r, int node, const vector<long long>& v) {
        if (l == r) {
            if (l < (int)v.size()) seg[node] = Node(v[l]);
            else seg[node] = Node(); // Dummy node perfectly handled
            return;
        }
        int mid = l + (r - l) / 2;
        build(l, mid, 2 * node + 1, v);
        build(mid + 1, r, 2 * node + 2, v);
        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
    }

    void updateAdd(int l, int r, int node, int lx, int rx, long long val) {
        if (l > rx || r < lx || seg[node].len == 0) return;
        if (l >= lx && r <= rx) {
            push_add(node, val);
            return;
        }
        propagate(node, l, r);
        int mid = l + (r - l) / 2;
        updateAdd(l, mid, 2 * node + 1, lx, rx, val);
        updateAdd(mid + 1, r, 2 * node + 2, lx, rx, val);
        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
    }

    void updateSet(int l, int r, int node, int lx, int rx, long long val) {
        if (l > rx || r < lx || seg[node].len == 0) return;
        if (l >= lx && r <= rx) {
            push_set(node, val);
            return;
        }
        propagate(node, l, r);
        int mid = l + (r - l) / 2;
        updateSet(l, mid, 2 * node + 1, lx, rx, val);
        updateSet(mid + 1, r, 2 * node + 2, lx, rx, val);
        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
    }

    void updateMin(int l, int r, int node, int lx, int rx, long long val) {
        if (l > rx || r < lx || seg[node].len == 0 || seg[node].mx <= val) return;
        if (l >= lx && r <= rx && val > seg[node].secMx) {
            push_min(node, val);
            return;
        }
        propagate(node, l, r);
        int mid = l + (r - l) / 2;
        updateMin(l, mid, 2 * node + 1, lx, rx, val);
        updateMin(mid + 1, r, 2 * node + 2, lx, rx, val);
        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
    }

    void updateMax(int l, int r, int node, int lx, int rx, long long val) {
        if (l > rx || r < lx || seg[node].len == 0 || seg[node].mn >= val) return;
        if (l >= lx && r <= rx && val < seg[node].secMn) {
            push_max(node, val);
            return;
        }
        propagate(node, l, r);
        int mid = l + (r - l) / 2;
        updateMax(l, mid, 2 * node + 1, lx, rx, val);
        updateMax(mid + 1, r, 2 * node + 2, lx, rx, val);
        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
    }

    long long querySum(int l, int r, int node, int lx, int rx) {
        if (l > rx || r < lx || seg[node].len == 0) return 0;
        if (l >= lx && r <= rx) return seg[node].sum;
        propagate(node, l, r);
        int mid = l + (r - l) / 2;
        return querySum(l, mid, 2 * node + 1, lx, rx) + querySum(mid + 1, r, 2 * node + 2, lx, rx);
    }

    long long queryMin(int l, int r, int node, int lx, int rx) {
        if (l > rx || r < lx || seg[node].len == 0) return INF;
        if (l >= lx && r <= rx) return seg[node].mn;
        propagate(node, l, r);
        int mid = l + (r - l) / 2;
        return min(queryMin(l, mid, 2 * node + 1, lx, rx), queryMin(mid + 1, r, 2 * node + 2, lx, rx));
    }

    long long queryMax(int l, int r, int node, int lx, int rx) {
        if (l > rx || r < lx || seg[node].len == 0) return -INF;
        if (l >= lx && r <= rx) return seg[node].mx;
        propagate(node, l, r);
        int mid = l + (r - l) / 2;
        return max(queryMax(l, mid, 2 * node + 1, lx, rx), queryMax(mid + 1, r, 2 * node + 2, lx, rx));
    }

public:
    SegmentTreeBeats(const vector<long long>& v) {
        int n = v.size();
        sz = 1;
        while (sz < n) sz <<= 1;
        seg.resize(sz << 1);
        build(0, sz - 1, 0, v);
    }

    void updateAdd(int l, int r, long long val) { updateAdd(0, sz - 1, 0, l, r, val); }
    void updateSet(int l, int r, long long val) { updateSet(0, sz - 1, 0, l, r, val); }
    void updateMin(int l, int r, long long val) { updateMin(0, sz - 1, 0, l, r, val); }
    void updateMax(int l, int r, long long val) { updateMax(0, sz - 1, 0, l, r, val); }

    long long queryMax(int l, int r) { return queryMax(0, sz - 1, 0, l, r); }
    long long queryMin(int l, int r) { return queryMin(0, sz - 1, 0, l, r); }
    long long querySum(int l, int r) { return querySum(0, sz - 1, 0, l, r); }
};

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // 1. Initialize the array and build the tree
    // Note: The template uses 0-based indexing and closed ranges [l, r]
    vector<long long> v = {1, 5, 2, 8, 3, 7, 4, 6};
    SegmentTreeBeats st(v);

    // 2. Basic Queries
    cout << "--- Initial Queries ---" << "\n";
    cout << "Sum [0, 7] = " << st.querySum(0, 7) << "\n"; // Sum of elements in range [0, 7]
    cout << "Min [0, 7] = " << st.queryMin(0, 7) << "\n"; // Minimum element in range [0, 7]
    cout << "Max [0, 7] = " << st.queryMax(0, 7) << "\n"; // Maximum element in range [0, 7]
    cout << "\n";

    // 3. Updates

    // A. Range Add: Add a fixed value to all elements in a range
    // Syntax: updateAdd(l, r, val)
    st.updateAdd(1, 4, 10) ; // Add 10 to elements from index 1 to 4

    // B. Range Set: Assign a fixed value to all elements in a range
    // Syntax: updateSet(l, r, val)
    st.updateSet(2, 5, 50) ; // Set elements from index 2 to 5 to 50

    // C. Range Chmin (Min Update): If an element > val, set it to val
    // Syntax: updateMin(l, r, val)
    st.updateMin(0, 7, 30) ; // Cap elements in the range so none exceed 30

    // D. Range Chmax (Max Update): If an element < val, set it to val
    // Syntax: updateMax(l, r, val)
    st.updateMax(0, 7, 5) ;  // Ensure elements in the range are at least 5

    // 4. Queries after updates
    cout << "--- Queries After Updates ---" << "\n";
    cout << "Sum [0, 7] = " << st.querySum(0, 7) << "\n";
    cout << "Min [0, 7] = " << st.queryMin(0, 7) << "\n";
    cout << "Max [0, 7] = " << st.queryMax(0, 7) << "\n";
    return 0;
}
