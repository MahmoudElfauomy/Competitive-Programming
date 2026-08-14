// O(sqrt(N))
vector<int> getDivisors(int64_t n)
{
    vector<int> ret;
    for (int64_t i = 1; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            ret.push_back(i);
            if (i != n / i) { ret.push_back(n / i); }
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}
