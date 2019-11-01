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

  ll s = 0; // The sum of building power station.
  rep(i, n) {
    s += c[i];
  }

  // nearest[i] .. the sorted map of points from i.
  vector< map<P, ll> > nearests(n);
  rep(i, n) {
    rep(j, n) {
      if (j == i) { continue; }
      ll dist = abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]);
      P p(dist, j);
      nearests[i][p] = j;
    }
  }
  // Here, nearest[i] is sorted map. { dist => i }. increasing

  // For Debug
  // rep(i, n) {
  //   cout << "i: " << i << endl;
  //   for (auto x : nearests[i]) {
  //     cout << "j: " << x.second << ", dist: " << x.first.first << endl;
  //   }
  // }

  vector<P> wires;
  vector<ll> power_indices;

  // Check if wire or power station
  rep(i, n) {
    auto it = nearests[i].begin();
    ll j = (*it).second; // nearest index.
    ll dist = (*it).first.first;
    ll wire_cost = dist * (k[i] * k[j]);
    if (c[i] > wire_cost) {
      // Use wire
      wires.emplace_back(i, j);
      s -= c[i];
      s += wire_cost;
    } else {
      power_indices.push_back(i);
    }
  }

  cout << s << endl;
  cout << power_indices.size() << endl;
  for (auto x : power_indices) {
    cout << x + 1<< " ";
  }
  cout << endl;

  cout << wires.size() << endl;
  for (auto x : wires) {
    cout << x.first + 1 << " " << x.second + 1 << endl;
  }
}
