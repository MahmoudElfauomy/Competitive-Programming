using cd = complex<double>;
const double PI = acos(-1);

void FFT(vector<cd> &a, bool invert)
{
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert)
    {
        for (cd &x : a)
            x /= n;
    }
}

vector<int> multiply(vector<int> const &a, vector<int> const &b)
{
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    FFT(fa, false);
    FFT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    FFT(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
/*
BIG INTGER

string mul(const string &a, const string &b)
{
    vector<int> p1(a.size()), p2(b.size());
    for (int i = 0; i < a.size(); i++)
    {
        p1[(int)a.size() - i - 1] = a[i] - '0';
    }
    for (int i = 0; i < b.size(); i++)
    {
        p2[(int)b.size() - i - 1] = b[i] - '0';
    }
    vector<int> ans = multiply(p1, p2);
    for (int i = 0; i < ans.size() - 1; i++)
    {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }
    string res = to_string(ans.back());
    for (int i = ans.size() - 2; ~i; i--)
    {
        res += ans[i] + '0';
    }
    for (int i = 0; i < res.size(); i++)
    {
        if (res[i] != '0')
            return res.substr(i);
    }
    return "0";
}


POWER

vector<ll> power(vector<ll> a, int k)
{
    vector<ll> ans{1};
    while (k)
    {
        if (k & 1)
            ans = multiply(ans, a);
        a = multiply(a, a);
        k >>= 1;
    }
    return ans;
}

*/
