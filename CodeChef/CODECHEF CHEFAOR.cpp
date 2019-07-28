/*
    Knuth dp and sparse table.
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
const int MAXN = 5000 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e7 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;

int a[MAXN];
ll dp[MAXN][MAXN];
int best[MAXN][MAXN];

int n, k;

int up[LOG][MAXN];
int lg[MAXN];

void build() {
    for (int i = 1; i <= n; ++i) {
        up[0][i] = a[i];
    }
    for (int e = 1; e < LOG; ++e) {
        for (int i = 1; i <= n; ++i) {
            if (i + (1 << (e - 1)) <= n)
                up[e][i] = (up[e - 1][i] | up[e - 1][i + (1 << (e - 1))]);
        }
    }

    lg[1] = 0;
    for (int i = 2; i <= n; ++i) {
        lg[i] = lg[i / 2] + 1;
    }

}

inline int get(int l, int r) {
    int j = lg[r - l + 1];

    return (up[j][l] | up[j][r - (1 << j) + 1]);
}


void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build();

    for (int i = 1; i <= n; ++i) {
        dp[1][i] = get(1, i);
        best[1][i] = 1;
    }

    for (int e = 2; e <= k; ++e) {
        for (int i = n; i >= 1; --i) {
            int right = n;
            if (i + 1 <= n)
                right = best[e][i + 1];
            int left = best[e - 1][i];

            dp[e][i] = -inf_ll;
            for (int j = left; j <= right && j <= i; ++j) {
                ll val = dp[e - 1][j - 1] + get(j, i);
                if (val >= dp[e][i]) {
                    dp[e][i] = val;
                    best[e][i] = j;
                }
            }
        }
    }

    cout << dp[k][n]<<"\n";
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

    int t = 1;
    cin >> t;
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}