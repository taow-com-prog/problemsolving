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
 
int a[MAXN];
vector<pll> dp[20][20];
 
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n - 1; ++i) {
        dp[i][i + 1].pb({0, 0});
    }
 
    for (int len = 3; len <= n; ++len) {
        for (int l = 1; l <= n; ++l) {
            for (int r = l + len - 1; r <= n; ++r) {
                vector<pll> vals;
                for (int mid = l + 1; mid <= r - 1; ++mid) {
                    for (auto x:dp[l][mid]) {
                        for (auto y:dp[mid][r]) {
                            vals.pb({x.fi + x.se + y.fi + a[mid], x.se + y.fi + y.se + a[mid]});
                        }
                    }
                }
                sort(all(vals));
                dp[l][r].pb(vals[0]);
                ll mx = vals[0].se;
                for (int i = 1; i < sz(vals); ++i) {
                    if (vals[i].se >= mx) {
                        continue;
                    } else {
                        mx = vals[i].se;
                        dp[l][r].pb(vals[i]);
                    }
                }
            }
        }
    }
 
    ll ans = inf_ll;
    for(auto x:dp[1][n]){
        ans = min(ans, x.fi + x.se);
    }
    cout << ans + a[1] + a[n]<<"\n";
}
 
signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
    //  freopen("../output.txt", "w", stdout);
#else
 
#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);
 
    int t = 1;
    while (t--)
        solve();
 
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}