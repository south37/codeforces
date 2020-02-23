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
  map<char, int> hist;
  for (char c : s) {
    ++hist[c];
  }
  bool oddFound = false;
  for (auto& p : hist) {
    if (p.second % 2 == 1) {
      if (oddFound) { return false; } // odd can be seen only once
      oddFound = true;
    }
  }
  return true;
}

string toPalindrom(const string& s) {
  int n = s.size();
  // If n is odd, only 1 character is odd. other is even.
  map<char, int> hist;
  for (char c : s) {
    ++hist[c];
  }
  char odd;
  string ans;
  for (auto& p : hist) {
    if (p.second % 2 == 1) {
      odd = p.first;
      if (p.second > 1) {
        ans += string(p.second/2, p.first);
      }
    } else {
      ans += string(p.second/2, p.first);
    }
  }
  string suffix = ans;
  reverse(all(suffix));
  if (n % 2 == 1) {
    ans += odd;
  }
  ans += suffix;
  return ans;
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
  rep(i, n) {
    cin >> inputs[i];
    sort(all(inputs[i]));
    ++cnts[inputs[i]];
  }
  // Here, we use pair in each string.

  map<string, int> ansCnts;
  for (auto& p : cnts) {
    if (p.second >= 2) { // cnt >= 2
      int usedCnt = (p.second / 2); // should be even.
      ansCnts[p.first] = usedCnt;
      cnts[p.first] -= usedCnt * 2;
    }
  }
  // Here, ansCnts has the information about ans.
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
        ans += toPalindrom(p.first);
        break; // we use only one palindrom
      }
    }
  }

  reverse(all(ansPrefix));
  ans += ansPrefix;
  cout << ans.size() << endl;
  cout << ans << endl;
}
