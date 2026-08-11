#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct PalindromicTree {
    static const int ALPHABET_SIZE = 26;

    struct Node {
        int next[ALPHABET_SIZE]; 
        int len;        // [ناتج]: طول الـ Palindrome
        int link;       
        int cnt;        // [ناتج]: عدد مرات تكرار الـ Palindrome في النص الكامل
        int num;        // [ناتج]: عدد الـ Palindromic Suffixes اللي بتنتهي عند النود دي
        int first_idx;  // [ناتج]: آخر index انتهى عنده الـ Palindrome ده أول مرة ظهر فيها

        Node(int l = 0, int lk = 0, int idx = -1) 
            : len(l), link(lk), cnt(0), num(0), first_idx(idx) {
            fill(next, next + ALPHABET_SIZE, 0);
        }
    };

    vector<Node> tree;
    string s;
    int last, sz;

    PalindromicTree() { clear(); }

    void clear() {
        tree.clear();
        s = "";
        tree.push_back(Node());        
        tree.push_back(Node(-1, 1));   
        tree.push_back(Node(0, 1));    
        last = 2;
        sz = 2;
    }

    int get_link(int v) {
        int i = (int)s.size() - 1;
        while (i - 1 - tree[v].len < 0 || s[i - 1 - tree[v].len] != s[i]) {
            v = tree[v].link;
        }
        return v;
    }

    // [Input]: إضافة حرف للنص
    // [Output]: ترجع true لو ظهر Palindrome جديد بسبب الحرف ده، أو false لو كان موجود قبل كده
    bool add(char ch) {
        s += ch;
        int c = ch - 'a';
        int curr = get_link(last);

        bool is_new = false;
        if (!tree[curr].next[c]) {
            int link_node = get_link(tree[curr].link);
            int link_target = tree[link_node].next[c] ? tree[link_node].next[c] : 2;

            sz++;
            int idx = (int)s.size() - 1;
            tree.push_back(Node(tree[curr].len + 2, link_target, idx));
            tree[curr].next[c] = sz;

            tree[sz].num = tree[link_target].num + 1;
            is_new = true;
        }

        last = tree[curr].next[c];
        tree[last].cnt++;

        return is_new;
    }

    // [تجميع البيانات]: لازم تستدعي الفانكشن دي بعد ما تخلص add لكل الحروف 
    // عشان يحسب الـ cnt (تكرار كل palindrome) صح
    void build_occurrences() {
        for (int i = sz; i > 2; i--) {
            tree[tree[i].link].cnt += tree[i].cnt;
        }
    }

    // [Output]: عدد الـ Palindromes الفريدة في النص
    int get_distinct_count() const {
        return sz - 2;
    }

    // [Output]: النص نفسه للـ Palindrome رقم node_id
    string get_palindrome_string(int node_id) const {
        if (node_id <= 2) return "";
        int len = tree[node_id].len;
        int end_idx = tree[node_id].first_idx;
        return s.substr(end_idx - len + 1, len);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s = "abacaba";
    PalindromicTree pam;

    for (int i = 0; i < (int)s.size(); i++) {
        bool is_new = pam.add(s[i]);
        // pam.tree[pam.last].num -> يديك عدد الـ palindromes اللي بتنتهي عند الحرف i
        cout << "Adding " << s[i] << " | New Palindrome Created? " << (is_new ? "YES" : "NO") 
             << " | Palindromes ending at " << i << ": " << pam.tree[pam.last].num << "\n";
    }

    pam.build_occurrences();

    cout << "\n--- Final Results ---\n";
    cout << "Total Distinct Palindromes: " << pam.get_distinct_count() << "\n\n";

    for (int node = 3; node <= pam.sz; node++) {
        cout << "String: " << pam.get_palindrome_string(node)
             << " | Length: " << pam.tree[node].len
             << " | Occurrences: " << pam.tree[node].cnt << "\n";
    }

    return 0;
}
