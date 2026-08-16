void solve() {
    int n;
    cin >> n;
    /// s1=x1+y1,s2=x2+y2,d1=x1-y1,d2=x2-y2
    // dis(x1,y1,x2,y2)=abs(x1-x2)+abs(y1-y2)=max(abs(s1-s2),abs(d1-d2))
    int mxs = -1e18, mns = 1e18, mxd = -1e18, mnd = 1e18;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        mxs = max(mxs, (x + y));
        mns = min(mns, (x + y));
        mxd = max(mxd, (x - y));
        mnd = min(mnd, (x - y));
    }
    cout<<max(abs(mxs-mns),abs(mnd-mxd));
}
