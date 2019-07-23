/*
    Solved using D&C and Persistent Segment Tree.
    O(n*k*log^2) approach got TL.

    To solve it, there is optimization, we can calculate once number_of_distinct(optR, mid), then other values
    number_of_distince(i, mid) where  optL <= i <= optR , we can see update using information where is next position of the value a[i]
*/

//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf_int = 1e9 + 100;
const ll inf_ll = 4e18;
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
const int MAXN = 1e5 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e7 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;

struct vertex {
    int l, r;
    int sum;

    vertex() {
        l = r = 0;
        sum = 0;
    }
};

int top_t = 1;
vertex t[MX];

int get_new() {
    return top_t++;
}

int get_new(int l, int r) {
    int v = top_t++;
    t[v].l = l;
    t[v].r = r;
    t[v].sum = t[l].sum + t[r].sum;
    return v;
}

int build(int tl, int tr) {
    if (tl == tr)
        return get_new();
    else {
        int tm = (tl + tr) >> 1;
        return get_new(build(tl, tm), build(tm + 1, tr));
    }
}

#define left t[v].l,tl,tm
#define right t[v].r,tm+1,tr

int get(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl)
        return 0;
    if (l <= tl && tr <= r) {
        return t[v].sum;
    } else {
        int tm = (tl + tr) >> 1;
        return get(left, l, r) + get(right, l, r);
    }
}

int update(int v, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        int nv = get_new();
        t[nv].sum = t[v].sum + val;
        return nv;
    } else {
        int tm = (tl + tr) >> 1;
        if (pos <= tm)
            return get_new(update(left, pos, val), t[v].r);
        return get_new(t[v].l, update(right, pos, val));
    }
}

int a[MAXN];

int root[MAXN];

int n;

int cost(int l, int r) {
    return get(root[r], 1, n, l, r);
}

int dp[2][MAXN];
int nxt[MAXN];

void calc(int cur, int optl, int optr, int l, int r) {
    if (l > r)
        return;
    int mid = (l + r) / 2;
    int pos = -1;
    int j = min(optr, mid);
    int c = cost(j, mid);
    pos = j;
    dp[cur][mid] = c + dp[cur ^ 1][j - 1];
    j--;
    while (j >= optl) {
        if (nxt[j] > mid)
            c++;

        if (dp[cur ^ 1][j - 1] + c >= dp[cur][mid]) {
            pos = j;
            dp[cur][mid] = dp[cur ^ 1][j - 1] + c;
        }
        j--;
    }

    calc(cur, optl, pos, l, mid - 1);
    calc(cur, pos, optr, mid + 1, r);
}

void solve() {
    cin >> n;
    int k;
    cin >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    map<int, int> mp;
    root[0] = build(1, n);
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        root[i] = update(root[i - 1], 1, n, i, 1);
        if (mp.count(x)) {
            root[i] = update(root[i], 1, n, mp[x], -1);
        }
        mp[x] = i;
    }

    dp[1][0] = -inf_int;
    for (int i = 1; i <= n; ++i) {
        dp[1][i] = cost(1, i);
    }

    mp.clear();
    for (int i = n; i >=1; --i) {
        if (mp.count(a[i])) {
            nxt[i] = mp[a[i]];
        } else {
            nxt[i] = n + 1;
        }
        mp[a[i]] = i;
    }

    for (int i = 2; i <= k; ++i) {
        calc(i & 1, 1, n, 1, n);
    }

    cout << dp[k & 1][n] << "\n";


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