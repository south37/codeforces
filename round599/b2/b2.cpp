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

  // Check the distribtion
  vector<ll> cnt(26);
  rep(i, n) {
    ++cnt[s[i]-'a'];
    ++cnt[t[i]-'a'];
  }
  rep(i, 26) {
    if (cnt[i] % 2 != 0) {
      cout << "No" << endl;
      return;
    }
  }
  // Now, distribtion is OK.

  vector<P> ans;
  rep(i, n) {
    if (s[i] == t[i]) {
      // Do nothing
      continue;
    } else {
      bool flag = false; // swap by s[i] == s[j]
      for (int j = i + 1; j < n; ++j) {
        if (s[j] == s[i]) {
          ans.emplace_back(j, i);
          swap(s[j], t[i]);
          flag = true;
          break;
        }
      }

      if (!flag) { // Must swap by s[i] == t[j]
        for (int j = i + 1; j < n; ++j) {
          if (t[j] == s[i]) {
            ans.emplace_back(j, j);
            ans.emplace_back(j, i);
            swap(s[j], t[j]);
            swap(s[j], t[i]);
            break;
          }
        }
      }
    }
  }

  cout << "Yes" << endl;
  cout << ans.size() << endl;
  for (auto p : ans) {
    cout << p.fr+1 << " " << p.sc+1 << endl;
  }
}

int main(int argc, char** argv) {
  ll t;
  cin >> t;
  rep(i, t) {
    solve();
  }
}
