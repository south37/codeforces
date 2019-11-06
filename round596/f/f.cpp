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
    cout << i + 1 << ": ";
    printvec(tree[i]);
  }
}
template<class T, class U> void printmap(const map<T, U>& mp) {
  for (auto x : mp) { cout << x.first << "=>" << x.second << endl; }
}

template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define rep(i, n) for(ll i = 0; i < n; ++i)
#define all(s) s.begin(), s.end()

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7

vector<ll> p; // p[i] .. parent of i
vector<ll> h; // h[i] .. height of i
vector<ll> b; // the first bamboo state
vector<ll> ans; // the result operation
vector< vector<ll> > c; // c[i] .. children of i
ll it = 0;

int dfs(int v) {
  h[v] = 1;
  rep(i, c[v].size()) {
    h[v] = max(h[v], dfs(c[v][i])+1);
  }
  return h[v];
}

void dfs1(int v) {
  b[it++] = v;
  int ln = 0;
  rep(i, c[v].size()) {
    rep(j, ln) {
      ans.push_back(c[v][i]);
    }
    dfs1(c[v][i]);
    ln = h[c[v][i]];
  }
}

int main(int argc, char** argv) {
  ll n;
  cin >> n;
  p.resize(n);
  c.resize(n);
  p[0] = -1;
  for (int i = 1; i < n; ++i) {
    cin >> p[i];
    c[p[i]].push_back(i);
  }
  dfs(0);
  rep(i, n) {
    sort(all(c[i]), [&](int a, int b) { return h[a] < h[b] });
  }
  b.resize(n);
  dfs1(0);
  rep(i, n) {
    cout << b[i] << ' ';
  }
  cout << endl;
  cout << ans.size() << endl;
  rep(i, ans.size()) {
    cout << ans[i] << ' ';
  }
  cout << endl;
}
