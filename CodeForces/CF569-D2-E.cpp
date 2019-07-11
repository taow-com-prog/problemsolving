/*
    As optimised version in editorial. Checked only for parite of letters.
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
const int MAXN = 1e6 + 100;
const int LOG = 25;
const int mod = 924844033;
const int MX = 5e5 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
int letters[30];
int A;
 
char edge_on[MAXN];
int top = 0;
vector<pii> g[500];
vector<pii> gr[500];
 
inline int add_edge(int a, int b) {
    g[a].pb({b, top});
    gr[b].pb({a, top});
    edge_on[top] = 1;
    return top++;
}
 
int put_let[500][2];
 
 
int n;
 
int clr[512];
vector<int> order;
 
void dfs(int v) {
    clr[v] = 1;
    for (pii x:g[v]) {
        if (edge_on[x.se]) {
            int to = x.fi;
            if (!clr[to])
                dfs(to);
        }
    }
    order.pb(v);
}
 
void dfs(int v, int val) {
    clr[v] = val;
    for (pii x:gr[v]) {
        if (edge_on[x.se]) {
            int to = x.fi;
            if (!clr[to]) {
                dfs(to, val);
            }
        }
    }
}
 
bool has_sol() {
    order.clear();
    memset(clr, 0, sizeof clr);
    for (int i = 0; i < 2 * n; ++i) {
        if (!clr[i])
            dfs(i);
    }
    reverse(all(order));
    int z = 1;
    memset(clr, 0, sizeof clr);
    for (int v:order) {
        if (!clr[v]) {
            dfs(v, z++);
        }
    }
 
    for (int i = 0; i < 2 * n; ++i) {
        if (clr[i] == clr[i ^ 1]) {
            return false;
        }
    }
    return true;
}
 
char a[512];
string s;
 
void fun(int pos, bool any) {
    if (pos == n) {
        for (int i = 0; i < n; ++i) {
            cout << a[i];
        }
        exit(0);
        return;
    }
 
    int can[2] = {false, false};
    for (int j = 0; j < 2; ++j) {
        edge_on[put_let[pos][j]] = 1;
        can[j] = has_sol();
        edge_on[put_let[pos][j]] = 0;
    }
    dout << "can " << pos << " " << can[0] << " " << can[1] << endl;
 
    if (any) {
        for (int j = 0; j < A; ++j) {
            if (can[letters[j]]) {
                edge_on[put_let[pos][letters[j]]] = 1;
                can[letters[j]] = 0;
                a[pos] = j + 'a';
                fun(pos + 1, any);
                edge_on[put_let[pos][letters[j]]] = 0;
            }
        }
        return;
    }
    if (can[letters[s[pos]]]) {
        int j = s[pos];
        edge_on[put_let[pos][letters[j]]] = 1;
        a[pos] = j + 'a';
        fun(pos + 1, any);
        edge_on[put_let[pos][letters[j]]] = 0;
    }
 
    for (int j = s[pos] + 1; j < A; ++j) {
        if (can[letters[j]]) {
            edge_on[put_let[pos][letters[j]]] = 1;
            can[letters[j]] = 0;
            a[pos] = j + 'a';
            fun(pos + 1, true);
            edge_on[put_let[pos][letters[j]]] = 0;
        }
    }
 
}
 
void solve() {
    string let;
    cin >> let;
    A = sz(let);
    for (int i = 0; i < sz(let); ++i) {
        if (let[i] == 'C')
            letters[i] = 1;
    }
    int m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int pos1, pos2;
        char a1, a2;
        cin >> pos1 >> a1 >> pos2 >> a2;
        pos1--;
        pos2--;
        pos1 = pos1 * 2;
        pos2 = pos2 * 2;
        if (a1 == 'C')
            pos1++;
        if (a2 == 'C')
            pos2++;
 
        add_edge(pos1, pos2);
        add_edge(pos2 ^ 1, pos1 ^ 1);
    }
 
    for (int i = 0; i < n; ++i) {
        put_let[i][0] = add_edge(i * 2 + 1, i * 2);
        put_let[i][1] = add_edge(i * 2, i * 2 + 1);
 
        edge_on[put_let[i][0]] = 0;
        edge_on[put_let[i][1]] = 0;
    }
 
    cin >> s;
    for (int i = 0; i < n; ++i) {
        s[i] -= 'a';
    }
    fun(0, 0);
 
 
    cout << -1;
}
 
signed main() {
#ifdef zxc
    debug = 1;
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