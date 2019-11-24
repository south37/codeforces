// base. https://pastebin.com/J8c8x2Fg
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

// The edge start -> end with weight.
struct Edge {
  Edge(ll w, ll s, ll e) : weight(w), start(s), end(e) {};
  ll weight, start, end;
};

bool operator<(Edge a, Edge b) {
  return a.weight < b.weight;
}

// Global Variables
ll n, m, k, q; // nodes, edges, centrals, queries

vector< vector<Edge> > graph; // (node) => The list of (node, weight)
vector<ll> dist; // The distance from nearest centrals.
vector<ll> closest; // closest[v] .. The closest central of v.
vector<Edge> paths;
vector< vector<Edge> > specTree; // Minimum spaning tree.

const int LOGN = 18;
vector< vector<ll> > ancester; // For LCA
vector< vector<ll> > weightToAnc; // For LCA
vector<int> depth; // For LCA. The depth in minimum spanning tree.

void dijkstra() {
  priority_queue<triple> q; // (distance, central, node)
  rep(v, k) {
    q.emplace(0, v, v);
  }
  rep(v, n) {
    closest[v] = -1; // initial value.
  }

  while(!q.empty()) {
    ll d, central, v;
    tie(d, central, v) = q.top(); q.pop();
    d *= -1;

    // alreday updated.
    if (closest[v] != -1) { continue; }

    closest[v] = central;
    dist[v] = d;
    for (Edge &e : graph[v]) {
      ll newD = d + e.weight;
      q.emplace(- newD, central, e.end);
    }
  }
}

// void root(int v) {
//   for (Edge& e : specTree[v]) {
//     if (e.end != ancester[v][0]) { // e is from child to parent
//       ancester[e.end][0] = v;
//       weightToAnc[e.end][0] = e.weight;
//       depth[e.end] = depth[v] + 1;
//       root(e.end);
//     }
//   }
// }

ll getanc(ll v, int exp) {
  if (ancester[v][exp] == -1) {
    ancester[v][exp] = getanc(getanc(v, exp-1), exp-1);
  }
  return ancester[v][exp];
}

ll lift(ll v, int dist) {
  if (dist == 0) {
    return v;
  }
  int exp = 31 - __builtin_clz(dist);
  return lift(getanc(v, exp), dist-(1<<exp));
}

void dfs(ll v, ll parent) {
  for (auto e : specTree[v]) { // (weight, e.start = v, e.end)
    if (e.end == parent) { continue; } // Skip parent

    ancester[e.end][0] = v;
    weightToAnc[e.end][0] = e.weight;
    depth[e.end] = depth[v] + 1;
    dfs(e.end, v);
  }
}

ll lca(ll u, ll v) {
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  u = lift(u, depth[u] - depth[v]);
  if (u == v) {
    return u;
  }

  for (int iExp = 31 - __builtin_clz(depth[u]); iExp >= 0; --iExp) {
    // cout << "iExp: " << iExp << endl;
    if (getanc(u, iExp) != getanc(v, iExp)) {
      u = getanc(u, iExp);
      v = getanc(v, iExp);
    }
  }

  return getanc(u, 0);
}

ll getweighttoanc(ll v, int exp) {
  if (weightToAnc[v][exp] == 0) {
    // Return the max in v to lift(v, 1<<exp).
    weightToAnc[v][exp] = max(getweighttoanc(v, exp-1), getweighttoanc(getanc(v, exp-1), exp-1));
  }
  return weightToAnc[v][exp];
}

ll liftw(ll v, int dist) {
  if (dist == 0) {
    return 0;
  }
  int exp = 31 - __builtin_clz(dist);
  return max(liftw(getanc(v, exp), dist - (1<<exp)), getweighttoanc(v, exp));

}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  cin >> n >> m >> k >> q;

  graph.resize(n);
  dist.resize(n);
  closest.resize(n);
  specTree.resize(n);
  ancester.assign(k, vector<ll>(LOGN + 5, -1));
  weightToAnc.assign(k, vector<ll>(LOGN + 5));
  depth.resize(k);

  rep(i, m) {
    ll n1, n2, w;
    cin >> n1 >> n2 >> w;
    --n1; --n2; // 0-indexed
    graph[n1].emplace_back(w, n1, n2);
    graph[n2].emplace_back(w, n2, n1);
  }

  // Calculate the shortest path from nearest centrals.
  dijkstra();

  // We update the weight of edge by using dist.
  // new weight = old weight + dist[n1] + dist[n2]
  // They are calculated as the path between centrals.
  rep(i, n) {
    for (auto e : graph[i]) {
      if (closest[i] != closest[e.end]) {
        paths.emplace_back(e.weight + dist[i] + dist[e.end], closest[i], closest[e.end]);
      }
    }
  }
  // cout << "paths:";
  // for (auto e : paths) {
  //   cout << "("<<e.start<<", "<<e.end<<", "<<e.weight<<")" << ' ';
  // }
  // cout << endl;

  // Now, the weights of paths are calculated.
  // We want to find the shortest path in terms of maximum weight in each path.

  // We make minimum spanning tree by Kruskal
  sort(all(paths));
  UnionFind uf(n);
  for (Edge& e : paths) {
    if (uf.root(e.start) != uf.root(e.end)) {
      uf.unite(e.start, e.end);
      specTree[e.start].emplace_back(e.weight, e.start, e.end);
      specTree[e.end].emplace_back(e.weight, e.end, e.start);
    }
  }
  // cout << "specTree: ";
  // for (long long i = 0; i < specTree.size(); ++i) {
  //   cout << i << ": ";
  //   for (auto e : specTree[i]) {
  //     cout << "("<<e.start<<", "<<e.end<<", "<<e.weight<<")" << ' ';
  //   }
  //   cout << endl;
  // }

  // Calculate LCA.
  // Make 0 to the root of tree.
  // root(0);
  dfs(0, -1);

  rep(i, q) {
    ll u, v;
    cin >> u >> v;
    --u; --v;

    ll w = lca(u, v);
    cout << max(liftw(u, depth[u] - depth[w]), liftw(v, depth[v] - depth[w])) << ' ';
  }
  cout << endl;
}
