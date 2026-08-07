const int N = 1e6 + 9;
int a[N], cnt[N];
long long dp[N];
// input a[1], a[2], ..., a[n]
// ...
for (int i = 1; i <= n; i++)
    cnt[a[i]]++;
for (int i = N - 1; i >= 1; --i)
{
    long long num_mul = 0; // number of multiples of i
    for (int j = i; j < N; j += i)
        num_mul += (long long)cnt[j];
    dp[i] = (num_mul * (num_mul - 1)) / 2; // number of pairs that are divisible by i
    for (int j = i + i; j < N; j += i)
        dp[i] -= dp[j]; // subtract all dp[j] for j > i and i divides j
}
