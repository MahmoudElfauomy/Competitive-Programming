// number of divisors
// MAX_n = 1e7
const int MAXN = 1e7 + 1;
int spf[MAXN];

// pre
void init() { 
    for (int i = 1; i < MAXN; i++) spf[i] = i;
    for (int i = 2; i * i < MAXN; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAXN; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

//  for each query : O(log(N)) 
int count_divisors(int n) 
{
    int ans = 1 ;
    while (n > 1) 
    {
        int p = spf[n] ;
        int count = 0 ;
        while (n % p == 0) 
        {
            count ++ ;
            n /= p ;
        }
        ans *= ( count + 1 ) ;
    }
    return ans;
}
