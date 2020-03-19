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

// rollinghash with mod(2**64)
struct rollinghash {
  // mod is 2**64 (max of ull + 1)
  static const ull base1 = 1000000007;
  vector<ull> _hash, _power;

  rollinghash(const string& s) { init(s); }
  void init(const string& s) {
    int n = s.size();
    _hash.resize(n+1);
    _power.assign(n+1, 1);
    rep(i, n) {
      _hash[i+1] = _hash[i] * base1 + s[i];
      _power[i+1] = _power[i] * base1;
    }
  }

  // get hash of s[left:right]
  inline ull get(int l, int r) const {
    ull res1 = _hash[r] - _hash[l] * _power[r-l];
    return res1;
  }

  // get lcp of s[a:] and t[b:]
  inline int getlcp(int a, int b) const {
    int len = min((int)_hash.size()-a, (int)_hash.size()-b);
    int low = 0, high = len;
    while (high - low > 1) {
      int mid = (low + high) >> 1;
      if (get(a, a+mid) != get(b, b+mid)) high = mid;
      else low = mid;
    }
    return low;
  }
};

// int main(int argc, char** argv) {
//   string S("abcabc");
//
//   RollingHash rh(S);
//
//   cout << (rh.get(0, 2) == rh.get(3, 5)) << endl; // abc == abc: true
//   cout << (rh.get(0, 2) == rh.get(3, 4)) << endl; // abc == ab: false
//
//   cout << rh.getLCP(0, 3) << endl; // abc, abc: 3
//   cout << rh.getLCP(1, 4) << endl; // bc, bc: 2
//   cout << rh.getLCP(0, 4) << endl; // abc, bc: 0
// }


// return the max length from each position.
// vector<P> calcAllParin(string& s) {
pair<vector<ll>, vector<ll>> calcAllParin(string& s) {
  string revS = s;
  reverse(all(s));
  string t = s;
  t += "$";
  t += revS;
  RollingHash rh(t); // rolling hash of t

  ll n = s.size();

  vector<ll> leftLenMap(n); // max length at pos[i].
  vector<ll> rightLenMap(n); // max length at pos[i].
  rep(i, n) {
    ll l = i;
    ll r = i;

    if ((n-1-r) > l) { // r is far than l. l is near. l is valid
      leftLenMap[l] = 1;
    } else if ((n-1-r) == l) { // distance is same
      leftLenMap[l] = 1;
      rightLenMap[r] = 1;
    } else { // l is far. r is near. r is valid.
      rightLenMap[r] = 1;
    }
  }
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
        if ((n-1-r) > l) { // r is far than l
          leftLenMap[l] = max(leftLenMap[l], len*2+1); // update lenMap
        } else if ((n-1-r) == l) { // distance is same
          rightLenMap[r] = max(rightLenMap[r], len*2+1); // update lenMap
          leftLenMap[l] = max(leftLenMap[l], len*2+1); // update lenMap
        } else { // l is far
          rightLenMap[r] = max(rightLenMap[r], len*2+1); // update lenMap
        }

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
        if ((n-1-r) > l) { // r is far than l
          leftLenMap[l] = max(leftLenMap[l], len*2); // update lenMap
        } else if ((n-1-r) == l) { // distance is same
          rightLenMap[r] = max(rightLenMap[r], len*2); // update lenMap
          leftLenMap[l] = max(leftLenMap[l], len*2); // update lenMap
        } else { // l is far
          rightLenMap[r] = max(rightLenMap[r], len*2); // update lenMap
        }

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
  // cout << "leftLenMap: "; printvec(leftLenMap);
  // cout << "rightLenMap: "; printvec(rightLenMap);

  // Here, we want to calculate the max length of same "pre" and "suf" of s.
  ll maxLen = calcMaxPreAndSuffs(s);
  // cout << "maxLen: " << maxLen << endl;

  string revS = s; // reverse of s
  reverse(all(revS));

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
      nowAns += revS.substr(len, parinLen);
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
