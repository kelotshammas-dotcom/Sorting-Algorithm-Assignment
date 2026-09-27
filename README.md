# Sorting Fixed-Length Social Media IDs — MergeSort vs QuickSort

**Input data (8 IDs, 3 digits each):**
`324, 125, 456, 218, 102, 389, 275, 147`

Repo contents: `mergesort.c`, `quicksort.c`, `input.txt`, `mergesort_output.txt`,
`quicksort_output.txt`, this `README.md`.

> **Note on part (a):** the assignment wording "record the contents after each
> digit position" describes **Radix Sort**, not MergeSort. MergeSort is a
> comparison-based, divide-and-conquer algorithm — it has no concept of digit
> positions. What is traced below instead is the standard MergeSort structure:
> the array contents **after every merge step** (equivalent to "after every
> pass" for this algorithm).

---

## a) MergeSort — Execution Trace

Recursive top-down MergeSort splits the array down to single elements, then
merges pairs back together. With n = 8, splitting is 3 levels deep
(8 → 4 → 2 → 1), so there are **7 merge operations** in total.

```
Initial array                : 324 125 456 218 102 389 275 147

Merge #1 [0..0]&[1..1]        : 125 324 456 218 102 389 275 147   (1 comparison)
Merge #2 [2..2]&[3..3]        : 125 324 218 456 102 389 275 147   (1 comparison)
Merge #3 [0..1]&[2..3]        : 125 218 324 456 102 389 275 147   (3 comparisons)
Merge #4 [4..4]&[5..5]        : 125 218 324 456 102 389 275 147   (1 comparison)
Merge #5 [6..6]&[7..7]        : 125 218 324 456 102 389 147 275   (1 comparison)
Merge #6 [4..5]&[6..7]        : 125 218 324 456 102 147 275 389   (3 comparisons)
Merge #7 [0..3]&[4..7]        : 102 125 147 218 275 324 389 456   (7 comparisons)

Final sorted array            : 102 125 147 218 275 324 389 456
```

Total comparisons = 1+1+3+1+1+3+7 = **17**
Total merge calls = **7** (= n − 1, for n = 8)

---

## b) QuickSort — Execution Trace

Implementation uses the **Lomuto partition scheme** with the **last element
of each sub-array as pivot**.

```
Initial array                   : 324 125 456 218 102 389 275 147

Partition #1 pivot=147 (0..7)   : 125 102 147 218 324 389 275 456   pivot→idx 2  (7 comparisons)
Partition #2 pivot=102 (0..1)   : 102 125 147 218 324 389 275 456   pivot→idx 0  (1 comparison)
Partition #3 pivot=456 (3..7)   : 102 125 147 218 324 389 275 456   pivot→idx 7  (4 comparisons)
Partition #4 pivot=275 (3..6)   : 102 125 147 218 275 389 324 456   pivot→idx 4  (3 comparisons)
Partition #5 pivot=324 (5..6)   : 102 125 147 218 275 324 389 456   pivot→idx 5  (1 comparison)

Final sorted array              : 102 125 147 218 275 324 389 456
```

Total comparisons = 7+1+4+3+1 = **16**
Total partition calls = **5**

(Sub-arrays of size ≤ 1 need no partitioning: after #2, the left side of #1
is fully sorted; after #4/#5, the right side settles without further calls.)

---

## c) Comparative Analysis

| Criterion | MergeSort | QuickSort |
|---|---|---|
| **Passes / calls on this input** | 7 merge operations (fixed: always n−1 merges for n=8) | 5 partition calls (data-dependent; varies with pivot choice/input order) |
| **Comparisons on this input** | 17 | 16 |
| **Best case time** | O(n log n) | O(n log n) (balanced partitions) |
| **Average case time** | O(n log n) | O(n log n) |
| **Worst case time** | O(n log n) — *always*, regardless of input order | O(n²) — occurs when input is already sorted/reverse-sorted and pivot is picked as first/last element |
| **Space complexity** | O(n) extra space (temporary arrays during merge) | O(log n) extra space on average (recursion stack); O(n) worst case for a badly balanced recursion |
| **Stability** | Stable (equal keys retain relative order) | Not stable (swaps can reorder equal keys) |
| **In-place?** | No | Yes (sorts within the original array) |
| **Predictability** | Guaranteed O(n log n) performance regardless of input arrangement | Performance depends on pivot selection and input distribution |
| **Cache/practical performance** | Slightly more overhead due to extra array copies | Generally faster in practice due to in-place operation and good cache locality |

### Which is more appropriate for large fixed-length keys?

For this workload — **large volumes of fixed-length numeric IDs** (e.g.
millions of social-media user/post IDs) — the deciding factors are:

- **Guaranteed performance:** MergeSort's O(n log n) worst case protects
  against pathological slowdowns that QuickSort can hit on adversarial or
  already-sorted ID streams (a realistic risk if IDs arrive in
  near-sequential batches, e.g. newly created accounts).
- **Stability:** if IDs are ever sorted alongside other associated data
  (timestamps, user metadata) where relative order of equal keys must be
  preserved, MergeSort's stability is a real advantage; QuickSort offers none.
- **Memory cost:** QuickSort's O(log n) average auxiliary space is cheaper
  than MergeSort's O(n), which matters when n is very large (millions of
  IDs) and memory is constrained.
- **Fixed-length keys specifically:** since the IDs here are small,
  fixed-width integers, comparisons are cheap (O(1) per comparison), so the
  *number* of comparisons matters more than comparison cost — favoring
  whichever algorithm minimizes total operations and data movement.

**Conclusion:** For **large-scale, latency-sensitive, and unpredictable
input order** (typical of a social media application ingesting IDs
continuously), **MergeSort is the more appropriate choice** because its
worst-case O(n log n) guarantee avoids the quadratic-time risk that
QuickSort carries on sorted/nearly-sorted ID streams, and its stability is
valuable when IDs are sorted together with related records. If memory is
tightly constrained and input order is known to be sufficiently random
(e.g., via randomized pivot selection or median-of-three), **QuickSort**
remains an excellent practical alternative due to its lower space overhead
and strong average-case speed.

---

## How to compile and run

```bash
gcc -O2 -o mergesort mergesort.c && ./mergesort
gcc -O2 -o quicksort quicksort.c && ./quicksort
```
