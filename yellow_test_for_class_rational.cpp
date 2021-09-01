#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class First, class Second>
ostream& operator << (ostream& os, const pair<First, Second>& p) {
    return os << "{" << p.first << ", " << p.second << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

/*class Rational {
public:
    Rational() {
        N = 0;
        D = 1;
    }
    Rational(int numerator, int denominator) {
        if (denominator < 0) {
            denominator *= -1;
            numerator   *= -1;
        }
        N = numerator;
        D = denominator;
    }

    int Numerator() const {
        return N;
    }

    int Denominator() const {
        return D;
    }
private:
    int N;
    int D;
};*/

void TestForDefCons() {
    Rational rat;
    pair<int, int> tested_val = make_pair(rat.Numerator(), rat.Denominator());
    pair<int, int> correct_val = make_pair(0, 1);
    AssertEqual(tested_val, correct_val, "Test for default constructor");
}

void TestWithDiffSigns() {
    Rational rat0(1, 2);
    pair<int, int> tested_val = make_pair(rat0.Numerator(), rat0.Denominator());
    pair<int, int> correct_val = make_pair(1, 2);
    AssertEqual(tested_val, correct_val, "Both are positive");

    Rational rat1(1, -2);
    tested_val = make_pair(rat1.Numerator(), rat1.Denominator());
    correct_val = make_pair(-1, 2);
    AssertEqual(tested_val, correct_val, "Numerator's positive, denominator's negative");

    Rational rat2(-1, -2);
    tested_val = make_pair(rat2.Numerator(), rat2.Denominator());
    correct_val = make_pair(1, 2);
    AssertEqual(tested_val, correct_val, "Both are negative");

    Rational rat3(-1, 2);
    tested_val = make_pair(rat3.Numerator(), rat3.Denominator());
    correct_val = make_pair(-1, 2);
    AssertEqual(tested_val, correct_val, "Numerator's negative, denominator's positive");

    Rational rat4(0, 2);
    tested_val = make_pair(rat4.Numerator(), rat4.Denominator());
    correct_val = make_pair(0, 1);
    AssertEqual(tested_val, correct_val, "Numerator's null, denominator's positive");

    Rational rat5(0, -10);
    tested_val = make_pair(rat5.Numerator(), rat5.Denominator());
    correct_val = make_pair(0, 1);
    AssertEqual(tested_val, correct_val, "Numerator's null, denominator's negative");
}

void TestRound() {
    Rational rat0(2, 4);
    pair<int, int> tested_val = make_pair(rat0.Numerator(), rat0.Denominator());
    pair<int, int> correct_val = make_pair(1, 2);
    AssertEqual(tested_val, correct_val, "Round test. Both are positive");

    Rational rat1(3, -6);
    tested_val = make_pair(rat1.Numerator(), rat1.Denominator());
    correct_val = make_pair(-1, 2);
    AssertEqual(tested_val, correct_val, "Round test. Numerator's positive, denominator's negative");

    Rational rat2(-4, -8);
    tested_val = make_pair(rat2.Numerator(), rat2.Denominator());
    correct_val = make_pair(1, 2);
    AssertEqual(tested_val, correct_val, "Both are negative");

    Rational rat3(-100, 200);
    tested_val = make_pair(rat3.Numerator(), rat3.Denominator());
    correct_val = make_pair(-1, 2);
    AssertEqual(tested_val, correct_val, "Numerator's negative, denominator's positive");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestForDefCons, "TestForDefCons");
    runner.RunTest(TestWithDiffSigns, "TestWithDiffSigns");
    runner.RunTest(TestRound, "TestRound");
    return 0;
}