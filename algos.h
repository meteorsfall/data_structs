long long GCD(long long a, long long b) {
    return a&&b ? GCD(b, a % b) : a + b;
}

long long bigGCD(long long a, long long b) {
    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    }
    long long bigger = a;
    long long smaller = b;
    if (b > a) {
        bigger = b;
        smaller = a;
    }
    long long difference = bigger % smaller;
    return bigGCD(smaller, difference);
}