vector<int>lis(vector<int>a) {
    vector<int>dp;int n=a.size();
    vector<int>v(n);
    for (int i=0;i<n;i++) {
        auto it=
            lower_bound(dp.begin(),dp.end(),a[i]);
        if(it == dp.end()) {
            dp.push_back(a[i]);
            v[i] = dp.size();
        } else {
            *it = a[i];
            v[i] = (it - dp.begin()) + 1;
        }
    }
    return v;
 
}
