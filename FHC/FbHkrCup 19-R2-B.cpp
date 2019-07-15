/*
    As in editorial dsu in O(n*m), than knapstack for minimizing difference.
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
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
const int MAXN = 4100 + 100;
const int LOG = 22;
const int mod = 1e9 + 7;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
int parent[MAXN];
int siz[MAXN];
 
 
void init_dsu(int n) {
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        siz[i] = 1;
    }
}
 
int get_parent(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = get_parent(parent[v]);
}
 
 
void union_set(int a, int b) {
    a = get_parent(a);
    b = get_parent(b);
    if (a != b) {
        if (siz[a] < siz[b])
            swap(a, b);
        parent[b] = a;
        siz[a] += siz[b];
    }
}
 
int dp[MAXN][MAXN];
 
bool clr[MAXN];
 
void solve() {
    int n, m;
    cin >> n >> m;
    init_dsu(n);
    for (int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        while (l <= r) {
            union_set(l, r);
            l++;
            r--;
        }
    }
 
    vector<pii> c;
    for (int i = 1; i <= n; ++i) {
        if (get_parent(i) == i) {
            c.pb({i, siz[i]});
        }
    }
 
    int N = sz(c);
    for (int i = 0; i <= N; ++i) {
        memset(dp[i], 0, sizeof dp[i]);
    }
 
    dp[0][0] = 1;
    for (int i = 0; i < N; ++i) {
        int val = c[i].se;
        for (int j = 0; j <= n; ++j) {
            if (dp[i][j])
                dp[i + 1][j] = 1;
        }
        for (int j = 0; j + val <= n; ++j) {
            if (dp[i][j]) {
                dp[i + 1][j + val] = 1;
            }
        }
    }
 
    int pos = -1, best = inf_int;
    for (int j = 0; j <= n; ++j) {
       // dout <<"HAVE " << j<<" "<<dp[N][j]<< " "<<abs((n - j) - j)<<endl;
        if (dp[N][j] && abs((n - j) - j) < best) {
            pos = j;
            best = abs((n - j) - j);
        }
    }
    dout << "best " << best << endl;
    memset(clr, 0, sizeof clr);
 
    int x = N, y = pos;
    while (x >= 1) {
        assert(dp[x][y] == 1);
        if (dp[x - 1][y] == 1) {
            x--;
        } else {
            x--;
            y = y - c[x].se;
            clr[c[x].fi] = 1;
        }
    }
 
 
    for(int i=1;i<=n;++i){
        int v = get_parent(i);
        if(clr[v])
            cout << 1;
        else
            cout << 0;
    }
 
 
}
 
signed main() {
#ifdef zxc
    debug = 0;
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#else
 
#endif //zxc
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(20);
 
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
        cout << "\n";
    }
 
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}