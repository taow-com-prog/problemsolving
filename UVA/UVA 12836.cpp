/*
	Knuth optimization
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

int a[MAXN];
int suf_pow[MAXN];
int pref_pow[MAXN];
int val[MAXN];
int pref_sum[MAXN];

int dp[MAXN][MAXN];
int best[MAXN][MAXN];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = n; i >= 1; --i) {
        suf_pow[i] = 1;
        for (int j = i + 1; j <= n; ++j) {
            if (a[i] > a[j]) {
                suf_pow[i] = max(suf_pow[i], suf_pow[j] + 1);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        pref_pow[i] = 1;
        for (int j = i - 1; j >= 1; --j) {
            if (a[j] < a[i]) {
                pref_pow[i] = max(pref_pow[i], pref_pow[j] + 1);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        val[i] = pref_pow[i] + suf_pow[i] - 1;

        pref_sum[i] = pref_sum[i - 1] + val[i];

    }
    for(int i=1;i<=n;++i){
        dout << val[i]<<" ";
    }
    dout << endl;

    for (int i = 1; i <= n; ++i) {
        dp[i][i] = 0;
        best[i][i] = i;
    }

    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l <= n && l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            dp[l][r] = inf_int;

            for (int j = best[l][r - 1]; j <= best[l + 1][r] && j < r; ++j) {
                if (dp[l][j] + dp[j + 1][r] + pref_sum[r] - pref_sum[l - 1] < dp[l][r]) {
                    dp[l][r] = dp[l][j] + dp[j + 1][r] + pref_sum[r] - pref_sum[l - 1];
                    best[l][r] = j;
                }
            }
            dout << l <<" "<<r <<" : "<<dp[l][r]<<"\n";
        }
    }

    cout << dp[1][n]<<"\n";


}

signed main() {
#ifdef zxc
    debug = 0;
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
    cin >> t;
    for(int i = 1;i <= t;++i){
        cout <<"Case "<<i<<": ";
        solve();
    }
    return 0;
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}