/*
    Used dp  for each column independently
   int dp[2][350][350][2]; // start token A.B , i-th , how much steps we did in algo, what was the last letter we took.
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 1e18;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double dbl;
#define pb push_back
const double pi = 3.1415926535898;
#define dout if(debug) cout
#define fi first
#define se second
#define sp setprecision
#define sz(a) (int(a.size()))
#define all(a) a.begin(),a.end()
bool debug = 0;
const int MAXN = 4100 + 100;
const int LOG = 22;
const int mod = 1e9 + 7;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
#define int ll
 
int n, m;
string a[350];
 
int dp[2][350][350][2]; // start, i , steps, last
int dp_cost[2][350]; // sum over all
 
 
int all_cost[2][350];
 
void solve() {
    int k;
    cin >> m >> n >> k;
    for (int e = 1; e <= m; ++e) {
        for (int i = 1; i <= n; ++i) {
            char x;
            cin >> x;
            a[i].pb(x);
        }
    }
    for (int i = 1; i <= n; ++i) {
        reverse(all(a[i]));
    }
    for (int i = 1; i <= n; ++i) {
        for (char &c:a[i]) {
            c -= 'A';
        }
    }
 
    memset(all_cost, 0, sizeof all_cost);
    dout << endl;
    for (int x = 1; x <= n; ++x) {
        string s = a[x];
        for (int st = 0; st < 2; ++st) {
            for (int i = 0; i <= m; ++i) {
                for (int j = 0; j <= m + 2; ++j) {
                    dp[st][i][j][0] = dp[st][i][j][1] = inf_int;
                }
            }
        }
        for (char c:s) {
            dout << int(c);
        }
        dout << endl;
 
        dp[0][0][1][0] = 0;
        dp[1][0][1][1] = 0;
 
        for (int st = 0; st < 2; ++st) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j <= m + 2; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        if (dp[st][i][j][k] != inf_int) {
                            if (s[i] == k) {
                                dp[st][i + 1][j][k] = min(dp[st][i + 1][j][k], dp[st][i][j][k]);
                            } else {
                                dp[st][i + 1][j][k] = min(dp[st][i + 1][j][k], dp[st][i][j][k] + 1);
                                dp[st][i + 1][j + 1][s[i]] = min(dp[st][i + 1][j + 1][s[i]], dp[st][i][j][k]);
                            }
                        }
                    }
                }
            }
        }
 
        for (int j = 0; j <= m + 2; ++j) {
            dp_cost[0][j] = dp_cost[1][j] = inf_int;
        }
 
        for (int st = 0; st < 2; ++st) {
            for (int j = 0; j <= m + 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    dp_cost[st][j] = min(dp_cost[st][j], dp[st][m][j][k]);
                }
            }
        }
        for (int st = 0; st < 2; ++st) {
            for (int j = 1; j <= m + 2; ++j) {
                dp_cost[st][j] = min(dp_cost[st][j], dp_cost[st][j - 1]);
            }
        }
 
        for (int j = 0; j <= m + 2; ++j) {
            dout << "x " << x << " " << j << " - " << dp_cost[0][j] << " " << dp_cost[1][j] << endl;
        }
 
        for (int st = 0; st < 2; ++st) {
            for (int j = 0; j <= m + 2; ++j) {
                all_cost[st][j] += dp_cost[st][j];
            }
        }
    }
 
    vector<pll> res;
    for (int j = 1; j <= m + 2; ++j) {
        int val = min(all_cost[0][j], all_cost[1][j]);
        dout << "val " << j << " " << val << endl;
        res.pb({val, j});
    }
    for (auto x:res) {
        dout << x.fi << " " << x.se << endl;
    }
 
 
    for (int i = 1; i <= k; ++i) {
        cout << " ";
        int x;
        cin >> x;
        if (x >= n * m) {
            cout << 0;
            continue;
        }
 
        int l = 0, r = sz(res) - 1;
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (res[mid].fi <= x) {
                ans = res[mid].se;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        assert(ans != -1);
        cout << ans;
    }
 
 
}
 
signed main() {
#ifdef zxc
    debug = 0;
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#else
 
#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);
 
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ":";
        solve();
        cout << "\n";
    }
 
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}