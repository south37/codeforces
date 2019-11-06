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

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;
typedef tuple<ll, ll, ll> triple;
typedef double D;

const ll INF = 1e9;
const ll MOD = 1000000007;  // 1e9 + 7



void solve() {
  ll n;
  cin >> n;
  string s, t;
  cin >> s;
  cin >> t;
  vector<ll> s_dist(26);
  vector<ll> t_dist(26);
  vector<ll> diff_dist(26);

  vector<ll> s_indices; // The different indicces of s
  vector<ll> t_indices; // The different indicces of s
  vector< vector<ll> > s_d(26);
  vector< vector<ll> > t_d(26);

  ll cnt = 0; // the count of different position
  rep(i, n) {
    if (s[i] == t[i]) {
      // skip
      // we consider only different positions.
    } else {
      ++cnt;
      s_indices.push_back(i);
      t_indices.push_back(i);
      ++s_dist[s[i] - 'a'];
      ++t_dist[t[i] - 'a'];
      s_d[s[i] - 'a'].push_back(i);
      t_d[t[i] - 'a'].push_back(i);
    }
  }
  if (cnt == 0) { // completely same
    cout << "Yes" << endl;
    cout << 0 << endl;
    cout << endl;
    return;
  }
  // Now, cnt positions are different.

  rep(i, 26) {
    diff_dist[i] = s_dist[i] - t_dist[i];
  }
  // cout << "s_dist: "; printvec(s_dist);
  // cout << "t_dist: "; printvec(t_dist);

  ll diff = 0; // the half of different counts.
  rep(i, 26) {
    if (diff_dist[i] % 2 != 0) { // each diff must be even
      cout << "No" << endl;
      return;
    }
    diff += abs(diff_dist[i]) / 2;
  }
  diff /= 2;

  // Now, we treat half diff as the proceeding.
  // "cnt" is the operation we must be done, and "cnt-diff" is the plus alpha.
  if (cnt - diff <= 2 * n) {
    cout << "Yes" << endl;
    cout << cnt + diff << endl;
    // At first, we use diff to make same distribution.
    rep(i, 26) {
      for (int j = i + 1; i < 26; ++j) {
        while ((diff_dist[i] > 0) && (diff_dist[j] < 0)) { // e.g. s['a'] > t['a'] && s['b'] < t['b']
          // swap s[i] and t[j]
          s_d[i]
        }
      }
    }

    // cout << cnt-diff << endl;
    // cout << "cnt: " << cnt << endl;
    // cout << "diff: " << diff << endl;
    cout << "TODO Impl" << endl;
    //
  } else {
    cout << "No" << endl;
    return;
  }
}

int main(int argc, char** argv) {
  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
