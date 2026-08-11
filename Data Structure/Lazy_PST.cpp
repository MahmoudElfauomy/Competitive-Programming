#include "bits/stdc++.h"
using namespace std;

/* you can set opt to true if update is (assign or single point update)*/
template <class node, int64_t LX = INT_MIN, int64_t RX = INT_MAX, bool opt = false>
class seg_tree {
private:
    vector<node> seg = vector<node>(1);
    vector<int> roots = {0}, left = {0}, right = {0};

    void create_node(int &x) {
        if (x && opt) return;
        int y = x;
        x = seg.size();
        seg.push_back(seg[y]);
        left.push_back(left[y]);
        right.push_back(right[y]);
    }

    template <class... M>
    int update(int x, int64_t lx, int64_t rx, int64_t l, int64_t r, const M &...val) {
        if (rx < l || r < lx) return x;

        int nd = (opt ? 0 : x);
        if (l <= lx && rx <= r) {
            create_node(nd);
            seg[nd].apply(lx, rx, val...);
            return nd;
        }

        int64_t mid = lx + rx >> 1;
        create_node(left[x]);
        create_node(right[x]);
        seg[x].propagate(seg[left[x]], seg[right[x]], lx, rx, mid);

        create_node(nd);
        left[nd] = update(left[x], lx, mid, l, r, val...);
        right[nd] = update(right[x], mid + 1, rx, l, r, val...);
        seg[nd].merge(seg[left[nd]], seg[right[nd]]);

        return nd;
    }

    node query(int x, int64_t lx, int64_t rx, int64_t l, int64_t r) {
        if (l <= lx && rx <= r) {
            return seg[x];
        }

        int64_t mid = lx + rx >> 1;
        create_node(left[x]);
        create_node(right[x]);
        seg[x].propagate(seg[left[x]], seg[right[x]], lx, rx, mid);

        if (r < mid + 1) {
            return query(left[x], lx, mid, l, r);
        }
        if (mid < l) {
            return query(right[x], mid + 1, rx, l, r);
        }
        node ret;
        ret.merge(query(left[x], lx, mid, l, r), query(right[x], mid + 1, rx, l, r));
        return ret;
    }

    pair<int, node> find(int x, int64_t lx, int64_t rx, node *last, int64_t l, int64_t r, int dir, const auto &F) {
        if (l <= lx && rx <= r) {
            node cur_node = seg[x];
            if (last) {
                dir ? cur_node.merge(*last, seg[x]) : cur_node.merge(seg[x], *last);
            }
            if (!F(cur_node)) return {-1, cur_node};
            if (lx == rx) return {lx, cur_node};
        }

        int64_t mid = lx + rx >> 1;
        create_node(left[x]);
        create_node(right[x]);
        seg[x].propagate(seg[left[x]], seg[right[x]], lx, rx, mid);

        if (r < mid + 1) {
            return find(left[x], lx, mid, last, l, r, dir, F);
        }
        if (mid < l) {
            return find(right[x], mid + 1, rx, last, l, r, dir, F);
        }
        auto [idx, nd] = (dir ? find(left[x], lx, mid, last, l, r, dir, F) : find(right[x], mid + 1, rx, last, l, r, dir, F));
        if (~idx) return {idx, nd};
        return dir ? find(right[x], mid + 1, rx, &nd, l, r, dir, F) : find(left[x], lx, mid, &nd, l, r, dir, F);
    }

public:
    seg_tree() { create_node(roots[0]); }

    int cur_time() { return roots.size() - 1; }

    void push_back(int time) {
        roots.push_back(roots[time]);
    }

    template <class... M>
    void update(int time, int64_t l, int64_t r, const M &...val) {
        roots[time] = update(roots[time], LX, RX, l, r, val...);
    }

    node query(int time, int64_t l, int64_t r) {
        return query(roots[time], LX, RX, l, r);
    }

    int find_first(int time, int64_t l, int64_t r, const auto &F) {
        return find(roots[time], LX, RX, nullptr, l, r, 1, F).first;
    }

    int find_last(int time, int64_t l, int64_t r, const auto &F) {
        return find(roots[time], LX, RX, nullptr, l, r, 0, F).first;
    }
};

struct node {
    int64_t cur_node = -1, lazy = -2;

    void apply(int64_t lx, int64_t rx, int64_t val) {
        cur_node = val;
        lazy = cur_node;
    }

    void merge(const node &a, const node &b) {
        // TO-DO
    }

    void propagate(node &left, node &right, int64_t lx, int64_t rx, int64_t mid) {
        if (lazy != -2) {
            left.apply(lx, mid, lazy);
            right.apply(mid + 1, rx, lazy);
            lazy = -2;
        }
    }
};

void ac() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> g(n + 1);
    for (int i = 1, a, b; i < n; ++i) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<vector<pair<int, int>>> q1(n + 1), q2(n + 1);
    int op, x, t1, t2, id = 0;
    while (q--) {
        cin >> op >> x >> t1;
        if (op == 1) {
            cin >> t2;
            q1[x].emplace_back(t1, t2);
        }
        else {
            q2[x].emplace_back(t1, id);
            ++id;
        }
    }

    vector<int> ans(id), time(n + 1);
    seg_tree<node, 0, (int)1E6 + 5, false> st;
    function<void(int, int)> dfs = [&](int u, int p) {
        st.push_back(time[p]);
        time[u] = st.cur_time();
        for (auto &[t1, t2] : q1[u]) {
            st.update(time[u], t1, t2, u);
        }
        for (auto &[t, q_id] : q2[u]) {
            ans[q_id] = st.query(time[u], t, t).cur_node;
        }

        for (auto ch : g[u]) {
            if (ch != p) {
                dfs(ch, u);
            }
        }
    };
    time[0] = 0;
    dfs(1, 0);
    for (auto it : ans) {
        cout << it << '\n';
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    if (fopen("in.txt", "r")) {
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    }
    int T = 1;
    cin >> T;
    while (T--) {
        ac();
        if (T) {
            cout << '\n';
        }
    }
}
