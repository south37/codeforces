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

vector<int> build_z(const string& s) {
  int n = s.size();
  vector<int> z(n, 0);
  int l = -1, r = -1;
  for (int i = 1; i < n; ++i) {
    if (i <= r) {
      z[i] = min<int>(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

// void search(const string& text, const string& pattern, vector<int>& result) {
//   vector<int> z = build_z(pattern + "$" + text);
//
//   int p = pattern.length();
//   for (int i = p + 1; i < z.size(); ++i) {
//     if (z[i] == p) {
//       result.push_back(i-p-1);
//     }
//   }
// }
//
// int main(int argc, char** argv) {
//   string s, t;
//   cin >> s;
//   cin >> t;
//
//   vector<int> matches;
//   search(s, t, matches);
//
//   for (auto e : matches) {
//     cout << e << endl;
//   }
//
//   cout << s << endl;
//   cout << t << endl;
// }

string calcPalin(string& s) {
  ll n = s.size();

  string t = s;
  t += "$";
  string revS = s;
  reverse(all(revS));
  t += revS;

  vector<int> z = build_z(t);
  ll len = 0;
  // Here, find the longest len where i+len == 2*n+1
  for (int i = n+1; i <= 2*n; ++i) {
    if (i+z[i] == 2*n+1) { // palindrom found
      len = max<ll>(len, z[i]);
    }
  }

  return s.substr(0, len);
}

// return the all possible length of "pre" and "suff"
ll calcMaxPreAndSuffs(string& s) {
  ll n = s.size();
  ll len = 0;
  ll left = 0, right = n-1;
  while (left < right && s[left] == s[right]) {
    ++left;
    --right;
    ++len;
  }
  return len;
}

void solve() {
  string s;
  cin >> s;
  ll n = s.size();

  ll preLen = calcMaxPreAndSuffs(s);
  string pre = s.substr(0, preLen);
  cout << pre; // print pre
  string t = s.substr(preLen, n - 2*preLen); // substring
  {
    string a = calcPalin(t); // palindrom from prefix
    reverse(all(t));
    string b = calcPalin(t); // palindrom from suffix
    if (a.size() < b.size()) { swap(a, b); }
    // Here, a.size() >= b.size()
    cout << a;
  }
  reverse(all(pre));
  cout << pre; // print suf
  cout << endl;
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
