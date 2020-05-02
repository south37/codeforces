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

  sort(all(remain));
  // Here, remain is sorted by q.

  while (remain.size() > 0) {
    {
      ll remain = 0;
      rep(i,10) {
        if (mp[i] == '$') {
          ++remain;
        }
      }
      if (remain == 0) { break; } // already ok.

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

    vector<pair<ll,string>> nex;

    // For Debug
    // cout << "mp: " << mp << endl;
    // cout << "remain.size: " << remain.size() << endl;

    for (auto& p : remain) {
      ll q = p.first;
      string r = p.second;
      for (char c : r) { usedC.insert(c); }
      string& M = r;
      ll m = r.size();
      // r is string representation of v. 1 <= v <= q.
      // cout << "q: " << q << endl;
      // cout << "r: " << r << endl;

      if (q <= 9) {
        assert(r.size() == 1);
        if (revMp.find(r[0]) != revMp.end()) { continue; } // already found

        // Here, we check remaining
        ll cnt = 0; // not found count
        for (ll i = 1; i <= q; ++i) {
          if (mp[i] == '$') { ++cnt; }
        }
        if (cnt == 0) { // all values are found.
          continue;
        }
        if (cnt == 1) {
          // Here, r[0] is exactly same.
          char c = r[0];
          for (ll i = 1; i <= q; ++i) {
            if (mp[i] == '$') {
              mp[i] = c;
              revMp[c] = i;
            }
          }
          continue;
        }

        // Else, we don't have much information
        nex.push_back({ q, r });
        continue;
      }

      vector<ll> ds; // vector representation of m.
      while (q > 0) {
        ds.push_back(q%10);
        q /= 10;
      }
      reverse(all(ds));

      // Here, q >= 10.
      // // Consider only 2 digits.
      ll id = -1;
      ll cnt = 0;
      rep(k,m) {
        ll d = q; // digit at k.
        rep(iter,k) { d /= 10; }
        d %= 10;
        if (mp[d] == '$') { ++cnt; id = k; }
      }
      if (cnt == 0) { continue; } // already determined.
      if (cnt > 1) { // too unknown
        nex.push_back({ q, r });
        continue;
      }
      // Here, cnt == 1. we consider this case.

      // Here, id is position from right at r.
      bool same = false;  // r and ds is ame at [0,prev)
      if (m == ds.size()) {
        same = true;
        rep(i, m-id) {
          if (ds[i] != M[i]) { same = false; }
        }
      }

      ll d = q; // digit at k.
      rep(iter,k) { d /= 10; }
      d %= 10;
      assert(mp[d] == '$');
      char c = r[m-1-k];
      if (revMp.find(c) != revMp.end()) { continue; } // already found

      if (!same) { // must consider 0to9.
        ll q = 9;
        ll k = id;

        ll id = -1;

        // TODO
        ll id = -1; // not found id.
        ll cnt = 0; // not found count
        for (ll i = 1; i <= q; ++i) {
          if (mp[i] == '$') { ++cnt; id = i; }
        }
        if (cnt == 0) { // all values are found
          continue;
        }
        if (cnt == 1) { // Here, only one value is undertermined
          mp[id] = c;
          revMp[c] = id;
          continue;
        }
        // Here, cnt > 1. we can not determine.
      } else { // Here, consider only small values.
        ll k = id;

        ll d = q; // digit at k.
        rep(iter,k) { d /= 10; }
        d %= 10;
        assert(mp[d] == '$');

        // Consider d.
        char c = r[m-1-k];
        if (revMp.find(c) != revMp.end()) { continue; } // already found

        ll id = -1; // not found id.
        ll cnt = 0; // not found count
        for (ll i = 1; i <= q; ++i) {
          if (mp[i] == '$') { ++cnt; id = i; }
        }
        if (cnt == 0) { // all values are found
          continue;
        }
        if (cnt == 1) { // Here, only one value is undertermined
          mp[id] = c;
          revMp[c] = id;
          continue;
        }
        // Here, cnt > 1. we can not determine.
      }

      nex.push_back({ q, r });
    }
    swap(remain, nex);
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
