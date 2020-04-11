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
  ll n;
  cin >> n;
  vector<string> pattern(n);
  rep(i, n) {
    cin >> pattern[i];
  }
  // Here, we solve only for test set 2.
  // We need to check only prefix and suffics
  vector<string> pres;
  vector<string> sufs;
  vector<string> middles;
  rep(i, n) {
    string& p = pattern[i];

    vector<string> splitted;
    ll pos = 0;
    while (true) {
      auto found = p.find('*', pos);
      if (found == string::npos) { // reached to last
        splitted.push_back(p.substr(pos));
        break;
      } else {
        splitted.push_back(p.substr(pos, found-pos));
        pos = found + 1; // skip '*'
      }
    }
    // cout << "splitted size: " << splitted.size() << endl;
    // cout << "splitted: "; printvec(splitted);

    // Here, j is *
    pres.push_back(splitted[0]);
    sufs.push_back(splitted[splitted.size()-1]);
    for (int i = 1; i < splitted.size()-1; ++i) {
      middles.push_back(splitted[i]);
    }
  }
  // cout << "pres: "; printvec(pres);
  // cout << "sufs: "; printvec(sufs);

  // Here, we treat sufs in reversed format
  for (auto& suf : sufs) {
    reverse(all(suf));
  }

  vector<string> PreAndSufAns(2);
  vector<vector<string>> PreAndSuf;
  PreAndSuf.push_back(pres);
  PreAndSuf.push_back(sufs);

  rep(k, 2) {
    string& ans = PreAndSufAns[k];
    vector<string>& pattern = PreAndSuf[k];
    // cout << "pattern:"; printvec(pattern);
    // cout << "pattern size:" << pattern.size() << endl;
    rep(i, n) {
      if (ans.size() < pattern[i].size()) {
        ans = pattern[i];
      }
    }
    // cout << "ans: " << ans << endl;

    // Here, ans is the longest pattern.
    // Check the sameness of them
    ll m = ans.size();
    rep(i, m) {
      rep(j, n) {
        auto& p = pattern[j];
        // cout << "p: " << p << endl;
        // cout << "p.size: " << p.size() << endl;

        if (i >= p.size()) { continue; } // p is short. skip
        if (ans[i] != p[i]) { // not match. invalid case.
          cout << "*"; // print '*'
          return;
        }
      }
    }
  }

  // Here, ans has valid string
  string ans = PreAndSufAns[0];
  for (auto& middle : middles) {
    ans += middle;
  }
  reverse(all(PreAndSufAns[1]));
  ans += PreAndSufAns[1];

  cout << ans;
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
    cout << endl;
  }
}
