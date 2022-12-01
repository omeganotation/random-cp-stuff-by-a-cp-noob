#include <bits/stdc++.h>
#include <ratio>

using namespace std;

using ll = long long;
const ll MOD = 1e9+7;
const int INF = 1e9; const ll INFLL = 1e18;

int t; int n; int k;

struct Cow {
	int x; int y;
	Cow() {}
	Cow(int i, int j) {
		x = i; y = j;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cin >> t >> n >> k;
	vector<Cow> a(n);
	for(int i=0;i<n;i++) {
		cin >> a[i].x >> a[i].y;
	}
	vector<vector<Cow>> groups;
	for(int i=0;i<n;) {
		groups.push_back({});
		int j = i;
		groups[groups.size()-1].push_back(a[i]);
		while(j+1<n&&a[j+1].x-a[j].x<=k) {
			j++;
			groups[groups.size()-1].push_back(a[j]);
		}
		i = j+1;
	}
	if(t==1) {
		int ans = 0;
		for(auto x:groups) {
			if(x.size()%2) {
				int curr = INF;
				for(int i=0;i<x.size();i++) {
					if(i%2) {
						if(x[i-1].x+k>=x[i+1].x) {
							curr = min(curr,x[i].y);
						}
					} else {
						curr = min(curr,x[i].y);
					}
				}
				ans += curr;
			}
		}
		cout << ans << "\n";
	} else {
		int ans = 0;
		for(auto x:groups) {
			vector<vector<int>> dp(x.size()+1,vector<int>(3,-INF));
			dp[0][0] = 0;
			//0 no extra
			//1 extra at i
			//2 extra at i-1
			for(int i=0;i<x.size();i++) {
				dp[i+1][0] = max(dp[i][1],dp[i][2]);
				dp[i+1][1] = dp[i][0];
				if(!(i%2)) {
					dp[i+1][0] = max(dp[i+1][0],x[i].y);
				} else {
					if(i+1<x.size()&&x[i-1].x+k>=x[i+1].x) {
						dp[i+1][2] = max(dp[i+1][2],x[i].y);
					}
				}
				int lo = 0; int hi = i;
				while(lo<hi) {
					int mid = lo+(hi-lo+1)/2;
					if(x[mid].x+k<x[i].x) {
						lo = mid;
					} else {
						hi = mid-1;
					}
				}
				if(lo<i&&x[lo].x+k<x[i].x) {
					if(lo%2==i%2) {
						dp[i+1][0] = max({dp[i+1][0],dp[lo+1][2]+x[i].y,dp[lo+1][1]+x[i].y});
						if(i+1<x.size()&&x[i-1].x+k>=x[i+1].x) {
							dp[i+1][2] = max(dp[i+1][2],dp[lo+1][0]+x[i].y);
						}
					} else {
						dp[i+1][0] = max(dp[i+1][0],dp[lo+1][0]+x[i].y);
						if(i&&i+1<x.size()&&x[i-1].x+k>=x[i+1].x) {
							dp[i+1][2] = max({dp[i+1][2],dp[lo+1][2]+x[i].y,dp[lo+1][1]+x[i].y});
						}
					}
				}
			}
			ans += dp[x.size()][0];
		}
		cout << ans << "\n";
	}
}
