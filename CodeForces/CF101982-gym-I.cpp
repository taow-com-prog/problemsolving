
/*
	Solved by dp[i][j] - first i empty positions filled with numbers >= j

	Compexilty  n * k * log(n) with D&C optimization


	can be solved by convex hull trick
*/
 
#include bitsstdc++.h
 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 2e18;
typedef pairint, int pii;
typedef pairll, ll pll;
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
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
int a[MAXN];
ll dp[2][MAXN];
ll val[MAXN];
ll pref_val[MAXN];
int spec[MAXN];
vectorint pos;
 
int pref[108];
 
void calc(int cur, int optL, int optR, int l, int r) {
    if (l  r)
        return;
    int mid = (l + r)  1;
 
    dp[cur][mid] = -inf_ll;
    int vmid = pos[mid];
    int pos_opt = -1;
 
    int ri = min(optR,mid);
    for (int i = optL; i = ri; ++i) {
        int to = pos[i];
        ll val = dp[cur ^ 1][i - 1] + pref_val[vmid] - pref_val[to - 1] + 1ll  (mid - i + 1)  (i - 1);
        if (val  dp[cur][mid]) {
            dp[cur][mid] = val;
            pos_opt = i;
        }
    }
 
 
    calc(cur, optL, pos_opt, l, mid - 1);
    calc(cur, pos_opt, optR, mid + 1, r);
 
}
 
 
void solve() {
    int n, k;
    cin  n  k;
    pos.pb(0);
    ll all = 0;
    int last = -1;
 
 
    for (int i = 1; i = n; ++i) {
        cin  a[i];
        if (a[i] == 0)
            pos.pb(i);
    }
    for (int i = 1; i = n; ++i) {
        if (a[i] == 0) {
            continue;
        }
        all += pref[a[i] + 1];
        for (int j = a[i]; j =1; --j) {
            pref[j]++;
        }
    }
    if (sz(pos) == 1) {
        cout  all;
        return;
    }
 
    for (int i = 1; i = n; ++i) {
        if (a[i] == 0)
            spec[i] = 1;
        spec[i] += spec[i - 1];
    }
 
    for (int j = k; j = 1; --j) {
        int cnt = 0;
        for (int i = 1; i = n; ++i) {
            val[i] = cnt;
            if (a[i]  0 && a[i]  j)
                cnt++;
        }
        cnt = 0;
        for (int i = n; i = 1; --i) {
            val[i] += cnt;
            if (a[i]  0 && a[i]  j)
                cnt++;
        }
 
        for(int i=1;i=n;++i){
            if(a[i]  0)
                val[i] = 0;
        }
        for (int i = 1; i = n; ++i) {
            pref_val[i] = pref_val[i - 1] + val[i];
        }
 
        if (j == k) {
            for (int i = 1; i  sz(pos); ++i) {
                dp[j & 1][i] = pref_val[pos[i]];
            }
        } else {
            calc(j & 1, 1, sz(pos) - 1, 1, sz(pos) - 1);
            for (int i = 1; i = n; ++i) {
                dp[j & 1][i] = max(dp[j & 1][i], dp[(j & 1) ^ 1][i]);
            }
        }
    }
    cout  dp[1][sz(pos) - 1] + all  n;
 
}
 
signed main() {
#ifdef zxc
    debug = 0;
    freopen(..input.txt, r, stdin);
    freopen(..output.txt, w, stdout);
#else
 
#endif zxc
    ios_basesync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(iosfixed);
    cout.precision(20);
 
    int t = 1;
    while (t--)
        solve();
    if (debug)
        cerr  endl  time    (1.0  clock()  CLOCKS_PER_SEC)  endl;
}