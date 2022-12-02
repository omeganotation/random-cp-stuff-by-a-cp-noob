#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll MOD = 1e9+7;
const int INF = 1e9; const ll INFLL = 1e18;

int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    vector<int> a(n+1);
    vector<int> pos(n+1);
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    set<int> st;
    vector<int> ans(n+1);
    for(int i=1;i<=n;i++) {
        auto it = st.lower_bound(a[i]);
        if(it!=st.end()) {
            auto it2 = st.lower_bound(a[i]);
            if(it2==st.begin()||pos[*(--it2)]<pos[*it]) {
                ans[a[i]]++;
                ans[*it]--;
            }
        }
        st.insert(a[i]);
    }
    cout << "0\n";
    for(int i=1;i<n;i++) {
        ans[i] += ans[i-1];
        cout << ans[i] << "\n";
    }
    cout << "0\n";
}
