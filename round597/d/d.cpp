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

  set<ll> powers;

  ll s = 0; // The sum of building power station.
  rep(i, n) {
    s += c[i];
    powers.insert(i);
  }

  priority_queue<triple, vector<triple>, greater<triple> > q; // increasing order

  rep(i, n) {
    rep(j, n) {
      if (i == j) { continue; }
      ll dist = abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]);
      ll cost = dist * (k[i] + k[j]);
      q.emplace(cost, i, j);
    }
  }

  vector<P> wires;

  // We check from paths with minimum cost.
  while (!q.empty()) {
    ll cost, i, j;
    tie(cost, i, j) = q.top(); q.pop();

    ll c_cost = -1;
    ll c_id = -1;
    if (powers.count(i) > 0) { // i uses power
      if (c_cost < c[i]) {
        c_cost = c[i];
        c_id = i;
      }
    }
    if (powers.count(j) > 0) { // j uses power
      if (c_cost < c[j]) {
        c_cost = c[j];
        c_id = j;
      }
    }

    if (c_cost == -1) { continue; } // i and j do not use power now.

    if (c_cost > cost) {
      // Now, we use wire instead of c[c_id]
      s -= c_cost;
      s += cost;
      wires.emplace_back(i, j);
      powers.erase(c_id);
    }
  }

  cout << s << endl;
  cout << powers.size() << endl;
  for (auto x : powers) {
    cout << x + 1 << " ";
  }
  cout << endl;

  cout << wires.size() << endl;
  for (auto x : wires) {
    cout << x.first + 1 << " " << x.second + 1 << endl;
  }
}
