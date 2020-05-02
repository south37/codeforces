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

const ll N = 1e4;

void solve() {
  ll u;
  cin >> u;
  string mp(10, '$'); // mapping of num => char
  map<char, ll> revMp;
  vector<pair<ll,string>> remain;
  set<char> usedC;

  rep(i,(ll)1e4) {
    ll q;
    cin >> q;
    string M;
    cin >> M;
    remain.push_back(pair<ll,string>(q, M));
  }
  // cout << remain.size() << endl;

  while (true) {
    {
      ll remain = 0;
      rep(i,10) {
        if (mp[i] == '$') { ++remain; }
      }
      if (remain == 0) { break; }

      if (remain == 1 && usedC.size() == 10) { // Here, remain is left one.
        rep(i,10) {
          if (mp[i] != '$') { usedC.erase(mp[i]); }
        }
        char left = *usedC.begin(); // must exist
        rep(i,10) {
          if (mp[i] == '$') {
            mp[i] = left;
          }
        }
        break;
      }
    }

    cout << "mp: " << mp << endl;

    for (auto& p : remain) {
      ll q = p.first;
      string& M = p.second;
      ll m = M.size();
      rep(i,m) {
        usedC.insert(M[i]);
      }
      // cout << "q: " << q << endl;
      // cout << "M: " << M << endl;

      // 1 <= value <= q.
      // respnse is M.

      if (q <= 9) {
        ll d = q;
        ll c = M[0];
        mp[d] = c;
        revMp[c] = d;
        continue;
      }

      vector<ll> ds(m, -1); // -1 is unknown
      rep(i,m) {
        char c = M[i];
        if (revMp.find(c) != revMp.end()) {
          ll d = revMp[c];
          ds[i] = d;
        }
      }

      if (ds[0] == -1) {
        // Here, ok if ds[1..-1] is known
        bool ok = true;
        for (ll i = 1; i < m; ++i) {
          if (ds[i] == -1) { ok = false; }
        }
        if (ok) { // Here, ds[0] is same with first digit of q.
          cout << "ds:"; printvec(ds);
          char c = M[0];
          ll d = q;
          rep(iter, m-1) { d/=10; }
          // Here, n is first digit.
          mp[d] = c;
          revMp[c] = d;
        }
      }
    }
  }
  cout << mp << endl;
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
  }
}
