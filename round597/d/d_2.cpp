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

const ll INF = 1e15;
const ll MOD = 1000000007;  // 1e9 + 7

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

  vector<bool> done(n);
  vector<ll> parent(n, -1);

  rep(iter, n) {
    ll mi = INF; // The minimum c[i].
    ll u = -1; // i with minimum c[i].
    rep(i, n) {
      if (done[i]) { continue; }
      if (c[i] < mi) {
        mi = c[i];
        u = i;
      }
    }

    ans += mi;
    done[u] = true;
    if (parent[u] == -1) {
      powers.emplace(u);
    } else {
      wires.emplace_back(min(parent[u], u), max(parent[u], u));
    }

    rep(i, n) {
      ll cost = (k[u] + k[i]) * (abs(xs[u] - xs[i]) + abs(ys[u] - ys[i]));
      if (cost < c[i]) {
        c[i] = cost;
        parent[i] = u;
      }
    }
  }

  cout << ans << endl;
  cout << powers.size() << endl;
  for (auto p : powers) {
    cout << p + 1 << " ";
  }
  cout << endl;
  cout << wires.size() << endl;
  for (auto x : wires) {
    cout << x.first + 1 << " " << x.second + 1 << endl;
  }
}
