// ref. https://codingcompetitions.withgoogle.com/codejam/submissions/000000000019fef2/U251a2U

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <string.h>
#include <set>
#include <unordered_map>
#include <vector>

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

void solve() {
  ll r, s;
  cin >> r >> s;
  vector<ll> a;
  rep(i, s) rep(j, r) {
    a.push_back(j+1);
  }
  vector<pair<ll, ll>> ans;
  auto add = [&](ll x, ll y) {
    ans.emplace_back(x, y);
    vector<ll> tmp(x);
    // Here, simulate the swap
    rep(i,x) tmp[i] = a[i];
    rep(i,y) a[i] = a[i+x];
    rep(i,x) a[i+y] = tmp[i];
  };
  while (true) {
    ll i = 0;
    ll fa = a[0]; // first element of a
    while (a[i] == fa) { ++i; }
    ll si = i; // a[si-1] == fa
    while (i < a.size() && a[i] != fa) { ++i; }
    if (i == a.size()) { break; } // reached to last
    if (i == a.size()-1) { // last element is same with fa.
      add(si, a.size()-si);
      break;
    }
    ll ba = a[i+1];
    int j = i-1; // a[j] != fa
    while (a[j] != ba) { --j; }
    // Here, a[j] == ba
    ++j;
    add(j, i+1-j); //
  }
  cout << ans.size() << endl;
  for (auto& p : ans) {
    cout << p.fr << " " << p.sc << endl;
  }
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll t;
  cin >> t;
  rep(i, t) {
    cout << "Case #" << (i+1) << ": ";
    solve();
  }
}
