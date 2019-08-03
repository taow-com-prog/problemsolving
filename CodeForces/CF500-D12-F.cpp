/*
    Like in the editorial, solution using D&C. split the items by treir position sorted by time.  
*/
 
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
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
const int MAXQ = 20000 + 100;
const int MAXB = 4001;
int dp[MAXN][MAXB];
 
struct item {
    int c, h, t;
 
    bool operator<(const item &o) const {
        return t < o.t;
    }
};
 
vector<int> quer[2 * MAXN];
 
item X[MAXN];
 
int a[MAXQ], b[MAXQ];
int Lid[MAXQ], Rid[MAXQ];
int ans[MAXQ];
 
void add(int v, int tl, int tr, int l, int r, int id) {
    if (l >= r)
        return;
    if (l < tl || r > tr)
        return;
    int tm = (tl + tr) >> 1;
    if (l <= tm && r > tm) {
        quer[v].pb(id);
        return;
    }
    add(v * 2, tl, tm, l, r, id);
    add(v * 2 + 1, tm + 1, tr, l, r, id);
 
}
 
void calc(int v, int tl, int tr) {
    if (tl >= tr)
        return;
    int tm = (tl + tr) >> 1;
    if (!quer[v].empty()) {
        //left part
        memset(dp[tm], 0, sizeof dp[tm]);
        for (int j = X[tm].c; j < MAXB; ++j) {
            dp[tm][j] = X[tm].h;
        }
 
        for (int i = tm - 1; i >= tl; --i) {
            for (int j = 0; j < MAXB; ++j) {
                dp[i][j] = dp[i + 1][j];
                if (j >= X[i].c)
                    dp[i][j] = max(dp[i][j], dp[i + 1][j - X[i].c] + X[i].h);
            }
        }
 
        // right part
        memset(dp[tm + 1], 0, sizeof dp[tm + 1]);
        for (int j = X[tm + 1].c; j < MAXB; ++j) {
            dp[tm + 1][j] = X[tm + 1].h;
        }
        for (int i = tm + 2; i <= tr; ++i) {
            for (int j = 0; j < MAXB; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j >= X[i].c) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - X[i].c] + X[i].h);
                }
            }
        }
 
 
        for (int id:quer[v]) {
            int val = 0;
            for (int j = 0; j <= b[id]; ++j) {
                val = max(val, dp[Lid[id]][j] + dp[Rid[id]][b[id] - j]);
            }
            ans[id] = val;
        }
    }
 
 
    calc(v * 2, tl, tm);
    calc(v * 2 + 1, tm + 1, tr);
}
 
void solve() {
    int n, p;
    cin >> n >> p;
 
    for (int i = 1; i <= n; ++i) {
        cin >> X[i].c >> X[i].h >> X[i].t;
    }
    sort(X + 1, X + n + 1);
    int q;
    cin >> q;
    for (int j = 1; j <= q; ++j) {
        cin >> a[j] >> b[j];
 
        int l = n + 1, r = 0;
        for (int i = 1; i <= n; ++i) {
            if (X[i].t +p - 1 >= a[j]) {
                l = i;
                break;
            }
        }
        for (int i = n; i >= 1; --i) {
            if (X[i].t <= a[j]) {
                r = i;
                break;
            }
        }
        if (l > r) {
 
        } else if (l == r) {
            if (X[l].c <= b[j]) {
                ans[j] = X[l].h;
            }
        } else {
            add(1, 1, n, l, r, j);
            Lid[j] = l;
            Rid[j] = r;
        }
    }
    calc(1,1,n);
    for(int i = 1;i<= q;++i){
        cout << ans[i]<<"\n";
    }
 
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