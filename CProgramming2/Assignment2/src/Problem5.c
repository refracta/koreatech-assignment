/**
  @file Problem5.c
  @brief Lab2-5. 라이브러리로 협업하기 (김덕수 교수)
  */
#include <stdio.h>

#include "inc/KSH_Info.h"
#include "inc/KYB_info.h"
#include "inc/KHH_info.h"
#include "inc/HH_Info.h"
#include "inc/LMS_info.h"
#include "inc/LES_info.h"
#include "inc/LJH_Info.h"
// From 1팀 라이브러리 - Google Docs https://docs.google.com/document/d/1eo4asjdsnz1feJiN1LKit5Me8OPaHuo03pQgVUeAVco/edit

#define PHH_name HH_name
#define PHH_hometown HH_hometown
#define PHH_age HH_age 
#define PHH_studentID HH_studentID
#define PHH_message HH_message
// 통일된 이니셜 처리를 위한 전처리기

#define KHH_name() printf("김혜현");
// 통일성을 위해 영문으로 이름을 출력한 팀원 함수 스왑

#define name(n) n ## _name() 
#define hometown(n) n ## _hometown() 
#define age(n) n ## _age() 
#define studentID(n, i) n ## _studentID(i) 
#define allStudentID(n) for(int i = 1; i <= 10; i++) { printf("%d", studentID(n, i)); } 
#define message(n) n ## _message()
// 이니셜 기반 출력 Wrapper 매크로

/**
 * @brief 이름 이니셜을 받아 해당 라이브러리를 사용하여 팀원을 소개합니다.
 */
#define introduce(n) printf("이름: "); name(n); printf(" ("); allStudentID(n); printf(")\n"); \
printf("나이: %d\n", age(n)); \
printf("고향: "); hometown(n); printf("\n"); \
printf("메시지: "); message(n); \

/**
 * @brief 시작 함수입니다.
 */
int main() {
	printf("2주차 1팀을 소개합니다!\n\n");

	introduce(KSH);
	printf("============================================================\n");
	introduce(KYB);
	printf("============================================================\n");
	introduce(KHH);
	printf("============================================================\n");
	introduce(PHH);
	printf("============================================================\n");
	introduce(LMS);
	printf("============================================================\n");
	introduce(LES);
	printf("============================================================\n");
	introduce(LJH);
	printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}