/*
    The same as in editorial:
    last first two subtasks: using scan line and segment tree. The answer is found using binary search. Complexity ( (n + m) * log m * Log (n + m));
    The last subtasks using segment tree and two pointers. In vertex I save the maximal value of suffix,prefix and total.  
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
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;
 
#define y1 agasdgaf
int x1[MAXN], x2[MAXN], y1[MAXN], y2[MAXN];
 
struct event {
    int x;
    int l, r;
    int add;
    int val;
 
    bool operator<(const event &o) const {
        if (x != o.x)
            return x < o.x;
        if (add != o.add)
            return add == 1;
        return false;
    }
};
 
ll t[4 * MX];
ll add[4 * MX];
#define left v<<1,tl,tm
#define right v<<1|1,tm+1,tr
 
void build(int v, int tl, int tr) {
    t[v] = add[v] = 0;
    if (tl == tr) {
 
    } else {
        int tm = (tl + tr) >> 1;
        build(left);
        build(right);
    }
}
 
inline void upd(int v) {
    t[v] = min(t[v << 1] + add[v << 1], t[v << 1 | 1] + add[v << 1 | 1]);
}
 
void update(int v, int tl, int tr, int l, int r, ll val) {
    if (l > tr || r < tl)
        return;
    if (l <= tl && tr <= r) {
        add[v] += val;
        return;
    } else {
        int tm = (tl + tr) >> 1;
        update(left, l, r, val);
        update(right, l, r, val);
        upd(v);
    }
}
 
 
inline ll get(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl)
        return inf_ll;
    if (l <= tl && tr <= r) {
        return t[v] + add[v];
    } else {
        int tm = (tl + tr) >> 1;
        ll val1 = get(left, l, r);
        ll val2 = get(right, l, r);
        return add[v] + min(val1, val2);
    }
}
 
int c[MAXN];
 
 
 
struct vertex {
    int pref, suf, val;
    int spec;
};
 
 
vertex t2[4 * MX];
 
void combine(int v, int tl, int tr, vertex &l, vertex &r) {
    if (t2[v].spec) {
        t2[v].pref = 0;
        t2[v].suf = 0;
        t2[v].val = 0;
    } else {
        if (tl < tr) {
            t2[v].pref = l.pref;
            t2[v].suf = r.suf;
            t2[v].val = max(l.val, max(r.val, l.suf + r.pref));
            int tm = (tl + tr) >> 1;
            if (l.val == tm - tl + 1) {
                assert(l.val == l.pref);
                t2[v].pref = l.pref + r.pref;
            }
            if (r.val == tr - tm) {
                assert(r.val == r.pref);
                t2[v].suf = r.suf + l.suf;
            }
        } else {
            t2[v].pref = t2[v].suf = t2[v].val = 1;
        }
    }
}
 
 
void build2(int v, int tl, int tr) {
    if (tl == tr) {
        t2[v].pref = t2[v].suf = t2[v].val = 1;
        t2[v].spec = 0;
    } else {
        int tm = (tl + tr) >> 1;
        build2(left);
        build2(right);
        combine(v, tl, tr, t2[v << 1], t2[v << 1 | 1]);
    }
}
 
void update2(int v, int tl, int tr, int l, int r, int x) {
    if (l > tr || r < tl)
        return;
    if (l <= tl && tr <= r) {
        t2[v].spec += x;
        combine(v, tl, tr, t2[v << 1], t2[v << 1 | 1]);
        return;
    } else {
        int tm = (tl + tr) >> 1;
        update2(left, l, r, x);
        update2(right, l, r, x);
        combine(v, tl, tr, t2[v << 1], t2[v << 1 | 1]);
    }
}
 
vector<int> add_rec[MAXN];
vector<int> rem_rec[MAXN];
 
 
void solve() {
    int n, m;
    cin >> n >> m;
    ll B;
    cin >> B;
    int k;
    cin >> k;
    for (int i = 1; i <= k; ++i) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i] >> c[i];
 
        add_rec[x1[i]].pb(i);
        rem_rec[x2[i] + 1].pb(i);
    }
 
    int l = 1, r = min(n, m);
    int ans = 0;
 
    if(B == 0) {
        build2(1, 1, m);
        dout << t2[1].val << endl;
        int r = 1;
        for (int v:add_rec[1]) {
            update2(1, 1, m, y1[v], y2[v], 1);
        }
        for (int i = 1; i <= n; ++i) {
            for (int v:rem_rec[i]) {
                update2(1, 1, m, y1[v], y2[v], -1);
            }
            while (r <= n && t2[1].val >= r - i + 1) {
                ans = max(ans, r - i + 1);
                r++;
                for (int v:add_rec[r]) {
                    update2(1, 1, m, y1[v], y2[v], 1);
                }
            }
        }
        cout << ans << "\n";
 
 
        return;
    }
 
 
    while (l <= r) {
        int mid = (l + r) >> 1;
        vector<event> cc;
        dout << "mid " << mid << endl;
        for (int i = 1; i <= k; ++i) {
            event e1, e2;
            e1.x = x1[i] - mid + 1;
            e1.l = y1[i] - mid + 1;
            e1.r = y2[i];
            e1.val = c[i];
            e1.add = 1;
 
            dout << e1.x << " " << e1.l << " " << e1.r << " " << e1.val << " " << e1.add << endl;
 
            e2.x = x2[i];
            e2.l = y1[i] - mid + 1;
            e2.r = y2[i];
            e2.val = -c[i];
            e2.add = -1;
            cc.pb(e1);
            cc.pb(e2);
        }
        sort(all(cc));
        int top = 0;
        build(1, 1, m);
 
        bool flag = false;
        for (int x = 1; x <= n && x + mid - 1 <= n; ++x) {
            while (top < sz(cc) && cc[top].x < x) {
                update(1, 1, m, cc[top].l, cc[top].r, cc[top].val);
                top++;
            }
            while (top < sz(cc) && cc[top].x == x && cc[top].add == 1) {
                update(1, 1, m, cc[top].l, cc[top].r, cc[top].val);
                top++;
            }
 
            ll val = get(1, 1, m, 1, m - mid + 1);
 
            if (val <= B) {
                flag = true;
                break;
            }
 
        }
 
        if (flag) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
 
 
    }
 
    cout << ans << "\n";
}
 
signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
    //freopen("../output.txt", "w", stdout);
#else
    //freopen("roboherd.in", "r", stdin);
    //freopen("roboherd.out", "w", stdout);
 
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