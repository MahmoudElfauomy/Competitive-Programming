for (int i = 0; i < n; i++)
{
    ll k = i;
    ll cur, l, r, mid;
    while (k < n)
    {
        cur = sp.query(i, k);
        l = k, r = n - 1;
        while (l <= r)
        {
            mid = (l + r) / 2;
            if (sp.query(i, mid) == cur)
            {
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        k = r + 1;
    }
}
