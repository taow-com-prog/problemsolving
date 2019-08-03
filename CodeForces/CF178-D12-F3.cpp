/*
    Dp on the trie. 
    dp[v][k] - get on node k elements

    compexilty (n * k + n * 500 * log(A)).
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
const int MAXN = 2000 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
int n, k;
int dp[2 * MAXN][MAXN];
string a[MAXN];
 
map<char, int> nxt[MX];
int sum[MX]; // num of strings
int top = 1;
int h[MX];
int ID[MX];
int leaf[MX];
 
int get_top() {
    assert(top < MX);
    return top++;
}
 
int top_id = 0;
 
int get_id() {
    return top_id++;
}
 
void add_string(string &a) {
    int v = 0;
    for (char c:a) {
        if (nxt[v].count(c) == 0) {
            int to = get_top();
            h[to] = h[v] + 1;
            nxt[v][c] = to;
        }
        v = nxt[v][c];
        sum[v]++;
    }
 
 
}
 
 
int temp[MAXN];
 
int calc(int v) {
    int id = -1;
    if (nxt[v].size() == 0) {
 
        id = get_id();
        for (int i = 0; i <= sum[v] && i <= k; ++i) {
            dp[id][i] = (i * (i - 1)) / 2 * (h[v] - 1);
        }
        return id;
    }
    if (nxt[v].size() == 1) {
        int to = nxt[v].begin()->se;
        return calc(to);
    }
 
    int cur = 0;
    for (auto x:nxt[v]) {
        int to = x.se;
        int id_to = calc(to);
        if (id == -1) {
            id = id_to;
            cur += sum[to];
            continue;
        }
 
        fill(temp, temp + k + 1, 0);
 
        for (int i = 0; i <= min(k, cur); ++i) {
            for (int j = 0; j <= sum[to] && i + j <= k; ++j) {
                temp[i + j] = max(temp[i + j], dp[id][i] + dp[id_to][j] + i * j * h[v]);
            }
        }
        cur += sum[to];
 
 
        for (int j = 0; j <= k; ++j) {
            dp[id][j] = temp[j];
        }
    }
    assert(id != -1);
    return id;
 
}
 
void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i].pb('#');
        add_string(a[i]);
    }
 
    int id = calc(0);
 
    cout << dp[id][k] << "\n";
 
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