struct Matrix_P
{
    vector<vector<ll>> multiply(vector<vector<ll>> &a, vector<vector<ll>> &b)
    {
        int n = a.size(), m = a[0].size(), k = b[0].size();
        vector<vector<ll>> res(n, vector<ll>(k));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                for (int z = 0; z < m; z++)
                {
                    res[i][j] += a[i][z] % mod * b[z][j] % mod;
                    res[i][j] += mod;
                    res[i][j] %= mod;
                }
            }
        }
        return res;
    }
    vector<vector<ll>> power(vector<vector<ll>> a, ll b)
    {
        vector<vector<ll>> product;
        bool f = 0;
        while (b)
        {
            if (b & 1)
            {
                if (f)
                    product = multiply(product, a);
                else
                    product = a, f = 1;
            }
            a = multiply(a, a), b >>= 1;
        }
        return product;
    }
};
