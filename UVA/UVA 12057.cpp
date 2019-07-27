/*
    Knuth

    To get AC, needed convert float values to integer.
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
const int MAXN = 1000 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e7 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;


int a[MAXN];
int pref[MAXN];
int dp[MAXN][MAXN];
int best[MAXN][MAXN];
string res[MAXN];

void fun(int l, int r) {
    if (l == r)
        return;
    int j = best[l][r];
    for (int i = l; i <= j; ++i) {
        res[i].pb('0');
    }
    for (int i = j + 1; i <= r; ++i) {
        res[i].pb('1');
    }

    fun(l, j);
    fun(j + 1, r);


}

void solve() {
    int n;
    cin >> n;
    if (n == 0)
        exit(0);

    for (int i = 1; i <= n; ++i) {
        dbl x;
        cin >> x;
        a[i] = x * 10000 + 0.5;
        pref[i] = pref[i - 1] + a[i];
    }
    for (int i = 1; i <= n; ++i) {
        dp[i][i] = 0;
        best[i][i] = i;
    }


    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l <= n && l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            dp[l][r] = inf_int;
            for (int j = best[l][r - 1]; j <= best[l + 1][r]; ++j) {
                dbl val = dp[l][j] + dp[j + 1][r] + pref[r] - pref[l - 1];
                if (val < dp[l][r]) {
                    dp[l][r] = val;
                    best[l][r] = j;
                }
            }
            dout << l << " " << r << " : " << best[l][r] << endl;
        }
    }

    for (int i = 1; i <= n; ++i) {
        res[i] = "";
    }
    int val = dp[1][n];

    cout << val/10000<<".";
    val = val%10000;
    vector<int> ans;
    for(int i = 0;i<4;++i){
        ans.pb(val%10);
        val = val/10;
    }
    reverse(all(ans));
    for(int v:ans){
        cout <<v;
    }
    cout<<"\n";

    fun(1, n);
    for (int i = 1; i <= n; ++i) {
        cout << res[i] << "\n";
    }
    cout << "\n";

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

    int t = inf_int;
    while (t--)
        solve();
    if (debug)
        cerr << endl << "time : " << (1.0 * clock() / CLOCKS_PER_SEC) << endl;
}