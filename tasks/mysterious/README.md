# MYSTERIOUS ARRAY

There is an array that contains a permutation of the numbers 1, 2, ..., n. The elements of the array are 1-indexed.

However, you don't know the contents of the array. Instead, you are given the results of q queries of the form "what is the minimum value between positions a and b?"

Your task is to count the number of arrays that match the queries.

## INPUT

The first input line contains two integers n and q: the size of the array and the number of queries.

Then there are q lines that describe the queries. Each line contains three integers a, b, and x: the minimum value between positions $a$ and b is x.

## OUTPUT

Print one integer: the number of arrays modulo 10^9+7.

## CONSTRAINTS

- Subtask 1: 1 <= n,q <= 10 (brute force solution)
- Subtask 2: 1 <= n,q <= 1000 (model solution with bad implementation)
- Subtask 3: 1 <= n,q <= 10^5 (model solution)

## EXAMPLE

Input:
```
8 3
3 7 2
6 8 2
4 5 5
```

Output:
```
576
```

## NOTE

A quite similar problem has been used in Petrozavodsk camp in 2008 (https://www.e-olymp.com/en/problems/3080). However, I don't think the problem is well-known among the NOI contestants.

