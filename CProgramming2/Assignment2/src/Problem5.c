/**
  @file Problem5.c
  @brief Lab2-5. ���̺귯���� �����ϱ� (����� ����)
  */
#include <stdio.h>

#include "inc/KSH_Info.h"
#include "inc/KYB_info.h"
#include "inc/KHH_info.h"
#include "inc/HH_Info.h"
#include "inc/LMS_info.h"
#include "inc/LES_info.h"
#include "inc/LJH_Info.h"
// From 1�� ���̺귯�� - Google Docs https://docs.google.com/document/d/1eo4asjdsnz1feJiN1LKit5Me8OPaHuo03pQgVUeAVco/edit

#define PHH_name HH_name
#define PHH_hometown HH_hometown
#define PHH_age HH_age 
#define PHH_studentID HH_studentID
#define PHH_message HH_message
// ���ϵ� �̴ϼ� ó���� ���� ��ó����

#define KHH_name() printf("������");
// ���ϼ��� ���� �������� �̸��� ����� ���� �Լ� ����

#define name(n) n ## _name() 
#define hometown(n) n ## _hometown() 
#define age(n) n ## _age() 
#define studentID(n, i) n ## _studentID(i) 
#define allStudentID(n) for(int i = 1; i <= 10; i++) { printf("%d", studentID(n, i)); } 
#define message(n) n ## _message()
// �̴ϼ� ��� ��� Wrapper ��ũ��

/**
 * @brief �̸� �̴ϼ��� �޾� �ش� ���̺귯���� ����Ͽ� ������ �Ұ��մϴ�.
 */
#define introduce(n) printf("�̸�: "); name(n); printf(" ("); allStudentID(n); printf(")\n"); \
printf("����: %d\n", age(n)); \
printf("����: "); hometown(n); printf("\n"); \
printf("�޽���: "); message(n); \

/**
 * @brief ���� �Լ��Դϴ�.
 */
int main() {
	printf("2���� 1���� �Ұ��մϴ�!\n\n");

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