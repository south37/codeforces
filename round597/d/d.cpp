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

#define rep(i, n) for(int i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

class UnionFind {
public:
  UnionFind(ll n) : par(n, -1), rnk(n, 0), cnt(n, 1), _size(n) {}

  bool same(ll x, ll y) {
    return root(x) == root(y);
  }
  void unite(ll x, ll y) {
    x = root(x); y = root(y);
    if (x == y) return;

    --_size;

    if (rnk[x] < rnk[y]) { swap(x, y); }
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


int main(int argc, char** argv) {
  ll n;
  cin >> n;
  vector<ll> xs(n);
  vector<ll> ys(n);
  rep(i, n) {
    ll x, y;
    cin >> xs[i] >> ys[i];
  }
  vector<ll> c(n); // the power station.
  rep(i, n) {
    cin >> c[i];
  }
  vector<ll> k(n); // the cost of wire.
  rep(i, n) {
    cin >> k[i];
  }

  priority_queue<triple, vector<triple>, greater<triple>> edges; // increasing order

  rep(i, n) {
    for (int j = i + 1; j < n; ++j) {
      ll cost = (k[i] + k[j]) * (abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]));
      edges.emplace(cost, i+1, j+1);
    }
  }
  // We add (c[i], 0, i+1) as the edges.
  rep(i, n) {
    edges.emplace(c[i], 0, i+1);
  }

  ll ans = 0; // The sum of cost
  set<ll> powers; // The indices of powers
  vector<P> wires; // The pairs of wires

  // We use Kruskal's algorithm to find the minimum spanning tree.
  UnionFind tree(n + 1);
  while (!edges.empty()) {
    auto e = edges.top(); edges.pop();
    ll cost, i, j;
    tie(cost, i, j) = e;
    if (!tree.same(i, j)) {
      tree.unite(i, j);

      ans += cost;
      if (i == 0) { // power
        powers.insert(j);
      } else {
        wires.emplace_back(i, j);
      }
    }
  }

  cout << ans << endl;
  cout << powers.size() << endl;
  for (auto p : powers) {
    cout << p << " ";
  }
  cout << endl;
  cout << wires.size() << endl;
  for (auto x : wires) {
    cout << x.first << " " << x.second << endl;
  }
}
