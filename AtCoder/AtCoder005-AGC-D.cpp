/*
    Like in editorial.
*/
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e8 + 100;
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
const int MAXN = 2000 + 100;
const int LOG = 25;
const int mod = 924844033;
const int MX = 5e5 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
 
int prv[MAXN][4];
int nxt[MAXN][4];
 
ll sum[MAXN];
 
void calc_sum() {
    for (int i = 0; i <= 2000; ++i) {
        sum[i] = 1ll * prv[i][0] + prv[i][1] + prv[i][2] + prv[i][3];
        sum[i] %= mod;
    }
}
 
inline void upd(int &x) {
    if (x >= mod)
        x -= mod;
}
 
inline void add(int &a, int b) {
    a += b;
    if (a >= mod)
        a -= mod;
}
 
ll fac[MAXN];
void solve() {
    fac[0] = 1;
    for(int i=1;i<MAXN;++i){
        fac[i] = (fac[i-1] * i)%mod;
    }
 
    int n, k;
    cin >> n >> k;
    prv[0][0] = 1;
    for (int i = 1; i <= k; ++i) {
        dout <<" start " << i << endl;
        calc_sum();
        memset(prv, 0, sizeof prv);
        for (int j = 0; j <= n; ++j) {
            prv[j][1] = sum[j];
        }
 
        int nxt_mask;
        for (int v = i; v <= n; v = v + k) {
            memset(nxt, 0, sizeof nxt);
            for (int j = 0; j <= n; ++j) {
                for (int mask = 0; mask < 4; ++mask) {
                    if (!prv[j][mask])
                        continue;
                    add(nxt[j][mask >> 1], prv[j][mask]);
                    if (!(mask & 1)) {
                        nxt_mask = mask | 1;
                        add(nxt[j + 1][nxt_mask >> 1], prv[j][mask]);
                    }
                    if (v + k <= n) {
                        nxt_mask = mask | 4;
                        add(nxt[j + 1][nxt_mask >> 1], prv[j][mask]);
                    }
                }
            }
            for (int j = 0; j <= n; ++j) {
                for (int mask = 0; mask < 4; ++mask) {
                    prv[j][mask] = nxt[j][mask];
 
                 //   dout << v <<" "<<j <<" "<<mask<< " : "<<nxt[j][mask]<<endl;
                }
            }
        }
    }
    calc_sum();
 
  /*  for(int i=0;i<=n;++i){
        dout<<i<<" : " << sum[i]<<" "<<endl;
    }*/
 
    ll ans = fac[n];
    for(int i=1;i<=n;++i){
        ll sign = 1;
        if(i & 1){
            sign = -1;
        }
        ans+= sign * (sum[i] * fac[n-i])%mod;
    }
    ans = (ans%mod + mod)%mod;
    cout << ans;
}
 
signed main() {
#ifdef zxc
    debug = 0;
    freopen("../input.txt", "r", stdin);
    // freopen("../output.txt", "w", stdout);
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