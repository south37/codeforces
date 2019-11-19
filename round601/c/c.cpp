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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  // vector<triple> ts; // The size if n-2.
  vector<ll> dist(n+1); // The distribution.
  map<P, vector<ll>> m; // The map of (pair) => [Third elements]. triple list is 1 or 2.
  rep(i, n-2) {
    ll q1, q2, q3;
    cin >> q1 >> q2 >> q3;
    // cout << q1 << "," << q2 << "," << q3 << endl;

    // ts.emplace_back(q1, q2, q3);
    ++dist[q1];
    ++dist[q2];
    ++dist[q3];
    m[mp(min(q1, q2), max(q1, q2))].push_back(q3);
    m[mp(min(q2, q3), max(q2, q3))].push_back(q1);
    m[mp(min(q3, q1), max(q3, q1))].push_back(q2);
  }
  // cout << "dist: "; printvec(dist);

  // Now, dist contains the information.
  // We check dist[i] = 1, 2
  vector<ll> ends;
  vector<ll> pre_ends;
  for (int i = 1; i <= n; ++i) {
    if (dist[i] == 1) {
      ends.push_back(i);
    } else if (dist[i] == 2) {
      pre_ends.push_back(i);
    } else { // Do nothing
    }
  }
  // cout << "ends: "; printvec(ends);
  // cout << "pre_ends: "; printvec(pre_ends);

  vector<bool> used(n+1);
  // Now, try the all pairs of ends and pre_ends

  vector<P> ok_pairs;
  rep(i, 2) rep(j, 2) {
    // cout << "(ends[i], pre_ends[j]):" << ends[i]<<", "<<pre_ends[j]<<endl;
    P p = mp(min(ends[i], pre_ends[j]), max(ends[i], pre_ends[j]));
    if (m.count(p)) {
      // cout << "(ends[i], pre_ends[j]):" << ends[i]<<", "<<pre_ends[j]<<endl;
      ok_pairs.push_back(mp(ends[i], pre_ends[j])); // Set in ends, pre_ends order.
    }
  }
  assert(ok_pairs.size() == 2);

  // Use first one.
  vector<ll> ans;

  used[ok_pairs[0].fr] = true;
  used[ok_pairs[0].sc] = true;
  ans.push_back(ok_pairs[0].fr);
  ans.push_back(ok_pairs[0].sc);
  ll ff = ok_pairs[0].fr;
  ll ss = ok_pairs[0].sc;
  rep(iter, n-2) {
    bool found = false;

    P p = mp(min(ff, ss), max(ff, ss));
    for (auto x : m[p]) { // 2 candidates
      if (used[x]) { continue; }

      // Ok, we use x
      used[x] = true;
      ff = ss;
      ss = x;
      ans.push_back(x);
      found = true;
    }

    assert(found);
  }

  // Now, ans.size() == n
  rep(i, ans.size()) {
    cout << ans[i] << (i == (n-1) ? '\n' : ' ');
  }
}
