class Manacher
{
    vector<int> man;

public:
    Manacher(string &s)
    {
        string t;
        for (auto &c : s)
        {
            t += string("_") + c;
        }
        t += '_';
        auto res = manacher_odd(t);
        man = vector<int>(begin(res) + 1, end(res));
    }

    vector<int> manacher_odd(string s)
    {
        int n = int(s.size());
        s = "^" + s + "!";
        vector<int> v(n + 2);
        int l = 1, r = 1;
        for (int i = 1; i <= n; i++)
        {
            v[i] = min(r - i, v[l + (r - i)]);
            while (s[i - v[i]] == s[i + v[i]])
            {
                v[i]++;
            }
            if (i + v[i] > r)
            {
                r = i + v[i];
                l = i - v[i];
            }
        }
        return vector<int>(begin(v) + 1, end(v) - 1);
    }

    int get_odd(int i) // to get the odd palindrome length EX : aba by multiply it 2 then subtract 1
    {
        return man[i << 1] / 2;
    }

    int get_even(int i) // to get the even palindrome length EX : abba by multiply it 2
    {
        return man[i << 1 | 1] / 2;
    }
};
