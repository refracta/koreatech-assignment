import java.util.ArrayDeque;
import java.util.Queue;

/**
 * @copyright 한국기술교육대학교 컴퓨터공학부 객체지향개발론및실습
 * @version 2022년도 2학기
 * @author 김상진
 * 0,1,2,3으로 표시되는 맵이 주어짐
 * 0: 통로
 * 1: 시작위치
 * 2: 보석
 * 3: 벽
 * 목적: 시작위치에서 보석까지의 최단 경로 찾기 
 * 이동은 상하좌우로만 할 수 있음
 * 맵에는 항상 보석이 하나 주어짐
 * 보석을 찾을 수 없으면 최단 경로의 길이는 -1을 출력해야 함
 * 주어진 해결책에서 코드 냄세를 찾아 리펙토링하세요.
 * 요구사항. 주석에 다음을 포함하여 주세요.
 * 1) 리펙토링한 순서
 * 2) 각 코드 냄새를 제거하기 위해 리펙토링한 방법
 */
public class OriginalCodeSmell {
	// BFS를 이용하여 시작 위치부터 보석을 찾는다.
	public static int solve(int[][] map) {
		// 시작 위치 탐색
		int startR = 0;
		int startC = 0; 
		FOUND:
		for(int r=0; r<map.length; ++r)
			for(int c=0; c<map[0].length; ++c) {
				if(map[r][c]==1) {
					startR = r;
					startC = c;
					break FOUND;
				}
			}
		// 시작 위치부터 BFS 수행
		int minLength = -1;
		boolean[][] visited = new boolean[map.length][map[0].length];
		Queue<Integer> rowQueue = new ArrayDeque<>();
		Queue<Integer> colQueue = new ArrayDeque<>();
		Queue<Integer> lengthQueue = new ArrayDeque<>();
		rowQueue.add(startR);
		colQueue.add(startC);
		lengthQueue.add(0);
		visited[startR][startC] = true;
		while(!rowQueue.isEmpty()) {
			int currR = rowQueue.poll();
			int currC = colQueue.poll();
			int length = lengthQueue.poll();
			// 4개 방향으로 탐색 진행
			if(currR+1<map.length && !visited[currR+1][currC]) {
				if(map[currR+1][currC]==2) {
					minLength = length+1;
					break;
				}
				else if(map[currR+1][currC]==0) {
					visited[currR+1][currC] = true;
					rowQueue.add(currR+1);
					colQueue.add(currC);
					lengthQueue.add(length+1);
				}
			}
			if(currR-1>=0 && !visited[currR-1][currC]) {
				if(map[currR-1][currC]==2) {
					minLength = length+1;
					break;
				}
				else if(map[currR-1][currC]==0) {
					visited[currR-1][currC] = true;
					rowQueue.add(currR-1);
					colQueue.add(currC);
					lengthQueue.add(length+1);
				}
			}
			if(currC+1<map[0].length && !visited[currR][currC+1]) {
				if(map[currR][currC+1]==2) {
					minLength = length+1;
					break;
				}
				else if(map[currR][currC+1]==0) {
					visited[currR][currC+1] = true;
					rowQueue.add(currR);
					colQueue.add(currC+1);
					lengthQueue.add(length+1);
				}
			}
			if(currC-1>=0 && !visited[currR][currC-1]) {
				if(map[currR][currC-1]==2) {
					minLength = length+1;
					break;
				}
				else if(map[currR][currC-1]==0) {
					visited[currR][currC-1] = true;
					rowQueue.add(currR);
					colQueue.add(currC-1);
					lengthQueue.add(length+1);
				}
			}
		}
		return minLength;
	}
	public static void main(String[] args) {
		int[][] map = {
			{3,0,3,0,3,1,3},
			{3,0,0,0,3,0,3},
			{3,0,3,0,0,0,3},
			{3,0,3,3,3,0,3},
			{3,0,0,2,3,0,0},
			{3,3,3,3,3,3,3}
		};
		System.out.println(solve(map));
		map = new int[][]{
			{3,3,3,0,3,0,3},
			{3,0,0,0,3,0,3},
			{1,0,3,0,3,0,3},
			{3,0,3,3,3,0,3},
			{3,0,3,2,0,0,0},
			{3,3,3,3,3,3,3}
		};
		System.out.println(solve(map));
		map = new int[][]{
			{3,3,3,0,3,3,3},
			{3,0,0,0,3,2,3},
			{1,0,3,0,0,0,3},
			{3,0,3,3,3,0,3}
		};
		System.out.println(solve(map));
	}

}
