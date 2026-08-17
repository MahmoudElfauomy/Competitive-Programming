class TRIE
{
    struct Node
    {
        Node *ch[26];
        int pre, last;
        Node()
        {
            memset(ch, 0, sizeof ch);
            pre = last = 0;
        }
    };

public:
    Node *root = new Node();
    void insert(string x)
    {
        Node *cur = root;
        for (int i = 0; i < x.size(); i++)
        {
            int ind = x[i] - 'a';
            if (cur->ch[ind] == 0)
            {
                cur->ch[ind] = new Node();
            }
            cur = cur->ch[ind];
            cur->pre++;
        }
        cur->last++;
    }
    void erase(const string &s)
    {
        Node *cur = root;
        for (auto it : s)
        {
            int to = it - 'a';
            if (cur->ch[to] == 0 || cur->pre == 1)
            {
                cur->ch[to] = 0;
                return;
            }
            cur = cur->ch[to];
            cur->pre--;
        }
        cur->last--;
    }
    int query(string x)
    {
        Node *cur = root;
        for (int i = 0; i < x.size(); i++)
        {
            int ind = x[i] - 'a';
            if (cur->ch[ind] == 0)
            {
                return 0;
            }
            cur = cur->ch[ind];
        }
        return cur->last;
    }

    int mx_pref(const string &s)
    {
        Node *cur = root;
        int ret = 0;
        for (auto it : s)
        {
            int idx = it - 'a';
            if (cur->ch[idx] == 0 || cur->ch[idx]->pre < 2)
            {
                return ret;
            }

            ret++;
            cur = cur->ch[idx];
        }
        return ret;
    }
};
