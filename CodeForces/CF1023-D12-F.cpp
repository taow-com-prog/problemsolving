/*
    As in editorial.
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
const int MAXN = 1e6 + 100;
const int LOG = 25;
const int mod = 1e9 + 7;
const int MX = 5e5 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
int h[MAXN];
 
struct DSU {
    int parent[MAXN];
    int total;
 
    void build(int n) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
        total = n;
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
            if (h[a] > h[b])
                swap(a, b);
            parent[b] = a;
            total--;
        }
    }
} comp1, comp2;
 
vector<int> g[MAXN];
 
int par[MAXN];
 
void dfs(int v, int p) {
    par[v] = p;
    for (int to:g[v]) {
        if (to == p)
            continue;
        h[to] = h[v] + 1;
        dfs(to, v);
 
    }
}
 
int A[MAXN], B[MAXN], C[MAXN];
 
bool used[MAXN];
 
void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    comp1.build(n);
    comp2.build(n);
    for (int i = 1; i <= k; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
        comp1.union_set(a, b);
    }
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        A[i] = a;
        B[i] = b;
        C[i] = c;
 
        if (comp1.get_parent(a) != comp1.get_parent(b)) {
            comp1.union_set(a, b);
            g[a].pb(b);
            g[b].pb(a);
            used[i] = 1;
        }
 
    }
 
 
    dfs(1, -1);
    for(int i=1;i<=m;++i){
        if(used[i])
            comp2.union_set(A[i],B[i]);
    }
    ll ans = 0;
    for (int i = 1; i <= m; ++i) {
        if (used[i])
            continue;
        int a = A[i];
        int b = B[i];
        while (true) {
            a = comp2.get_parent(a);
            b = comp2.get_parent(b);
            if (a == b)
                break;
            if (h[a] > h[b])
                swap(a, b);
            comp2.union_set(b, par[b]);
            ans += C[i];
        }
    }
    if(comp2.total != 1){
        cout << -1;
        return;
    }
 
    cout << ans;
 
 
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
 
    int t = 1;
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}