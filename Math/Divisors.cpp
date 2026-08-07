vector<ll> divisors(ll n)
{
    vector<ll> divisors;
    for (int i = 1; i <= n / i; i++)
    {
        if (n % i == 0)
        {
            divisors.push_back(i);
            if (i * i != n)
            {
                divisors.push_back(n / i);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}
