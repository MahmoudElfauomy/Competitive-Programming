vector<int> spf(N);

void SPF()
{
    for (int i = 2; i < N; i++)
    {
        if (!spf[i])
        {
            for (int j = i; j < N; j += i)
            {
                if (!spf[j]) { spf[j] = i; }
            }
        }
    }
}
