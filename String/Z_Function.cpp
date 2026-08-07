vector<int> z;
void Z_function(string &st)
{
    int sz = st.size();
    z = vector<int>(sz, 0);
    int l = 0, r = 0;

    for (int i = 1; i < sz; i++)
    {
        if (i < r)
        {
            z[i] = min(r - i, z[i - l]);
        }
        while (z[i] + i < sz && st[z[i]] == st[z[i] + i])
            z[i]++;
        if (i + z[i] > r)
        {
            r = i + z[i];
            l = i;
        }
    }
}
