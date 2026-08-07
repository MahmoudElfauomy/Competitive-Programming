int SQ;
int mp[N];
struct pack
{
    int l, r, ind;
    bool operator<(pack &P)
    {
        if (l / SQ != P.l / SQ)
            return l / SQ < P.l / SQ;
        return (l / SQ & 1 ? r < P.r : r > P.r);
    }
};

class Mo
{
    vector<pack> v;
    vector<ll> vv;
    
    int sum = 0;
    int l_pointer = 0, r_pointer = -1;

    void add(int id)
    {
        
    }
    void sub(int id)
    {

    }
    int query()
    {
        return sum;
    }
    
    public:
    void add_query(int l, int r, int id)
    {
        v.push_back({l, r, id});
    }
    Mo(vector<ll> &z)
    {
        SQ = sqrt(z.size()) + 1;
        vv = z;
    }
    void get()
    {
        vector<int> ans(v.size());
        sort(v.begin(), v.end());
        for (auto &[le, ri, id] : v)
        {
            while (r_pointer < ri)
                add(++r_pointer);
            while (l_pointer > le)
                add(--l_pointer);
            while (r_pointer > ri)
                sub(r_pointer--);
            while (l_pointer < le)
                sub(l_pointer++);
            ans[id] = query();
        }
        for (int i = 0; i < ans.size(); i++)
            cout << ans[i] << '\n';
    }
};
