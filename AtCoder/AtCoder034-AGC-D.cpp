/*
	Min cost max flow like in editorial.
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
const int MAXN = 2e5 + 100;
const int LOG = 25;
const int mod = 998244353;
const int MX = 1e6 + 100;
typedef long long li;
const li MOD = 1000000000949747713ll;

int ax[MAXN], ay[MAXN], ac[MAXN];
int bx[MAXN], by[MAXN], bc[MAXN];


struct Edge {
    int a, b, c, flow, cost;
};

struct MIN_FLOW {
    vector<Edge> e;
    vector<int> g[MAXN];
    int n, s, t;

    int id[MAXN];
    ll dis[MAXN];
    int from[MAXN];

    void init(int N, int S, int T) {
        n = N;
        s = S;
        t = T;
    }

    void add_edge(int a, int b, int c, int cost) {
        Edge e1 = {a, b, c, 0, cost};
        Edge e2 = {b, a, 0, 0, -cost};
        g[a].pb(e.size());
        e.pb(e1);
        g[b].pb(e.size());;
        e.pb(e2);
    }

    ll get_val(int k) {
        int flow = 0;
        ll cost = 0;

        while (1) {
            queue<int> q;
            fill(id, id + n, 0);
            fill(dis, dis + n, -inf_ll);
            dis[s] = 0;
            id[s] = 1;
            q.push(s);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                id[v] = 0;
                for (int ind:g[v]) {
                    Edge &edge = e[ind];
                    int to = edge.b;
                    if (edge.c > edge.flow && dis[edge.b] < dis[v] + edge.cost) {
                        if (id[to] == 0) {
                            q.push(to);
                            id[to] = 1;
                        }
                        dis[to] = dis[v] + edge.cost;
                        from[to] = ind;
                    }
                }

            }
            if (dis[t] == -inf_ll)
                break;

            int addflow = min(inf_int, k - flow);
            int v = t;
            while (v != s) {
                int ind = from[v];
                addflow = min(addflow, e[ind].c - e[ind].flow);
                v = e[ind].a;
            }

            v = t;
            while (v != s) {
                int ind = from[v];
                cost += 1ll * e[ind].cost * addflow;
                e[ind].flow += addflow;
                e[ind ^ 1].flow -= addflow;
                v = e[ind].a;
            }
            flow += addflow;
            if (flow == k)
                break;
        }

        return cost;
    }


} flow;

int IDa[MAXN], IDb[MAXN];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> ax[i] >> ay[i] >> ac[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> bx[i] >> by[i] >> bc[i];
    }

    int top = 0;
    int speca[4];
    int specb[4];
    for (int i = 0; i < 4; ++i) {
        speca[i] = top++;
        specb[i] = top++;
    }
    int S = top++;
    int T = top++;

    for (int i = 1; i <= n; ++i) {
        IDa[i] = top++;
        flow.add_edge(S,IDa[i],ac[i],0);
        flow.add_edge(IDa[i], speca[0], inf_int, ax[i] + ay[i]);
        flow.add_edge(IDa[i], speca[1], inf_int, ax[i] - ay[i]);
        flow.add_edge(IDa[i], speca[2], inf_int, -ax[i] + ay[i]);
        flow.add_edge(IDa[i], speca[3], inf_int, -ax[i] - ay[i]);
    }

    for (int i = 1; i <= n; ++i) {
        IDb[i] = top++;
        flow.add_edge(IDb[i],T,bc[i],0);
        flow.add_edge(specb[0], IDb[i], bc[i], bx[i] + by[i]);
        flow.add_edge(specb[1], IDb[i], bc[i], bx[i] - by[i]);
        flow.add_edge(specb[2], IDb[i], bc[i], -bx[i] + by[i]);
        flow.add_edge(specb[3], IDb[i], bc[i], -bx[i] - by[i]);
    }

    flow.add_edge(speca[0], specb[3], inf_int, 0);
    flow.add_edge(speca[1], specb[2], inf_int, 0);
    flow.add_edge(speca[2], specb[1], inf_int, 0);
    flow.add_edge(speca[3], specb[0], inf_int, 0);

    flow.init(top+2,S,T);

    ll val = flow.get_val(inf_int);
    cout << val <<"\n";

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