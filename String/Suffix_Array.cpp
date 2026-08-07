struct SuffixArray
{
    int n;
    vector<int> sa, c, lcp;

    SuffixArray(string s)
    {
        s += "$";
        n = s.size();
        sa.assign(n, 0);
        c.assign(n, 0);
        lcp.assign(n, 0);
        vector<int> cnt(max(256, n), 0), pn(n), cn(n);

        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < 256; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++)
            sa[--cnt[s[i]]] = i;

        c[sa[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++)
        {
            if (s[sa[i]] != s[sa[i - 1]])
                classes++;
            c[sa[i]] = classes - 1;
        }

        for (int k = 0; (1 << k) < n; ++k)
        {
            for (int i = 0; i < n; i++)
                pn[i] = (sa[i] - (1 << k) + n) % n;

            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
                sa[--cnt[c[pn[i]]]] = pn[i];

            cn[sa[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++)
            {
                pair<int, int> cur = {c[sa[i]], c[(sa[i] + (1 << k)) % n]};
                pair<int, int> prev = {c[sa[i - 1]], c[(sa[i - 1] + (1 << k)) % n]};
                if (cur != prev)
                    classes++;
                cn[sa[i]] = classes - 1;
            }
            c = cn;
        }

        for (int i = 0, k = 0; i < n - 1; i++, k = max(k - 1, 0))
        {
            int j = sa[c[i] - 1];
            while (s[i + k] == s[j + k])
                k++;
            lcp[c[i]] = k;
        }
    }
};
