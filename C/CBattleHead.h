#ifndef __CBattleHead_H_
#define __CBattleHead_H_

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

//CUI 관련
void CursorView(char show); //커서 켜기/끄기
void gotoxy(int x, int y); //커서 위치
void txtclr(int num); //텍스트 색

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_Z 122

//유저 정보 관련
struct UserInformation {
	char username[30]; //유저이름
	int user_hp;  //HP
	int user_max_hp; //최대HP
	int user_str; //공격
	int user_vit; //방어
	int user_dex; //능숙
	int user_agi; //민첩
	int user_int; //지력
}UsrInf;

//몬스터 정보 관련
struct MonsterInformation {
	char monstername[20]; //몬스터이름
	int monster_hp; //몬스터 HP
	int monster_max_hp; //몬스터 최대HP
	int monster_str; //몬스터 공격
	int monster_vit; //몬스터 방어
	int monster_dex; //몬스터 능숙
	int monster_agi; //몬스터 민첩
	int monster_int; //몬스터 지력
}MonInf;

//전투 시스템 관련
#define USER 12345 //(숫자는 의미없음)
#define MONSTER 67890 //(숫자는 의미없음)

struct inBattleValue {
	int turn_go_first; //선공
	int turn_go_second; //후공

	int user_con; //유저 Condition
	int user_attack_count; //유저가 지난 3턴동안 공격한 휫수(CON+마다 1씩 증가)
	int user_guard_count; //유저가 지난 3턴동안 방어한 휫수(CON+마다 1씩 증가)
	int user_avoid_count; //유저가 지난 3턴동안 회피한 휫수(CON-마다 1씩 감소)
	int user_magic_count; //유저가 지난 3턴동안 마법공격한 휫수(CON-마다 1씩 감소)
	int user_estrus_count; //유저의 ♡ 개수
	//int is_user_can_act; //유저가 어떤 행동을 취할 수 있는지 여부(CON이 -대이면 해당 턴 행동불능)
}BattleVal;

//함수들
void UserInfoSetup(); //인트로 및 유저등록
void BattleTurnStartMessage(int turn_num); //전투시작메세지 및 턴 상태메세지 출력
void UserSetCondition(); //유저 컨디션 값 세팅
void UserAct(); //유저의 턴에서 행동할 것 선택


#endif