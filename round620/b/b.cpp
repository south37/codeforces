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

bool isPalindrom(const string& s) {
  string reversed = s; // copy
  reverse(all(reversed));
  return reversed == s;
}

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n, m;
  cin >> n >> m;
  map<string, int> cnts;
  vector<string> inputs(n);
  map<string, int> ansCnts; // tha counts of pairs.
  // In each step, we check the existence of reversed string.
  rep(i, n) {
    cin >> inputs[i];
    if (cnts.find(inputs[i]) != cnts.end()) { // found
      ++ansCnts[inputs[i]];
      --cnts[inputs[i]];
    } else {
      string reversed = inputs[i]; // copy
      reverse(all(reversed));
      ++cnts[reversed];
    }
  }
  // Here, we have all pairs in ansCnts and remaining in cnts.

  string ansPrefix;
  for (auto& p : ansCnts) {
    int cnt = p.second;
    rep(iter, cnt) {
      ansPrefix += p.first;
    }
  }
  // Here, ansPrefix is the prefix. suffix is the reversed one.

  string ans = ansPrefix;
  for (auto& p : cnts) {
    if (p.second > 0) {
      if (isPalindrom(p.first)) {
        ans += p.first;
        break; // we use only one palindrom
      }
    }
  }

  reverse(all(ansPrefix));
  ans += ansPrefix;
  cout << ans.size() << endl;
  cout << ans << endl;
}
