#ifndef __CBattleHead_H_
#define __CBattleHead_H_

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

//CUI ����
void CursorView(char show); //Ŀ�� �ѱ�/����
void gotoxy(int x, int y); //Ŀ�� ��ġ
void txtclr(int num); //�ؽ�Ʈ ��

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_Z 122

//���� ���� ����
struct UserInformation {
	char username[30]; //�����̸�
	int user_hp;  //HP
	int user_max_hp; //�ִ�HP
	int user_str; //����
	int user_vit; //���
	int user_dex; //�ɼ�
	int user_agi; //��ø
	int user_int; //����
}UsrInf;

//���� ���� ����
struct MonsterInformation {
	char monstername[20]; //�����̸�
	int monster_hp; //���� HP
	int monster_max_hp; //���� �ִ�HP
	int monster_str; //���� ����
	int monster_vit; //���� ���
	int monster_dex; //���� �ɼ�
	int monster_agi; //���� ��ø
	int monster_int; //���� ����
}MonInf;

//���� �ý��� ����
#define USER 12345 //(���ڴ� �ǹ̾���)
#define MONSTER 67890 //(���ڴ� �ǹ̾���)

struct inBattleValue {
	int turn_go_first; //����
	int turn_go_second; //�İ�

	int user_con; //���� Condition
	int user_attack_count; //������ ���� 3�ϵ��� ������ �ܼ�(CON+���� 1�� ����)
	int user_guard_count; //������ ���� 3�ϵ��� ����� �ܼ�(CON+���� 1�� ����)
	int user_avoid_count; //������ ���� 3�ϵ��� ȸ���� �ܼ�(CON-���� 1�� ����)
	int user_magic_count; //������ ���� 3�ϵ��� ���������� �ܼ�(CON-���� 1�� ����)
	int user_estrus_count; //������ �� ����
	//int is_user_can_act; //������ � �ൿ�� ���� �� �ִ��� ����(CON�� -���̸� �ش� �� �ൿ�Ҵ�)
}BattleVal;

//�Լ���
void UserInfoSetup(); //��Ʈ�� �� �������
void BattleTurnStartMessage(int turn_num); //�������۸޼��� �� �� ���¸޼��� ���
void UserSetCondition(); //���� ����� �� ����
void UserAct(); //������ �Ͽ��� �ൿ�� �� ����


#endif