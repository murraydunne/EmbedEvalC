// Return 2^n modulo p (be aware of numerics).
// This function requires 64-bit numbers.
/// modp(3, 5) -> 3
/// modp(1101, 101) -> 2
/// modp(0, 101) -> 1
/// modp(3, 11) -> 8
/// modp(100, 101) -> 1

long long modp(long long n, long long p) { //***
    long long result = 1;
    long long x = 2;

    while (n != 0) {
        if(n % 2 == 1) {
            result = (result * x) % p;
        }
        x = (x * x) % p;
        n /= 2;
    }
    
    return result % p;
}
//HUMAN NOTE: modified from humaneval task 49 - changes made
//***
assert(modp(###0I###, ###1I###) == ###_I###);
