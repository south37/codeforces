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

bool allsame(string& t) {
  char c = t[0];
  bool ans = true;
  rep(i, t.size()) {
    if (t[i] != c) {
      ans = false;
    }
  }
  return ans;
}

string zigzag(string& t) {
  ll n = t.size();
  char c = t[0];
  char left, right;
  if (c == '0') {
    left = '0';
    right = '1';
  } else {
    left = '1';
    right = '0';
  }

  ll len = 0;
  ll i = 0;
  while (i < n) {
    if (i < n-1 && t[i] == left && t[i+1] == right) {
      ++len;
      i = i+2;
    } else {
      ++len;
      ++i;
    }
  }
  // Here, i == n.
  string ans;
  rep(iter, len) {
    ans += left;
    ans += right;
  }
  return ans;
}

void solve() {
  string t;
  cin >> t;
  if (allsame(t)) {
    cout << t << endl;
  } else {
    // print zig-zag
    string s = zigzag(t);
    cout << s << endl;
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
    solve();
  }
}
