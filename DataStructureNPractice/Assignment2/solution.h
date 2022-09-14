//============================================================================
// Name        : solution.h
// Author      : refracta
// Version     : 2021년도 2학기
// Copyright   : 한국기술교육대학교 컴퓨터공학부 자료구조및실습
// Description : LeetCode 389, 771 Solution
//============================================================================

#ifndef SOLUTION_H_
#define SOLUTION_H_

#define FAST_LOOP(STR, VAR) for(int VAR = 0, l = STR.length(); VAR < l; VAR++)
// 문제 솔루션용 루프 매크로

class Solution {
    public:
		/*
		 * LeetCode 389 
		 * https://leetcode.com/problems/find-the-difference/
		 * Status: Accepted
		 * Runtime: 0 ms, faster than 100.00% of C++ online submissions for Find the Difference.
		 * Memory Usage: 6.7 MB, less than 24.81% of C++ online submissions for Find the Difference.
		 * n = s.length(), m = t.length(), l = n + m이라고 하면
		 * s와 t에 대한 FAST_LOOP를 고려하였을 때, 각 루프당 n번 m번 반복하므로
		 * O(N) = O(l) = O(n) + O(m) <선형 시간>
		 */
		char findTheDifference(string s, string t) {
            char c = 0;
            FAST_LOOP(s, i) {
                c ^= s[i];
				// s의 원소 전부와 xor 연산
				// string을 character set으로 생각하였을 때 s ⊂ t가 성립하고 t - s가 character 원소 1개이므로 s, t의 모든 원소를 xor 연산하면 나머지 원소를 구할 수 있다. (set이 아닌 경우에도 중복은 제거되므로 성립한다.)
            }
            FAST_LOOP(t, i) {
                c ^= t[i];
				// t의 원소 전부와 xor 연산
            } 
            return c;
		};
		
		/*
		 * LeetCode 771 
		 * https://leetcode.com/problems/jewels-and-stones/
		 * Status: Accepted
		 * Runtime: 0 ms, faster than 100.00% of C++ online submissions for Jewels and Stones.
		 * Memory Usage: 6.1 MB, less than 96.68% of C++ online submissions for Jewels and Stones.
		 * n = jewels.length(), m = t.length(), l = n + m이라고 하면
		 * jewels와 stones에 대한 FAST_LOOP를 고려하였을 때, 각 루프당 n번 m번 반복하므로
		 * O(N) = O(l) = O(n) + O(m) <선형 시간>
		 */
        int numJewelsInStones(string jewels, string stones) {
            bool flags['z' - 'A' + 1] = { 0, };
			// [A-Za-z]의 bool flag를 담을 수 있는 bool 배열 선언
            FAST_LOOP(jewels, i) {
                flags[jewels[i] - 'A'] = true;
				// 보석인 알파벳 원소는 true로 초기화
            }
            int number_of_jewels = 0;
            FAST_LOOP(stones, i) {
                flags[stones[i] - 'A'] ? number_of_jewels++ : NULL;
				// 돌이 보석인 경우에만 보석 개수 증가
            }
            return number_of_jewels;
        };
};

#endif
