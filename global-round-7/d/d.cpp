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

void search(const string& text, const string& pattern, vector<int>& result) {
  vector<int> z = build_z(pattern + "$" + text);

  int p = pattern.length();
  for (int i = p + 1; i < z.size(); ++i) {
    if (z[i] == p) {
      result.push_back(i-p-1);
    }
  }
}

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

// return the max length from each position.
// vector<P> calcAllParin(string& s) {
pair<vector<ll>, vector<ll>> calcAllParin(string& s) {
  ll n = s.size();

  vector<ll> leftLenMap(n); // max length at pos[i].
  vector<ll> rightLenMap(n); // max length at pos[i].
  // vector<P> ans;
  rep(i, n) { // outer loop
    // Here, we calculate all candidates from s[i].
    // try (l,center,r) case
    {
      ll l = i - 1; ll r = i + 1;
      ll len = 1;
      while (l >= 0 && r <= n-1 && s[l] == s[r]) {
        // cout << "s[l], s[r]: " << s[l] << "," << s[r] << endl;
        // cout << "i: " << i << endl;
        // cout << "l: " << l << endl;
        // cout << "r: " << r << endl;
        // cout << "len: " << len << endl;
        leftLenMap[l] = max(leftLenMap[l], len*2+1); // update lenMap
        rightLenMap[r] = max(rightLenMap[r], len*2+1); // update lenMap

        --l;
        ++r;
        ++len;
      }
    }
    // Here, l < 0 or r >= n or s[l] != s[r]
    // ans.emplace_back(i, len);

    // try (l,r) case
    {
      ll l = i; ll r = i+1;
      ll len = 1;
      while (l >= 0 && r <= n-1 && s[l] == s[r]) {
        leftLenMap[l] = max(leftLenMap[l], len*2);
        rightLenMap[r] = max(rightLenMap[r], len*2);

        --l;
        ++r;
        ++len;
      }
    }
  }
  // return ans;
  return { leftLenMap, rightLenMap };
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
  auto p = calcAllParin(s);
  vector<ll>& leftLenMap = p.first;
  vector<ll>& rightLenMap = p.second;
  cout << "leftLenMap: "; printvec(leftLenMap);
  cout << "rightLenMap: "; printvec(rightLenMap);

  // vector<P> parins = calcAllParin(s);
  // set<P> sortedParins; // sorted by left.
  // for (auto& p : parins) {
  //   sortedParins.insert({ p.first - p.second, p.first }); // { left, pos }
  // }
  // vector<ll> lenMap(n); // max length at pos i.
  // for (auto& p : parins) {
  //   ll pos = p.first;
  //   ll len = p.second;
  //   ll left = pos - len;
  //   lenMap[left] = max(lenMap[left],

  // Here, we search the match of prefix ans suffix.
  // string preS = s.substr(0, s.size()/2);
  // string sufS = s.substr(s.size()/2);
  // string t = sufS;
  // reverse(all(t));
  // t += "$";
  // t += preS;
  // cout << "t: " << t << endl;
  // // Here t = rev s + "$" + s
  // vector<int> z = build_z(t);
  // cout << "z: "; printvec(z);
  // z contains the length of match of prefix and suffix.

  // Here, we want to calculate the max length of same "pre" and "suf" of s.
  ll maxLen = calcMaxPreAndSuffs(s);
  // cout << "maxLen: " << maxLen << endl;

  string ans;
  rep(len, maxLen + 1) {
    // Here, z[i] is the match of prefix and suffix
    // We only need to calculate the maximum parindrom in s[k..]
    // ll len = z[i]; // the length of match.
    string pre = s.substr(0, len);

    // Here, we should check "left" and "right"
    // 1. left
    {
      ll parinLen = leftLenMap[len]; // max length of parindrom from s[len]
      string nowAns = pre;
      nowAns += s.substr(len, parinLen);
      string suf = pre;
      reverse(all(suf));
      nowAns += suf;
      if (nowAns.size() > ans.size()) {
        ans = nowAns;
      }
    }

    // 2. right
    {
      ll parinLen = rightLenMap[n-1-len];
      string nowAns = pre;
      nowAns += s.substr(n-1-len-parinLen+1, parinLen); // (n-1-len-parinLen2, n-1-len]
      string suf = pre;
      reverse(all(suf));
      nowAns += suf;
      if (nowAns.size() > ans.size()) {
        ans = nowAns;
      }
    }
  }
  cout << ans << endl;
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
