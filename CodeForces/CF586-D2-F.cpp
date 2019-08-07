
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
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
 
int a[MAXN], b[MAXN], c[MAXN];
 
vector<tuple<int, int, int, int> > get_all(int l, int r) {
    int n = r - l + 1;
    int max_mask = 1;
    for (int i = 1; i <= n; ++i) {
        max_mask = max_mask * 3;
    }
    vector<tuple<int, int, int, int> > res;
    for (int mask = 0; mask < max_mask; ++mask) {
 
        int x = mask;
        int A = 0, B = 0, C = 0;
        for (int i = r; i >= l; --i) {
            int id = x % 3;
            x = x / 3;
            if (id == 0) {
                A += a[i];
                B += b[i];
            } else if (id == 1) {
                A += a[i];
                C += c[i];
            } else {
                B += b[i];
                C += c[i];
            }
 
        }
        dout << "mask " << mask << " " << A << " " << B << " " << C << endl;
        res.emplace_back(mask, A, B, C);
    }
    return res;
}
 
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
        dout << "get " << a[i] << " " << b[i] << " " << c[i] << endl;
    }
 
    string temp[3];
    temp[0] = "LM";
    temp[1] = "LW";
    temp[2] = "MW";
    if (n == 1) {
        if (!a[1] && !b[1]) {
            cout << temp[0];
            return;
        }
        if (!a[1] && !c[1]) {
            cout << temp[1];
            return;
        }
        if (!b[1] && !c[1]) {
            cout << temp[2];
            return;
        }
        cout << "Impossible";
        return;
    }
 
    int mid = n / 2;
 
    auto res1 = get_all(1, mid);
    auto res2 = get_all(mid + 1, n);
 
 
    map<pii, pii> mp;
    for (auto &x:res2) {
        int mask, a, b, c;
        tie(mask, a, b, c) = x;
 
        if (mp.count({b - a, c - a})) {
            mp[{b - a, c - a}] = max(mp[{b - a, c - a}], {a, mask});
        } else {
            mp[{b - a, c - a}] = {a, mask};
        }
    }
 
    int ans = -inf_int;
    int mask1 = -1;
    int mask2;
    for (auto &x:res1) {
        int mask, a, b, c;
        tie(mask, a, b, c) = x;
 
        if (mp.count({a - b, a - c})) {
            auto cur = mp[{a - b, a - c}];
            if (cur.fi + a > ans) {
                ans = cur.fi + a;
                mask1 = mask;
                mask2 = cur.se;
            }
        }
 
    }
    if (ans == -inf_int) {
        cout << "Impossible";
        return;
    }
 
    vector<string> res;
    for (int i = n; i >= mid + 1; --i) {
        res.pb(temp[mask2 % 3]);
        mask2 = mask2 / 3;
    }
    for (int i = mid; i >= 1; --i) {
        res.pb(temp[mask1 % 3]);
        mask1 = mask1 / 3;
    }
 
    reverse(all(res));
    for (auto x:res) {
        cout << x << "\n";
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