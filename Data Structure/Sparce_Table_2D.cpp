const int N = 505;
const int LG = 10;

int st[LG][LG][N][N];
int lg[N];

//==================== Merge ====================//
inline int merge(int a, int b)
{
    return max(a, b);

    // return min(a, b);
    // return __gcd(a, b);
    // return a & b;
    // return a | b;
}
//==================== Build ====================//
void build(vector<vector<int>> &a, int n, int m)
{
    lg[1] = 0;
    for (int i = 2; i < N; i++)
        lg[i] = lg[i / 2] + 1;

    // Base
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            st[0][0][i][j] = a[i][j];

    // Horizontal
    for (int ky = 1; (1 << ky) <= m; ky++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j + (1 << ky) - 1 <= m; j++)
            {
                st[0][ky][i][j] = merge(
                    st[0][ky - 1][i][j],
                    st[0][ky - 1][i][j + (1 << (ky - 1))]
                );
            }
        }
    }

    // Vertical
    for (int kx = 1; (1 << kx) <= n; kx++)
    {
        for (int ky = 0; (1 << ky) <= m; ky++)
        {
            for (int i = 1; i + (1 << kx) - 1 <= n; i++)
            {
                for (int j = 1; j + (1 << ky) - 1 <= m; j++)
                {
                    st[kx][ky][i][j] = merge(
                        st[kx - 1][ky][i][j],
                        st[kx - 1][ky][i + (1 << (kx - 1))][j]
                    );
                }
            }
        }
    }
}
//==================== Query ====================//
int query(int x1, int y1, int x2, int y2)
{
    int kx = lg[x2 - x1 + 1];
    int ky = lg[y2 - y1 + 1];

    return merge(
        merge(
            st[kx][ky][x1][y1],
            st[kx][ky][x2 - (1 << kx) + 1][y1]
        ),
        merge(
            st[kx][ky][x1][y2 - (1 << ky) + 1],
            st[kx][ky][x2 - (1 << kx) + 1][y2 - (1 << ky) + 1]
        )
    );
}
//===============================================//
void Captain()
{
    ll n , m ; cin >> n >> m ;

    vector<vector<int>> a(n + 1, vector<int>(m + 1)) ;
    for ( int i = 1 ; i <= n ; i ++ )
    {
        for ( int j = 1 ; j <= m ; j ++ )
        {
            cin >> a[i][j] ;
        }
    }

    // O( n * m  * log n * log m)
    build ( a , n , m ) ;

    // 1-based ---------- // O(1) 
    cout << query ( 1 , 1 , n , m ) << el ;
}
