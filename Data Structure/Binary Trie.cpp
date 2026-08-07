struct Binary_Trie
{
    vector<array<int, 2>> nxt;
    vector<int> freq;

    Binary_Trie()
    {
        newNode();
    }

    int newNode()
    {
        nxt.push_back({-1, -1});
        freq.push_back(0);
        return nxt.size() - 1;
    }

    void insert(int x)
    {
        int cur = 0;
        freq[cur]++;
        for (int i = 30; i >= 0; i--)
        {
            int on = (x >> i) & 1;
            if (nxt[cur][on] == -1)
            {
                int new_idx = newNode();
                nxt[cur][on] = new_idx;
            }
            cur = nxt[cur][on];
            freq[cur]++;
        }
    }

    void remove(int x)
    {
        int cur = 0;
        freq[cur]--;
        for (int i = 30; i >= 0; i--)
        {
            int on = (x >> i) & 1;
            cur = nxt[cur][on];
            freq[cur]--;
        }
    }

    int mx_xor(int x)
    {
        if (freq[0] == 0)
            return 0;
        int cur = 0;
        int ans = 0;
        for (int i = 30; i >= 0; i--)
        {
            int on = (x >> i) & 1;
            if (nxt[cur][on ^ 1] != -1 && freq[nxt[cur][on ^ 1]])
            {
                ans |= (1 << i);
                cur = nxt[cur][on ^ 1];
            }
            else
            {
                cur = nxt[cur][on];
            }
        }
        return ans;
    }

    int mn_xor(int x)
    {
        if (freq[0] == 0)
            return 0;
        int cur = 0;
        int ans = 0;
        for (int i = 30; i >= 0; i--)
        {
            int on = (x >> i) & 1;
            if (nxt[cur][on] == -1 || freq[nxt[cur][on]] == 0)
            {
                ans |= (1 << i);
                cur = nxt[cur][on ^ 1];
            }
            else
            {
                cur = nxt[cur][on];
            }
        }
        return ans;
    }

    int less_than_k(int x, int k)
    {
        int cur = 0;
        ll ans = 0;
        for (int i = 30; i >= 0 && cur != -1; i--)
        {
            int on_x = (x >> i) & 1;
            int on_k = (k >> i) & 1;
            if (on_k == 0)
            {
                cur = nxt[cur][on_x];
            }
            else
            {
                if (nxt[cur][on_x] != -1)
                    ans += freq[nxt[cur][on_x]];
                cur = nxt[cur][on_x ^ 1];
            }
        }
        return ans;
    }
    ll kth_element(ll k)
    {
        if (freq.empty() || k > freq[0] || k <= 0)
            return -1;

        int cur = 0;
        ll ans = 0;

        for (int i = 30; i >= 0 && cur != -1; i--)
        {
            int left_child = nxt[cur][0];
            ll left_cnt = (left_child != -1 ? freq[left_child] : 0);

            if (k <= left_cnt)
            {
                cur = left_child;
            }
            else
            {
                k -= left_cnt;
                ans |= (1LL << i);
                cur = nxt[cur][1];
            }
        }

        return ans;
    }

    ll get_mex()
    {
        int cur = 0;
        ll ret = 0;

        for (int i = 30; i >= 0; i--)
        {
            if (cur == -1)
                break;

            int left_child = nxt[cur][0];

            if (left_child != -1 && freq[left_child] == (1LL << i))
            {
                ret |= (1LL << i);
                cur = nxt[cur][1];
            }
            else
            {
                cur = left_child;
            }
        }
        return ret;
    }
};
