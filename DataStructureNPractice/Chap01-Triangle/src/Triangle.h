//============================================================================
// Name        : Chap01-Triangle.cpp
// Author      : refracta
// Version     : 2021년도 2학기
// Copyright   : 한국기술교육대학교 컴퓨터공학부 자료구조및실습
// Description : 삼각형 클래스
//============================================================================

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

/**
 * @brief 주어진 숫자의 절댓값을 계산한다.
 * @param N 절댓값을 취할 숫자
*/
#define ABS(N) ((N) < 0 ? -(N) : (N))
/**
 * @brief 두 위치 벡터 Point 구조체를 A, B를 벡터 AB Point 구조체로 변환한다.
 * @param A 점 A를 가리키는 위치 벡터 A
 * @param B 점 A를 가리키는 위치 벡터 A
*/
#define TO_VECTOR_POINT(A, B) (Point{(B).x - (A).x, (B).y - (A).y})
/**
 * @brief 2차원 외적 벡터의 절댓값을 계산한다.
 * @param A 외적 연산의 피연산 벡터 A
 * @param B 외적 연산의 피연산 벡터 B
*/
#define CROSS_PRODUCT_MAGNITUDE(A, B) ABS((A).x * (B).y - (A).y * (B).x)
/**
 * @brief 삼각형 ABC의 2배 면적을 가지는 평행 사변형의 넓이를 계산한다.
 * @param A 삼각형의 한 변 벡터 A
 * @param B 삼각형의 한 변 벡터 B
*/
#define TO_PARALLELOGRAM_AREA(A, B, C) CROSS_PRODUCT_MAGNITUDE(TO_VECTOR_POINT(A, B), TO_VECTOR_POINT(B,C))
#define TPA TO_PARALLELOGRAM_AREA
// TPA를 TO_PARALLELOGRAM_AREA의 별칭으로 설정

struct Point{
	int x;
	int y;
};

class Triangle{
private:
	Point p1;
	Point p2;
	Point p3;

public:
	// 주어진 좌표로 삼각형을 만들 수 없으면 std::runtime_error 예외를 발생해야 함
	Triangle(const Point& p1, const Point& p2, const Point& p3):
		p1(p1), p2(p2), p3(p3){
		if(area() == 0.0) {
			// 삼각형 두 변의 벡터를 구한 뒤 외적 연산을 통해 넓이를 구한 값이 0이면 두 벡터중 한 벡터 이상이 영벡터이거나
			// 두 벡터는 평행하다. 따라서 넓이가 0인 경우를 검사하면 삼각형이 성립하지 않는 조건에 대한 필터 분기가 가능하다.
			// 원래 부동 소수점 비교 연산의 경우 Threshold를 설정하여 비교하는 것이 보통이지만
			// 넓이가 0이 되는 경우 double area();의 반환 값이 정확히 0.0으로 설정되므로 == 연산자를 통해 비교할 수 있다.
			throw std::runtime_error("Couldn't create a triangle with the given coordinates.");
		}
	}
	// 삼각형의 면적
	double area(){
		return 0.5 * TPA(p1, p2, p3);
		// TO_PARALLELOGRAM_AREA 매크로를 이용하여 p1-p2-p3의 2배의 면적을 가지는 평행 사변형의 넓이를 구한 후
		// 이 값에 절반을 취하여 삼각형의 넓이를 계산한다.
	}
	// 주어진 좌표가 삼각형 내부에 있는 여부
	bool isInside(const Point& p){
		return TPA(p, p2, p3) + TPA(p1, p, p3) + TPA(p1, p2, p) <= TPA(p1, p2, p3);
		// 삼각형 내부에 점 p가 있는 경우 p1-p2-p3 삼각형의 넓이는
		// p-p2-p3, p1-p-p3, p1-p2-p 세 삼각형의 넓이 합보다 항상 크거나 같다.
	}
};

#endif
