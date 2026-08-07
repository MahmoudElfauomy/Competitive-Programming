vector<int> last;
void KMP(string &st)
{
    last = vector<int>(st.size());
    last[0] = 0;
    for (int i = 1, j = 0; i < st.size(); i++)
    {
        while (j && st[i] != st[j])
            j = last[j - 1];
        j += (st[i] == st[j]);
        last[i] = j;
    }
}
vector<vector<int>> com(N, vector<int>(26));
void compute_automation(string st)
{
    st += '^';
    KMP(st);
    for (int i = 0; i < st.size(); i++)
    {
        for (int ch = 0; ch < 26; ch++)
        {
            if (i && st[i] != ch + 'a')
                com[i][ch] = com[last[i - 1]][ch];
            else
                com[i][ch] = i + (st[i] == ch + 'a');
        }
    }
}
