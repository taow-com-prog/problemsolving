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
const int MAXN = 4000 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e7 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
char u[MAXN][MAXN];
 
int c[MAXN][MAXN];
 
int suf[MAXN][MAXN];
 
int dp[810][MAXN];
 
void calc(int x, int optl, int optr, int l, int r) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    dp[x][mid] = inf_int;
    int pos = -1;
    for (int j = optl; j <= optr && j <= mid; ++j) {
        int val = dp[x - 1][j - 1] + c[j][mid];
        if (val < dp[x][mid]) {
            dp[x][mid] = val;
            pos = j;
        }
    }
    calc(x, optl, pos, l, mid - 1);
    calc(x, pos, optr, mid + 1, r);
}
 
void solve() {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> u[i][j];
            u[i][j]-='0';
        }
    }
 
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= j; ++i) {
            suf[j][i] = suf[j][i - 1] + u[j][i];
            dout <<"s "<< j <<" "<<i<<" : "<<suf[j][i]<<endl;
        }
    }
 
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            c[i][j] = c[i][j - 1] + suf[j][j] - suf[j][i - 1];
            dout <<i <<" "<<j <<" : "<<c[i][j]<<endl;
        }
 
    }
    for(int i=1;i<=n;++i){
        dp[1][i] = c[1][i];
    }
 
    for (int i = 2; i <= k; ++i) {
        calc(i, 1, n, 1, n);
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
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}