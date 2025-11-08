import sys
input = sys.stdin.readline
INF = 10**30

def solve_one(a):
    n = len(a)
    w = [abs(a[i] - a[(i+1) % n]) for i in range(n)]

    # linear solve assuming whether edge (n-1,0) is used or not
    def solve_linear(use_last_edge):
        # dp0[i] = min cost up to i (inclusive), with i **not covered** yet
        # dp1[i] = min cost up to i, with i covered
        dp0 = [INF] * n
        dp1 = [INF] * n
        if use_last_edge:
            dp1[0] = w[n-1]  # cover 0 and n-1 by that edge
        else:
            dp0[0] = 0

        for i in range(1, n):
            # transitions from i-1 → i using edge (i-1, i)
            # from dp1[i-1]:
            dp0[i] = min(dp0[i], dp1[i-1])
            dp1[i] = min(dp1[i], dp1[i-1] + w[i-1])
            # from dp0[i-1], must pick edge (i-1, i)
            dp1[i] = min(dp1[i], dp0[i-1] + w[i-1])

        # at final vertex n-1
        if use_last_edge:
            # since we used the edge linking (n-1,0), vertex n-1 is covered already
            return min(dp0[n-1], dp1[n-1])
        else:
            # must end covered (because vertex n-1 needs a neighbor equal)
            return dp1[n-1]

    return min(solve_linear(False), solve_linear(True))


def main():
    t = int(input().strip())
    out = []
    for _ in range(t):
        n = int(input().strip())
        a = list(map(int, input().split()))
        out.append(str(solve_one(a)))
    print("\n".join(out))


if __name__ == "__main__":
    main()
