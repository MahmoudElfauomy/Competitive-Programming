vector<int> LIS(vector<int>& v)
{
    if (v.empty()) { return {}; }
    int n = v.size();
    vector<int> t, par(n, -1);
    for (int i = 0; i < n; i++)
    {
        auto it = lower_bound(t.begin(), t.end(), v[i],
        [&v](int index, int value) { return v[index] < value; });

        int idx = distance(t.begin(), it);
        if (idx > 0) { par[i] = t[idx - 1]; }
        if (it == t.end()) { t.push_back(i); }
        else { t[idx] = i; }
    }

    vector<int> lis;
    int cur = t.back();
    while (cur != -1)
    {
        lis.push_back(v[cur]);
        cur = par[cur];
    }
    reverse(lis.begin(), lis.end());
    return lis;
}
