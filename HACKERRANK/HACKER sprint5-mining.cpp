/*
    Solved using D&C approach dp[k][n] - split first n elements in K blocks
    calculated cost[l][r] in O(1) using median and prefix sums.

*/

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 4e18;
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
const int MX = 5000 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;


ll x[MAXN], w[MAXN];

ll pref[MAXN];
ll pref_cnt[MAXN];
ll cost[MAXN][MAXN];

ll dp[MAXN][MAXN];

void calc(int x, int optl, int optr, int l, int r) {
    if (l > r)
        return;
    int mid = (l + r) / 2;

    int pos = -1;
    dp[x][mid] = inf_ll;
    for (int i = optl; i <= optr && i <= mid; ++i) {
        if (dp[x - 1][i - 1] + cost[i][mid] < dp[x][mid]) {
            dp[x][mid] = dp[x - 1][i - 1] + cost[i][mid];
            pos = i;
        }
    }
  //  dout << "here " << x << " " << mid << " " << dp[x][mid] << "\n";

    calc(x, optl, pos, l, mid - 1);
    calc(x, pos, optr, mid + 1, r);
}

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> w[i];
    }

    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + 1ll * x[i] * w[i];
        pref_cnt[i] = pref_cnt[i - 1] + w[i];
    }

    for (int l = 1; l <= n; ++l) {

        int mid = l;
        for (int r = l; r <= n; ++r) {

            while ((pref_cnt[mid] - pref_cnt[l - 1]) * 2 < pref_cnt[r] - pref_cnt[l - 1]) {
                mid++;
            }

            cost[l][r] = (1ll * x[mid] * (pref_cnt[mid] - pref_cnt[l - 1]) - (pref[mid] - pref[l - 1]));

            cost[l][r] += (pref[r] - pref[mid]) - 1ll * x[mid] * (pref_cnt[r] - pref_cnt[mid]);

        }
    }


    for (int i = 1; i <= n; ++i) {
        dp[0][i] = inf_ll;
    }
    dp[0][0] = 0;

    for (int i = 1; i <= k; ++i) {
        calc(i, 1, n, 1, n);
    }
    cout << dp[k][n] << "\n";


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
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}