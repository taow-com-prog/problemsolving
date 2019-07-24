/*
    Solved using D&C dp.
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
const int MAXN = 2e5 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e7 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;

int t[MAXN];
ll pref_sum[MAXN];

dbl pref_val[MAXN];
dbl pref_rev[MAXN];

dbl get_cost(int l, int r) {
    return pref_val[r] - pref_val[l - 1] - (pref_sum[l - 1]) * (pref_rev[r] - pref_rev[l - 1]);
}


dbl dp[2][MAXN];

void calc(int cur, int optL, int optR, int l, int r) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    int pos = -1;
    dp[cur][mid] = 1e30;
    for (int i = optL; i <= optR && i <= mid; ++i) {
        dbl val = get_cost(i, mid) + dp[cur ^ 1][i - 1];
        dout <<i <<" "<<mid <<" : "<<val<<endl;
        if (val < dp[cur][mid]) {
            dp[cur][mid] = val;
            pos = i;
        }
    }

    calc(cur, optL, pos, l, mid - 1);
    calc(cur, pos, optR, mid + 1, r);
}

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i];
    }
    for (int i = 1; i <= n; ++i) {
        pref_sum[i] = pref_sum[i - 1] + t[i];

        pref_rev[i] = pref_rev[i-1] + 1/dbl(t[i]);
    }

    for (int i = 1; i <= n; ++i) {
        pref_val[i] = pref_val[i - 1];
        pref_val[i] += dbl(pref_sum[i]) / t[i];

    }
    dp[1][0] = inf_ll;
    for (int i = 1; i <= n; ++i) {
        dp[1][i] = pref_val[i];
    }

    for (int i = 2; i <= k; ++i) {
        calc(i & 1, 1, n, 1, n);
    }

    cout << dp[k&1][n]<<"\n";


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