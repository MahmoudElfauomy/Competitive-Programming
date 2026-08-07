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
