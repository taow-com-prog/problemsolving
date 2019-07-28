/*
    Knuth dp
*/

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 2e18;
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
const int MAXN = 1000 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e7 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;


ll dp[MAXN][MAXN];
int best[MAXN][MAXN];

int a[MAXN];

void solve() {
    int n, m;
    if (cin >> n >> m) {

    } else {
        exit(0);;
    }
    a[0] = 0;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
    }
    a[m + 1] = n;

    for (int i = 0; i <= m; ++i) {
        dp[i][i + 1] = 0;
        best[i][i + 1] = i + 1;
    }

    for (int len = 3; len <= m + 2; ++len) {
        for (int l = 0; l <= m && l + len - 1 <= m + 1; ++l) {
            int r = l + len - 1;
            dp[l][r] = inf_ll;

            for (int j = best[l][r - 1]; j <= best[l + 1][r] && j < r; ++j) {
                ll val = dp[l][j] + dp[j][r] + a[r] - a[l];
                if (val < dp[l][r]) {
                    dp[l][r] = val;
                    best[l][r] = j;
                }
            }
            dout << l << " - " << r << " : " << dp[l][r] << "\n";
        }
    }
    cout << dp[0][m + 1] << "\n";


}

signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
    //freopen("../output.txt", "w", stdout);
#else

#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);

    int t = inf_int;
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}