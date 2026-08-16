class sparseTable
{
    struct node
    {
        int64_t n = 0, mn, mx, sum;

        node()
        {
            sum = 0;
            mn = 1e18;
            mx = -1e18;
        }
    };


    vector<vector<node>> sp;
    vector<int> Log;

    node merge(node a, node b)
    {
        node ret;

        return ret;
    }

public:
    sparseTable(vector<int64_t>& v)
    {
        // build
        int n = v.size();
        sp.resize(n + 5, vector<node>(__lg(n) + 5));

        Log.resize(n + 5);
        Log[1] = 0;
        for (int i = 2; i <= n; i++) { Log[i] = Log[i >> 1] + 1; }


        for (int i = 0; i < n; i++)
        {
            ///////////////////
            sp[i][0].mn = v[i];
            sp[i][0].mx = v[i];
        }

        for (int k = 1; k <= __lg(n); k++)
        {
            for (int i = 0; i + (1 << k) <= n; i++)
            {
                sp[i][k] = merge(sp[i][k - 1], sp[i + (1LL << (k - 1))][k - 1]);
            }
        }
    }

    node query(int l, int r)
    {
        int64_t k = Log[r - l + 1];
        return merge(sp[l][k], sp[r - (1 << k) + 1][k]);
    }
};
