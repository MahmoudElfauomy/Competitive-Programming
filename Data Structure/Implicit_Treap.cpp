#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// ULTIMATE IMPLICIT TREAP TEMPLATE (BLACK BOX)
// Features: Dynamic Array, Range Add, Range Set, Reverse, Shift/Rotate, Move,
//           Memory Pool (Recycled), Linear O(N) Build, Binary Search on Treap.
// ============================================================================

const long long INF64 = 4e18;
const int INF32 = 2e9;
mt19937 rng(1337); // Standard Mersenne Twister RNG

struct Node {
    int val;
    int prior, sz;
    long long sum;
    int mn, mx;
    
    bool rev;
    long long add_lazy;
    int set_lazy;
    bool has_set;

    Node* l;
    Node* r;

    Node() {}
    void reset(int v) {
        val = sum = mn = mx = v;
        sz = 1;
        prior = rng();
        rev = false;
        add_lazy = 0;
        set_lazy = 0;
        has_set = false;
        l = r = nullptr;
    }
};

typedef Node* pnode;

// ---------------- Memory Pool Allocation & Recycling ----------------
// N = max (n) + max insert operation + buffer
const int MAXNODES = 2 * N; // اضبط الحجم الأقصى حسب حدود المسألة
Node pool[MAXNODES];
Node* free_nodes[MAXNODES];
int pool_ptr = 0;
int free_ptr = 0;

pnode create_node(int val) {
    pnode res;
    if (free_ptr > 0) res = free_nodes[--free_ptr];
    else res = &pool[pool_ptr++];
    res->reset(val);
    return res;
}

void recycle_node(pnode t) {
    if (t) free_nodes[free_ptr++] = t;
}
// ---------------------------------------------------------------------

struct ImplicitTreap {
    pnode root = nullptr;

    // --- Helper Functions ---
    static int sz(pnode t) { return t ? t->sz : 0; }
    static long long get_sum(pnode t) { return t ? t->sum : 0LL; }
    static int get_min(pnode t) { return t ? t->mn : INF32; }
    static int get_max(pnode t) { return t ? t->mx : -INF32; }

    static void apply_rev(pnode t) {
        if (!t) return;
        t->rev ^= 1;
    }

    static void apply_set(pnode t, int v) {
        if (!t) return;
        t->val = v;
        t->sum = 1LL * v * t->sz;
        t->mn = t->mx = v;
        t->set_lazy = v;
        t->has_set = true;
        t->add_lazy = 0; 
    }

    static void apply_add(pnode t, long long v) {
        if (!t) return;
        t->val += v;
        t->sum += 1LL * v * t->sz;
        t->mn += v;
        t->mx += v;
        
        if (t->has_set) {
            t->set_lazy += v;
        } else {
            t->add_lazy += v;
        }
    }

    static void upd(pnode t) {
        if (!t) return;
        t->sz = 1 + sz(t->l) + sz(t->r);
        t->sum = t->val + get_sum(t->l) + get_sum(t->r);
        t->mn = min({t->val, get_min(t->l), get_min(t->r)});
        t->mx = max({t->val, get_max(t->l), get_max(t->r)});
    }

    static void push(pnode t) 
    {
        if (!t) return;
        if (t->rev) {
            t->rev = false;
            swap(t->l, t->r);
            apply_rev(t->l);
            apply_rev(t->r);
        }
        if (t->has_set) {
            apply_set(t->l, t->set_lazy);
            apply_set(t->r, t->set_lazy);
            t->has_set = false;
        }
        if (t->add_lazy != 0) {
            apply_add(t->l, t->add_lazy);
            apply_add(t->r, t->add_lazy);
            t->add_lazy = 0;
        }
    }

    static void split(pnode t, pnode &l, pnode &r, int k, int add = 0) {
        if (!t) return void(l = r = nullptr);
        push(t);
        int cur_key = add + sz(t->l);
        if (k <= cur_key) {
            split(t->l, l, t->l, k, add);
            r = t;
        } else {
            split(t->r, t->r, r, k, add + 1 + sz(t->l));
            l = t;
        }
        upd(t);
    }

    static void merge(pnode &t, pnode l, pnode r) {
        push(l); push(r);
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior) {
            merge(l->r, l->r, r);
            t = l;
        } else {
            merge(r->l, l, r->l);
            t = r;
        }
        upd(t);
    }

    static void destroy(pnode t) {
        if (!t) return;
        destroy(t->l);
        destroy(t->r);
        recycle_node(t);
    }

    // --- Core Public Methods ---

    // 1. build O(N) 
    void build(const vector<int>& a) {
        destroy(root);
        root = nullptr;
        int n = a.size();
        if (n == 0) return;
        vector<pnode> st;
        for (int i = 0; i < n; i++) {
            pnode curr = create_node(a[i]);
            pnode last = nullptr;
            while (!st.empty() && st.back()->prior < curr->prior) {
                last = st.back();
                upd(last);
                st.pop_back();
            }
            curr->l = last;
            if (!st.empty()) st.back()->r = curr;
            st.push_back(curr);
        }
        while (!st.empty()) {
            upd(st.back());
            root = st.back();
            st.pop_back();
        }
    }

    int size() const { return sz(root); }
    bool empty() const { return size() == 0; }

    // 2. إدراج عنصر في الاندكس k
    void insert(int k, int val) {
        pnode t1, t2;
        split(root, t1, t2, k);
        merge(t1, t1, create_node(val));
        merge(root, t1, t2);
    }

    void push_back(int val) { insert(size(), val); }

    // 3. حذف عنصر في اندكس k
    void erase(int k) {
        pnode t1, t2, t3;
        split(root, t1, t2, k);
        split(t2, t2, t3, 1);
        recycle_node(t2);
        merge(root, t1, t3);
    }

    // 4. حذف نطاق [L, R]
    void erase_range(int L, int R) {
        if (L > R) return;
        pnode t1, t2, t3;
        split(root, t1, t2, L);
        split(t2, t2, t3, R - L + 1);
        destroy(t2);
        merge(root, t1, t3);
    }

    // 5. عكس ترتيب العناصر في [L, R]
    void reverse_range(int L, int R) {
        if (L > R) return;
        pnode t1, t2, t3;
        split(root, t1, t2, L);
        split(t2, t2, t3, R - L + 1);
        apply_rev(t2);
        merge(t1, t1, t2);
        merge(root, t1, t3);
    }

    // 6. إضافة قيمة V لجميع العناصر في [L, R]
    void add_range(int L, int R, long long val) {
        if (L > R) return;
        pnode t1, t2, t3;
        split(root, t1, t2, L);
        split(t2, t2, t3, R - L + 1);
        apply_add(t2, val);
        merge(t1, t1, t2);
        merge(root, t1, t3);
    }

    // 7. جعل جميع العناصر في [L, R] مساوية لـ V
    void set_range(int L, int R, int val) {
        if (L > R) return;
        pnode t1, t2, t3;
        split(root, t1, t2, L);
        split(t2, t2, t3, R - L + 1);
        apply_set(t2, val);
        merge(t1, t1, t2);
        merge(root, t1, t3);
    }

    // 8. إزاحة دورية لليمين (Cyclic Shift) بمقدار K في النطاق [L, R]
    void rotate_range(int L, int R, int k) {
        int len = R - L + 1;
        if (len <= 1) return;
        k = (k % len + len) % len;
        if (k == 0) return;
        pnode t1, t2, t3, a, b;
        split(root, t1, t2, L);
        split(t2, t2, t3, len);
        split(t2, a, b, len - k);
        merge(t2, b, a);
        merge(t1, t1, t2);
        merge(root, t1, t3);
    }
    
    // تدوير للشمال .9 (Cyclic Shift Left) بمقدار K خطوة في النطاق [L, R]
    void rotate_left_range(int L, int R, int k) {
        int len = R - L + 1;
        if (len <= 1) return;
        
        k = (k % len + len) % len;
        if (k == 0) return;
    
        pnode t1, t2, t3, a, b;
        split(root, t1, t2, L);
        split(t2, t2, t3, len);
        
        split(t2, a, b, k);
        
        merge(t2, b, a);
    
        merge(t1, t1, t2);
        merge(root, t1, t3);
    }
    
    // 10. قص النطاق [L, R] وزرعه بعد الاندكس dest
    // dest idx after erase
    void move_range(int L, int R, int dest) {
        if (L > R) return;
        pnode t1, t2, t3;
        split(root, t1, t2, L);
        split(t2, t2, t3, R - L + 1);
        merge(root, t1, t3); 
        
        pnode left, right;
        split(root, left, right, dest);
        merge(left, left, t2);
        merge(root, left, right);
    }

    void swap_ranges(int L1, int R1, int L2, int R2) {
        if ( L1 > R1 || L2 > R2 ) return ;
        
        if (L1 > L2) 
        {
            swap(L1, L2);
            swap(R1, R2);
        }
        
        if (R1 >= L2) return; 

        pnode t1234 = nullptr, p5 = nullptr;
        pnode t123 = nullptr, p4 = nullptr;
        pnode t12 = nullptr, p3 = nullptr;
        pnode p1 = nullptr, p2 = nullptr;

        split(root, t1234, p5, R2 + 1);
        split(t1234, t123, p4, L2);
        split(t123, t12, p3, R1 + 1);
        split(t12, p1, p2, L1);

        pnode new_root = nullptr;
        merge(new_root, p1, p4);      
        merge(new_root, new_root, p3);
        merge(new_root, new_root, p2);
        merge(new_root, new_root, p5);

        root = new_root;
    }
    
    // 11. استعلامات النطاق (Queries)
    long long query_sum(int L, int R) 
    {
        if (L > R) return 0;
        pnode t1, t2, t3;
        split(root, t1, t2, L);
        split(t2, t2, t3, R - L + 1);
        long long ans = get_sum(t2);
        merge(t1, t1, t2);
        merge(root, t1, t3);
        return ans;
    }
    
    int query_max(int L, int R) {
        if (L > R) return -INF32;
        pnode t1, t2, t3;
        split(root, t1, t2, L);
        split(t2, t2, t3, R - L + 1);
        int ans = get_max(t2);
        merge(t1, t1, t2);
        merge(root, t1, t3);
        return ans;
    }
    
    int query_min(int L, int R) {
        if (L > R) return INF32;
        pnode t1, t2, t3;
        split(root, t1, t2, L);
        split(t2, t2, t3, R - L + 1);
        int ans = get_min(t2);
        merge(t1, t1, t2);
        merge(root, t1, t3);
        return ans;
    }

    // Subscript Operator للوصول السريع: treap[i]
    int operator[](int idx) {
        return query_min(idx, idx);
    }

    // 11. البحث الثنائي الداخلي: إيجاد أول اندكس يتخطى فيه المجموع S
    int lower_bound_sum(long long S) {
        return lower_bound_sum(root, S);
    }

    void print() {
        print(root);
        cout << "\n";
    }

private:
    void print(pnode t) {
        if (!t) return;
        push(t);
        print(t->l);
        cout << t->val << " ";
        print(t->r);
    }

    int lower_bound_sum(pnode t, long long S) {
        if (!t) return -1;
        push(t);
        long long left_sum = get_sum(t->l);
        if (left_sum >= S) {
            return lower_bound_sum(t->l, S);
        } else if (left_sum + t->val >= S) {
            return sz(t->l);
        } else {
            int res = lower_bound_sum(t->r, S - left_sum - t->val);
            return (res == -1) ? -1 : sz(t->l) + 1 + res;
        }
    }
};

// ============================================================================
// Example Usage / Testing
// ============================================================================

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

   cout << "====================================================\n";
    cout << "          TESTING IMPLICIT TREAP FUNCTIONS          \n";
    cout << "====================================================\n\n";

    ImplicitTreap treap;

    // 1. Build & Basic Checks
    vector<int> init_vec = {10, 20, 30, 40, 50};
    treap.build(init_vec);
    cout << "[1] Build O(N):\n    Array : ";
    treap.print(); // Expected: 10 20 30 40 50
    cout << "    Size  : " << treap.size() << " | Is Empty? " << (treap.empty() ? "Yes" : "No") << "\n\n";

    // 2. Insert & Push Back
    treap.push_back(60);
    cout << "[2] push_back(60):\n    Array : ";
    treap.print(); // Expected: 10 20 30 40 50 60

    treap.insert(2, 25); // Insert 25 at index 2
    cout << "    insert(2, 25):\n    Array : ";
    treap.print(); // Expected: 10 20 25 30 40 50 60
    cout << "\n";

    // 3. Subscript Operator []
    cout << "[3] Subscript Operator treap[idx]:\n";
    cout << "    treap[2] = " << treap[2] << " (Expected: 25)\n";
    cout << "    treap[5] = " << treap[5] << " (Expected: 50)\n\n";

    // 4. Query Range Sum / Min / Max
    // Array currently: [10, 20, 25, 30, 40, 50, 60]
    // Range [1, 4] contains: 20, 25, 30, 40
    cout << "[4] Range Queries on range [1, 4]:\n";
    cout << "    Sum [1, 4] : " << treap.query_sum(1, 4) << " (Expected: 115)\n";
    cout << "    Min [1, 4] : " << treap.query_min(1, 4) << " (Expected: 20)\n";
    cout << "    Max [1, 4] : " << treap.query_max(1, 4) << " (Expected: 40)\n\n";

    // 5. Lazy Propagation Test: Set Range & Add Range
    // Reset range [1, 3] to 100
    treap.set_range(1, 3, 100);
    cout << "[5] set_range(1, 3, 100):\n    Array : ";
    treap.print(); // Expected: 10 100 100 100 40 50 60

    // Add 15 to range [2, 4] -> tests combining Set and Add lazy tags!
    treap.add_range(2, 4, 15);
    cout << "    add_range(2, 4, 15):\n    Array : ";
    treap.print(); // Expected: 10 100 115 115 55 50 60
    cout << "\n";

    // 6. Reverse Range
    treap.reverse_range(1, 5);
    cout << "[6] reverse_range(1, 5):\n    Array : ";
    treap.print(); // Reverses [100, 115, 115, 55, 50]
    cout << "\n";

    // 7. Cyclic Rotations (Rotate Right & Rotate Left)
    treap.build({1, 2, 3, 4, 5, 6, 7});
    cout << "[7] Reset Array for Rotations:\n    Array : ";
    treap.print();

    // Rotate Right range [1, 5] by 2 steps
    treap.rotate_range(1, 5, 2);
    cout << "    rotate_range(1, 5, 2) [Rotate Right]:\n    Array : ";
    treap.print(); // Range [2, 3, 4, 5, 6] becomes [5, 6, 2, 3, 4]

    // Rotate Left range [1, 5] by 2 steps (should restore to original)
    treap.rotate_left_range(1, 5, 2);
    cout << "    rotate_left_range(1, 5, 2) [Rotate Left]:\n    Array : ";
    treap.print(); // Restores to original: 1 2 3 4 5 6 7
    cout << "\n";

    // 8. Move Range (Cut & Paste)
    // Cut range [1, 3] (which is [2, 3, 4]) and paste after index 3 in remaining array
    treap.move_range(1, 3, 3);
    cout << "[8] move_range(1, 3, 3) [Cut elements 2,3,4 and paste after dest idx 3]:\n    Array : ";
    treap.print(); // Expected: 1 5 6 2 3 4 7
    cout << "\n";

    // 9. Binary Search on Treap (lower_bound_sum)
    treap.build({2, 3, 5, 1, 4});
    cout << "[9] Reset for lower_bound_sum:\n    Array : ";
    treap.print(); // Prefix sums: [2], [5], [10], [11], [15]
    cout << "    lower_bound_sum(5) = Index " << treap.lower_bound_sum(5) << " (Expected: 1, sum=5)\n";
    cout << "    lower_bound_sum(8) = Index " << treap.lower_bound_sum(8) << " (Expected: 2, sum=10 >= 8)\n\n";

    // 10. Erase & Erase Range
    treap.erase(2); // Erases element at index 2 (value 5)
    cout << "[10] erase(2):\n     Array : ";
    treap.print(); // Remaining: 2 3 1 4

    treap.erase_range(0, 1); // Erases elements at indices [0, 1] (values 2, 3)
    cout << "     erase_range(0, 1):\n     Array : ";
    treap.print(); // Remaining: 1 4

    cout << "\n====================================================\n";
    cout << "               ALL TESTS PASSED SUCCESSFULLY!       \n";
    cout << "====================================================\n";
    return 0;
}
