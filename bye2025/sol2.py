import sys

def solve():
    # Read all input at once for speed
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    t = int(input_data[0])
    results = []
    
    curr = 1
    for _ in range(t):
        r = input_data[curr]
        curr += 1
        
        # Assertion as requested: ensure only 's' and 'u' are present
        assert all(c == 's' or c == 'u' for c in r), "String must only contain 's' or 'u'"
        
        n = len(r)
        s_indices = [i for i, char in enumerate(r) if char == 's']
        
        # Case 1: No 's' in the string
        if not s_indices:
            # We need at least two 's'. 
            # Best to make it "s u s" (2 ops) or "s s" (2 ops) 
            # If length is 3, "sus" is 0 ops but requires 2 changes. 
            # If length is 4, "suss" is 3 changes.
            # Actually, for 'uuuu', turning index 0 and 2 to 's' gives 'susu', 
            # but 'u' at index 3 has no 's' to its right. 
            # So 'uuuu' -> 'suss' (3 ops) or 'ssuu' -> 'ssss' (4 ops).
            # The rule: if all 'u', change all but one 'u' at a midpoint, or just all.
            # Minimum for 'uuuu' is 3 (suss). Minimum for 'uuu' is 2 (sus).
            if n == 3:
                results.append(2) # sus
            else:
                results.append(n - 1)
            continue

        # Case 2: At least one 's' exists
        ops = 0
        
        # Rule: Any 'u' outside the first and last 's' must be changed
        first_s = s_indices[0]
        last_s = s_indices[-1]
        
        ops += first_s # u's at the start
        ops += (n - 1 - last_s) # u's at the end
        
        # Rule: Between any two 's', there can be at most one 'u'
        for i in range(len(s_indices) - 1):
            gap = s_indices[i+1] - s_indices[i] - 1
            if gap > 1:
                # If gap is 2 (suus), must change both to 's'
                # If gap is 3 (suuus), must change all to 's' 
                # because a single 'u' wouldn't be in the middle.
                ops += gap
            elif gap == 1:
                # Check if it's perfectly centered (it is, since distance is 1 and 1)
                pass
        
        # Final Check: Must have at least two 's'
        # If the string became "s" with only 1 's' total, we need one more.
        total_s = (n - ops)
        if total_s < 2:
            ops += (2 - total_s)
            
        results.append(ops)

    print('\n'.join(map(str, results)))

if __name__ == "__main__":
    solve()