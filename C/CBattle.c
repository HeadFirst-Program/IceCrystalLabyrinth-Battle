#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "CBattleHead.h"
//https://eskeptor.tistory.com/25 ������� ���� ���

int main() {
	int turn_num = 0;

	UserInfoSetup();
	while (1) {
		turn_num++;
		BattleTurnStartMessage(turn_num);
		UserSetCondition();
		UserAct();
	}
}