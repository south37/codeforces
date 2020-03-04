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

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vector<vector<ll>> g; // tree
vector<ll> degree; // degree of each node

ll ask(ll u, ll v) {
  cout << "? " << u + 1 << " " << v + 1 << endl;
  cout.flush();
  ll w;
  cin >> w;
  assert(w != -1);
  return w - 1; // 0-indexed
}

void answer(ll r) {
  cout << "! " << r + 1 << endl;
  cout.flush();
  exit(0);
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  g.resize(n);
  degree.resize(n);

  rep(i, n-1) {
    ll x, y;
    cin >> x >> y;
    --x; --y; // 0-indexed
    g[x].push_back(y);
    g[y].push_back(x);
    ++degree[x];
    ++degree[y];
  }

  vector<ll> leaves;
  set<ll> purged; // purged nodes

  rep(i, n) {
    if (degree[i] == 1) {
      leaves.push_back(i);
    }
  }
  while (leaves.size() > 1) {
    ll u = leaves.back(); leaves.pop_back();
    ll v = leaves.back(); leaves.pop_back();
    ll w = ask(u, v);
    if (w == u || w == v) {
      answer(w);
    }

    // purge u and v
    purged.insert(u);
    purged.insert(v);

    for (int nu : g[u]) {
      if (purged.find(nu) != purged.end()) { continue; } // skip purged nodes
      --degree[nu];
      if (degree[nu] == 1) { leaves.push_back(nu); }
    }
    for (int nv : g[v]) {
      if (purged.find(nv) != purged.end()) { continue; } // skip purged nodes
      --degree[nv];
      if (degree[nv] == 1) { leaves.push_back(nv); }
    }
  }

  // Here, we must find answer

  return 0;
}
