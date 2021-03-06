// base. https://pastebin.com/xrm0MU71
// tutorial. https://codeforces.com/blog/entry/71489

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <set>

using namespace std;

#define COUT(x) cout << #x << " = " << (x) << " (L" << __LINE__ << ")" << endl

template<class T> void printvec(const vector<T>& v) {
  for (auto x : v) { cout << x << " "; }
  cout << endl;
}
template<class T> void printtree(const vector< vector<T> >& tree) {
  for (long long i = 0; i < tree.size(); ++i) {
    cout << i + 1 << ": "; printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()
#define fr first
#define sc second
#define mp make_pair
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e18;
const ll MOD = 1000000007;  // 1e9 + 7

class UnionFind {
public:
  UnionFind(ll n) : par(n, -1), rnk(n, 0), cnt(n, 1), _size(n) {}

  bool same(ll x, ll y) {
    return root(x) == root(y);
  }
  // We use x if count(x) == count(y). if count(x) < count(y), we use y.
  void unite(ll x, ll y) {
    x = root(x); y = root(y);
    if (x == y) return;

    --_size;

    if (cnt[x] < cnt[y]) { swap(x, y); } // We check cnt
    par[y] = x;
    cnt[x] += cnt[y];
    if (rnk[x] == rnk[y]) { ++rnk[x]; }
  }
  ll root(ll x) {
    if (par[x] < 0) {
      return x;
    } else {
      return par[x] = root(par[x]);
    }
  }
  ll count(ll x) {
    return cnt[root(x)];
  }
  ll size() {
    return _size;
  }

private:
  vector<ll> par;
  vector<ll> rnk;
  vector<ll> cnt; // The number of vertices in each connected components.
  ll _size; // The number of connected components. Decreases by unite.
};

// int main(int argc, char** argv) {
//   ll N, M;
//   cin >> N >> M;
//   UnionFind tree(N);
//   rep(i, M) {
//     ll p, a, b;
//     cin >> p >> a >> b;
//     if (p == 0) { // Connect
//       tree.unite(a, b);
//     } else { // Judge
//       if (tree.same(a, b)) {
//         cout << "Yes" << endl;
//         cout << "size: " << tree.size() << endl;
//         cout << "count(" << a << "): " << tree.count(a) << endl;
//         cout << "count(" << b << "): " << tree.count(b) << endl;
//       } else {
//         cout << "No" << endl;
//         cout << "size: " << tree.size() << endl;
//         cout << "count(" << a << "): " << tree.count(a) << endl;
//         cout << "count(" << b << "): " << tree.count(b) << endl;
//       }
//     }
//   }
// }

// Global Variables
ll n, m, k, q; // nodes, edges, centrals, queries

vector< vector<P> > adj; // (node) => The list of (node, weight)
vector<ll> dist; // The distance from nearest centrals.
vector<ll> baseTok; // The table of (token) => (node)
vector< vector<ll> > tokenIn; // The table of (node) => [token1, token2, ...]

// Dijkstra.
// calculate the dist.

void dijkstra() {
  priority_queue<P> q;
  rep(i, n) { // loop for nodes
    if (i < k) {
      q.emplace(0, i);
    } else {
      dist[i] = INF;
    }
  }
  // cout << "n: " << n << endl;
  // cout << "k: " << k << endl;
  // cout << "dist in dijkstra: "; printvec(dist);

  while (!q.empty()) {
    P p = q.top(); q.pop();
    ll curD = -p.fr;
    ll v = p.sc;
    if (curD != dist[v]) { continue; } // dist[v] was already updated, so ignore it.

    for (auto x : adj[v]) {
      ll u = x.fr;
      ll newD = curD + x.sc; // new distance
      if (newD < dist[u]) {
        dist[u] = newD;
        q.emplace(- newD, u);
      }
    }
  }
}

// Token and Edges

struct Edge {
  ll weight, n1, n2;
};

bool operator<(Edge a, Edge b) {
  return a.weight < b.weight;
}

vector<Edge> edges;

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> m >> k >> q;

  adj.resize(n);
  dist.resize(n);

  rep(i, m) {
    ll n1, n2, w;
    cin >> n1 >> n2 >> w;
    --n1; --n2; // 0-indexed
    adj[n1].emplace_back(n2, w);
    adj[n2].emplace_back(n1, w);
    edges.push_back({ w, n1, n2 });
  }

  baseTok.resize(2*q+5);
  tokenIn.resize(n+5);

  rep(query, q) {
    ll a, b;
    cin >> a >> b;
    --a; --b; // 0-indexed
    ll tk1 = 2*query; ll tk2 = 2*query+1;

    baseTok[tk1] = a;
    baseTok[tk2] = b;

    tokenIn[a].push_back(tk1);
    tokenIn[b].push_back(tk2);
  }

  // Calculate the shortest path from nearest centrals.
  dijkstra();

  // We update the weight of edge by using dist.
  // new weight = old weight + dist[n1] + dist[n2]
  for (auto &e : edges) {
    e.weight += dist[e.n1] + dist[e.n2];
  }

  // Now, the weights of edges are updated.
  // We want to find the shortest path in terms of maximum weight in each path.

  // We use offline method here.

  vector<ll> ans(q); // ans contains the result of each query.

  sort(all(edges)); // Sort edges in increasing order.

  UnionFind uf(n);
  for (auto e : edges) {
    if (uf.same(e.n1, e.n2)) { continue; } // already connected.

    // Here, e.n1 and e.n2 is not connected yet.
    ll small = uf.root(e.n1);
    ll large = uf.root(e.n2);
    if (uf.count(small) > uf.count(large)) { swap(small, large); }

    // Now, the root of e.n1 and e.n2 are small and large. They are not
    // connected yet. small is lower rank, so small is merged to large

    // Next, we search "a token pair" which is connected by this edge.
    for (int token : tokenIn[small]) {
      int oth = token^1; // The other side of this token.
      int query = token/2;
      int oth_n = baseTok[oth];
      if (uf.root(oth_n) == large) { // found. small and large are connected.
        ans[query] = e.weight;
      }
      tokenIn[large].push_back(token);
    }
    tokenIn[small].clear(); tokenIn[small].shrink_to_fit();

    uf.unite(large, small);
  }

  // Now, ans is calculated.
  for (auto x : ans) {
    cout << x << endl;
  }
}
