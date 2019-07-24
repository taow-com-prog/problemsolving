/*
    D&C optimization.
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
const int MAXN = 2e5 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e7 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;

ll dp[12][MAXN];
int best[12][MAXN];
int w[MAXN];
ll pref[MAXN];
ll pref_val[MAXN];

ll cost(int l, int r) {
    return pref_val[r] - pref_val[l - 1] - (pref[r] - pref[l - 1]) * l;
}

void calc(int cur, int optl, int optr, int l, int r) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    int pos = -1;
    dp[cur][mid] = inf_ll;
    dout <<"cur "<<mid <<" "<<optl <<" "<<optr<<endl;
    for (int j = optl; j <= optr && j <= mid; ++j) {
        ll val = dp[cur - 1][j - 1] + cost(j, mid);
        if (val < dp[cur][mid]) {
            dp[cur][mid] = val;
            pos = j;
        }
    }

    calc(cur, optl, pos, l, mid - 1);
    calc(cur, pos, optr, mid + 1, r);
}

void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];

        pref[i] = pref[i - 1] + w[i];
        pref_val[i] = pref_val[i - 1] + w[i] * i;
    }
    for (int i = 1; i <= n; ++i) {
        dp[1][i] = cost(1, i);
        best[1][i] = 1;

    }
    dp[1][0] = 0;

    dout << "C " << cost(1, 3) << " " << cost(4, 5) << endl;

    for (int x = 2; x <= k; ++x) {
        /* for (int i = n; i >= 1; --i) {
             int right = n;
             if (i + 1 <= n)
                 right = best[x][i + 1];
             int left = best[x - 1][i];

             dp[x][i] = inf_ll;
             dout << "x " << i << " " << left << " " << right << endl;
             for (int j = left; j <= right && j <= i; ++j) {
                 ll val = dp[x - 1][j - 1] + cost(j, i);
                 if (val <= dp[x][i]) {
                     dp[x][i] = val;
                     best[x][i] = j;
                 }
             }
         }*/

        calc(x,1,n,1,n);
    }

    for(int i=1;i<=n;++i){
        dout <<i<<" - "<< dp[k][i]<<endl;
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