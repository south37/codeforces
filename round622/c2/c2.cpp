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
#include <stack>

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

int main(int argc, char** argv) {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(false);
  //cout << setprecision(10) << fixed;

  ll n;
  cin >> n;
  vector<ll> m(n);
  rep(i, n) {
    cin >> m[i];
  }
  // Search the largest i.
  ll ans = 0;

  vector<ll> leftCont(n);
  {
    stack<pair<ll, ll>> st; // the stack of { value, cnt }
    ll prevSum = 0;
    rep(i, n) {
      ll cnt = 0;
      while (!st.empty() && st.top().first >= m[i]) {
        pair<ll, ll> p = st.top();
        st.pop();
        cnt += p.second;
        prevSum -= p.first * p.second; // minus the popped sum
      }
      /// Here, st.empty() or st.top().first < m[i]
      st.push({ m[i], cnt + 1 });
      leftCont[i] = prevSum + m[i] * (cnt + 1);
      prevSum = leftCont[i];
    }

    // Debug
    // cout << "stack:" << endl;
    // cout << st.size() << endl;
    // cout << st.top().first << "," << st.top().second << endl;
  }
  // Here, we calculated the sum from left in each i. the sum is in [0, i].

  // Do same thing for right
  vector<ll> rightCont(n);
  {
    stack<pair<ll, ll>> st; // the stack of { value, cnt }
    ll prevSum = 0;
    for (int i = n-1; i >= 0; --i) {
      ll cnt = 0;
      while (!st.empty() && st.top().first >= m[i]) {
        pair<ll, ll> p = st.top();
        st.pop();
        cnt += p.second;
        prevSum -= p.first * p.second; // minus the popped sum
      }
      /// Here, st.empty() or st.top().first < m[i]
      st.push({ m[i], cnt + 1 });
      rightCont[i] = prevSum + m[i] * (cnt + 1);
      prevSum = rightCont[i];
    }

    // Debug
    // cout << "stack2:" << endl;
    // cout << st.size() << endl;
    // cout << st.top().first << "," << st.top().second << endl;
  }

  ll maxI = -1;
  ll maxHeight = -1;
  rep(i, n) {
    // Here, we check the sum when we use i as top.
    ll cand = leftCont[i] + rightCont[i] - m[i];
    if (cand > maxHeight) {
      maxHeight = cand;
      maxI = i;
    }
  }
  // cout << "maxI: " << maxI << endl;
  // cout << "maxHeight: " << maxHeight << endl;

  // Here, maxI is the i with maximum height.

  vector<ll> ansVec(n);
  {
    ll highest = m[maxI];
    for (int j = maxI; j < n; ++j) {
      ll height = min(highest, m[j]);
      ansVec[j] = height;
      highest = min(highest, height);
    }
    highest = m[maxI];
    for (int j = maxI-1; j >= 0; --j) {
      ll height = min(highest, m[j]);
      ansVec[j] = height;
      highest = min(highest, height);
    }
  }

  rep(i, n) {
    cout << ansVec[i];
    if (i != n-1) { cout << " "; }
  }
  cout << endl;
}
