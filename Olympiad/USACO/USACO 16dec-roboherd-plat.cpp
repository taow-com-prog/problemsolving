/*
    Like in second solution in editorial. 
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
const int MAXN = 1e5 + 100;
const int LOG = 25;
const int mod = 1e9 + 7;
const int MX = 1 * (1e7 + 100);
typedef long long li;
const li MOD = 1000000000949747713ll;


struct vertex {
    int l, r;
    int val;
};
vector<int> dif[MAXN];
int len[MAXN];

vertex mem[MX];
int top = 1;

inline int get_top() {
    return top++;
}

inline int get_top(int l, int r) {
    int v = get_top();
    mem[v].l = l;
    mem[v].r = r;
    mem[v].val = min(mem[l].val, mem[r].val);
    return v;
}

int build(int tl, int tr) {
    if (tl == tr) {
        int v = get_top();
        if (len[tl] == 0) {
            mem[v].val = inf_int;
        } else {
            mem[v].val = dif[tl][0];
        }
        mem[v].l = 0;
        return v;
    } else {
        int tm = (tl + tr) >> 1;
        return get_top(build(tl, tm), build(tm + 1, tr));
    }
}

#define left mem[v].l,tl,tm
#define right mem[v].r,tm+1,tr

int update(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        assert(mem[v].l + 1 <= len[tl]);
        int nv = get_top();
        mem[nv].l = mem[v].l + 1;
        if (mem[v].l + 1 == len[tl]) {
            mem[nv].val = inf_int;
        } else {
            dout << "new update " << dif[tl][mem[v].l + 1] << endl;
            mem[nv].val = dif[tl][mem[v].l + 1];
        }
        return nv;
    } else {
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            return get_top(update(left, pos), mem[v].r);
        } else {
            return get_top(mem[v].l, update(right, pos));
        }
    }
}

int get_mn(int v, int tl, int tr, int l, int r) {
    if (l > tr || r < tl)
        return inf_int;
    if (l <= tl && tr <= r) {
        return mem[v].val;
    } else {
        int tm = (tl + tr) >> 1;
        return min(get_mn(left, l, r), get_mn(right, l, r));
    }
}

int pos = -1;

void find_pos(int v, int tl, int tr, int l, int r, int val) {
    if (l > tr || r < tl)
        return;
    if (pos != -1)
        return;
    if (mem[v].val > val)
        return;
    if (tl == tr) {
        assert(mem[v].val == val);
        pos = tl;
    } else {
        int tm = (tl + tr) >> 1;
        find_pos(left, l, r, val);
        find_pos(right, l, r, val);
    }
}


int mark(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        assert(mem[v].val != inf_int);
        int nv = get_top();
        mem[nv].val = inf_int;
        return nv;
    } else {
        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            return get_top(mark(left, pos), mem[v].r);
        } else {
            return get_top(mem[v].l, mark(right, pos));
        }
    }
}


struct event {
    int root;
    int init_root;
    ll base_cost;
    ll min_edge;
    ll cost;
    int pos;

    bool operator<(const event &o) const {
        return cost < o.cost;
    }
};

int n;

struct temp_e {
public:
    bool operator()(event *a, event *b) {
        return a->base_cost + a->min_edge > b->base_cost + b->min_edge;
    }
};


event *update(event *e) {
    int val = get_mn(e->root, 1, n, e->pos, n);
    assert(val == e->min_edge);
    assert(val < inf_int);
    pos = -1;
    find_pos(e->root, 1, n, e->pos, n, val);
    assert(pos != -1);


    event *temp = new event;
    temp->root = update(e->init_root, 1, n, pos);
    temp->init_root = temp->root;
    temp->base_cost = e->base_cost + e->min_edge;
    temp->pos = pos;
    temp->min_edge = get_mn(temp->root, 1, n, pos, n);
    dout << "undate onn : " << temp->base_cost + temp->min_edge << endl;

    e->root = mark(e->root, 1, n, pos);
    e->min_edge = get_mn(e->root, 1, n, e->pos, n);
    dout << "upgrade too : " << e->base_cost + e->min_edge << endl;

    return temp;
}

void solve() {
    int k;
    cin >> n >> k;
    ll init_cost = 0;
    for (int i = 1; i <= n; ++i) {
        int m;
        cin >> m;
        vector<int> vals;
        for (int e = 1; e <= m; ++e) {
            int x;
            cin >> x;
            vals.pb(x);
        }
        len[i] = sz(vals) - 1;
        sort(all(vals));
        init_cost += vals[0];
        for (int e = 1; e < m; ++e) {
            dif[i].pb(vals[e] - vals[e - 1]);
        }

        for (int v:dif[i]) {
            dout << v << " ";
        }
        dout << endl;
    }

    int root = build(1, n);
    event *e1 = new event();
    e1->root = root;
    e1->init_root = root;
    e1->base_cost = init_cost;
    e1->min_edge = get_mn(root, 1, n, 1, n);
    e1->pos = 1;


    priority_queue<event *, vector<event *>, temp_e> ss;
    ss.push(e1);

    ll res = init_cost;

    for (int j = 2; j <= k; ++j) {
        auto x = ss.top();
        ss.pop();
        res += x->base_cost + x->min_edge;
        dout << "ADD : " << x->base_cost << " " << x->min_edge << " -- " << x->pos << endl;

        auto x1 = update(x);
        if (x1->min_edge != inf_int)
            ss.push(x1);

        if (x->min_edge != inf_int)
            ss.push(x);
    }

    cout << res << "\n";


}

signed main() {
#ifdef zxc
    debug = 1;
    freopen("../input.txt", "r", stdin);
    //freopen("../output.txt", "w", stdout);
#else
    freopen("roboherd.in", "r", stdin);
    freopen("roboherd.out", "w", stdout);

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