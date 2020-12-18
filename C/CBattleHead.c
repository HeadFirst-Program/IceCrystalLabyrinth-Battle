#define _CRT_SECURE_NO_WARNINGS
#include "CBattleHead.h"

//CUI ����
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void txtclr(int num) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}


void UserInfoSetup() {
	int difficulty;

	printf("[[������ �̱� �����ý��� Ŭ�� ������Ʈ by VDoring]]");
	printf("\n����� �̸���? : ");
	scanf("%s", UsrInf.username);

	printf("\n���̵��� �����ϼ��� >");
	printf("\n[1]����\t[2]����\t[3]�����");
	printf("\n�����Է� : ");
	scanf("%d", &difficulty);
	switch (difficulty) {
	case 1:
		UsrInf.user_hp = 250;
		UsrInf.user_max_hp = 250;
		UsrInf.user_str = 64;
		UsrInf.user_vit = 30;
		UsrInf.user_dex = 39;
		UsrInf.user_agi = 34;
		UsrInf.user_int = 29;
		BattleVal.user_attack_count = 0;
		BattleVal.user_guard_count = 0;
		BattleVal.user_avoid_count = 0;
		BattleVal.user_magic_count = 0;
		BattleVal.user_estrus_count = 0;

		strcpy(MonInf.monstername, "������ ������");
		MonInf.monster_hp = 100;
		MonInf.monster_max_hp = 100;
		MonInf.monster_str = 30;
		MonInf.monster_vit = 60;
		MonInf.monster_dex = 30;
		MonInf.monster_agi = 35;
		MonInf.monster_int = 30;

		printf("���� ���̵� ������ �Ϸ�Ǿ����ϴ�.");
		break;
	case 2:
		UsrInf.user_hp = 140;
		UsrInf.user_max_hp = 140;
		UsrInf.user_str = 37;
		UsrInf.user_vit = 36;
		UsrInf.user_dex = 31; //�׽�Ʈ��
		UsrInf.user_agi = 37;
		UsrInf.user_int = 30;
		BattleVal.user_attack_count = 0;
		BattleVal.user_guard_count = 0;
		BattleVal.user_avoid_count = 0;
		BattleVal.user_magic_count = 0;
		BattleVal.user_estrus_count = 0;

		strcpy(MonInf.monstername, "���� ������");
		MonInf.monster_hp = 150;
		MonInf.monster_max_hp = 150;
		MonInf.monster_str = 40;
		MonInf.monster_vit = 40;
		MonInf.monster_dex = 35;
		MonInf.monster_agi = 35;
		MonInf.monster_int = 35;

		printf("���� ���̵� ������ �Ϸ�Ǿ����ϴ�.");
		break;
	case 3:
		UsrInf.user_hp = 110;
		UsrInf.user_max_hp = 110;
		UsrInf.user_str = 24;
		UsrInf.user_vit = 22;
		UsrInf.user_dex = 20;
		UsrInf.user_agi = 24;
		UsrInf.user_int = 16;
		BattleVal.user_attack_count = 0;
		BattleVal.user_guard_count = 0;
		BattleVal.user_avoid_count = 0;
		BattleVal.user_magic_count = 0;
		BattleVal.user_estrus_count = 0;

		strcpy(MonInf.monstername, "������ ������");
		MonInf.monster_hp = 200;
		MonInf.monster_max_hp = 200;
		MonInf.monster_str = 50;
		MonInf.monster_vit = 50;
		MonInf.monster_dex = 50;
		MonInf.monster_agi = 50;
		MonInf.monster_int = 50;

		printf("����� ���̵� ������ �Ϸ�Ǿ����ϴ�.");
		break;
	default:
		UsrInf.user_hp = 140;
		UsrInf.user_str = 37;
		UsrInf.user_vit = 36;
		UsrInf.user_dex = 31;
		UsrInf.user_agi = 37;
		UsrInf.user_int = 30;
		BattleVal.user_attack_count = 0;
		BattleVal.user_guard_count = 0;
		BattleVal.user_avoid_count = 0;
		BattleVal.user_magic_count = 0;
		BattleVal.user_estrus_count = 0;

		strcpy(MonInf.monstername, "���� ������");
		MonInf.monster_hp = 150;
		MonInf.monster_max_hp = 150;
		MonInf.monster_str = 40;
		MonInf.monster_vit = 40;
		MonInf.monster_dex = 35;
		MonInf.monster_agi = 35;
		MonInf.monster_int = 35;

		printf("�̻��� �̸��̱���.. �׳� ���볭�̵��� �����Ҳ���.");
		printf("\n���� ���̵� ������ �Ϸ�Ǿ����ϴ�.");
		break;
	}
}

void BattleTurnStartMessage(int turn_num) {
	printf("\n\n\n");
	if (turn_num == 1) {
		Sleep(1000);
		printf("%s ����!", MonInf.monstername);
		printf("\n%s:������!��", UsrInf.username);
	}

	srand((unsigned int)time(NULL)); //���� seed�� �ʱ�ȭ
	int turn_first_second_select; //����,�İ� ���ϱ�
	turn_first_second_select = rand();

	printf("\n\n-%d�� ", turn_num);
	if (turn_first_second_select % 2 == 1) {
		BattleVal.turn_go_first = USER;
		BattleVal.turn_go_second = MONSTER;
		printf("����---------------");
	}
	else {
		BattleVal.turn_go_first = MONSTER;
		BattleVal.turn_go_second = USER;
		printf("�İ�---------------");
	}
}

void UserSetCondition() {
#define MAX_RAND_NUM 20
	srand((unsigned int)time(NULL)); //���� seed�� �ʱ�ȭ
	CursorView(0);

	int condition_rand_arr[MAX_RAND_NUM]; //�������� �������� Con�� ����
	int visible_i = 0; //ȭ�鿡 ����ϱ� ���� ���Ǵ� ���� i

	for (int i = 0; i < MAX_RAND_NUM; i++) { //���� �� ���ϱ�(����:0~99)
		condition_rand_arr[i] = rand() % 100;
	}
	
	int key_input; //Ű �Է� �� ����
	int is_double_backspace = 0; //(CUI) �̹� �齺���̽��� 2�� �Ͽ����� ����
	int temp_condition = 0; //������ ���������� �ʱ� Con��
	printf("\n�ذ��� Ű�� �����ּ���.");
	printf("\nCON : ");
	while (1) {
		if (condition_rand_arr[visible_i] < 10) { //���� �������ڰ� 1�ڸ����ΰ�� CUI�� ������ �ʰ� ���� ����
			printf("  ");
			printf("\b\b");
			is_double_backspace = 1;
		}

		printf("%d", condition_rand_arr[visible_i]); //�������� ���
		Sleep(60);

		if (is_double_backspace == 1) { //1�ڸ����� �������ڿ� ���� �̹� CUI������ �Ǿ��� ���
			printf("\b");
			is_double_backspace = 0;
		}
		else { //�������ڰ� 2�ڸ��ϰ��
			printf("\b\b");
		}

		//key_input = _getch(); // �Է°��� ������ ���� ����ߴٰ� ������ ���� ���� ����
		if (_kbhit()) {
			key_input = _getch();
			if((key_input == KEY_Z) || (key_input == KEY_ENTER)) {
				temp_condition = condition_rand_arr[visible_i]; //������ ������ Con�� ����
				break;
			}
		}

		if (visible_i >= MAX_RAND_NUM - 1) { //condition_rand_arr�迭�� ������ ǥ��������� ó������ ���ư�
			visible_i = 0;
		}
		visible_i++;
	}

	switch (BattleVal.user_attack_count) { //������ Attack �ܼ��� ���� Con�� +
	case 9:
		temp_condition += 9;
		//printf(GREEN"+9"); �� ���ϸ��̼� ǥ�� �κ��� ���� Attack �ý����� �� ��������� �ֱ�!
	case 8:
		temp_condition += 8;
	case 7:
		temp_condition += 7;
	case 6:
		temp_condition += 6;
	case 5:
		temp_condition += 5;
	case 4:
		temp_condition += 4;
	case 3:
		temp_condition += 3;
	case 2:
		temp_condition += 2;
	case 1:
		temp_condition += 1;
	}

	switch (BattleVal.user_guard_count) { //������ Guard �ܼ��� ���� Con�� +
	case 9:
		temp_condition += 9;
		//printf(GREEN"+9"); �� ���ϸ��̼� ǥ�� �κ��� ���� Defence �ý����� �� ��������� �ֱ�!
	case 8:
		temp_condition += 8;
	case 7:
		temp_condition += 7;
	case 6:
		temp_condition += 6;
	case 5:
		temp_condition += 5;
	case 4:
		temp_condition += 4;
	case 3:
		temp_condition += 3;
	case 2:
		temp_condition += 2;
	case 1:
		temp_condition += 1;
	}

	switch (BattleVal.user_avoid_count) { //������ Avoid �ܼ��� ���� Con�� -
	case 3:
		temp_condition -= 3;
		//printf(RED"-3"); �� ���ϸ��̼� ǥ�� �κ��� ���� �ý����� �� ��������� �ֱ�!
	case 2:
		temp_condition -= 2;
	case 1:
		temp_condition -= 1;
	}
	if (temp_condition < 0) { //���� Con�� ��굵�� Con���� ���̳ʽ�(-)���
		goto CalcForcedStop;
	}

	switch (BattleVal.user_magic_count) { //������ Magic �ܼ��� ���� Con�� -
	case 6:
		temp_condition -= 6;
		//printf(RED"-6"); �� ���ϸ��̼� ǥ�� �κ��� ���� �ý����� �� ��������� �ֱ�!
	case 5:
		temp_condition -= 5;
	case 4:
		temp_condition -= 4;
	case 3:
		temp_condition -= 3;
	case 2:
		temp_condition -= 2;
	case 1:
		temp_condition -= 1;
	}
	if (temp_condition < 0) { //���� Con�� ��굵�� Con���� ���̳ʽ�(-)���
		goto CalcForcedStop;
	}

	switch (BattleVal.user_estrus_count) { //������ �� ������ ���� Con�� -
	case 3:
		temp_condition -= 19;
		//printf(RED"-19"); �� ���ϸ��̼� ǥ�� �κ��� ���� �ý����� �� ��������� �ֱ�!
	case 2:
		temp_condition -= 13;
	case 1:
		temp_condition -= 7;
	}
	if (temp_condition < 0) { //���� Con�� ��굵�� Con���� ���̳ʽ�(-)���
		goto CalcForcedStop;
	}

	temp_condition += UsrInf.user_dex; //������ DEX ������ ����ŭ Con�� +
	//printf(GREEN"+DEX"); �� ���ϸ��̼� ǥ�� �κ��� ���� �ý����� �� ��������� �ֱ�!

CalcForcedStop:
	BattleVal.user_con = temp_condition; //���� Con�� ���� ����
	if (BattleVal.user_con < 0) { //���� ������ Con���� ���̳ʽ�(-)��� ������ �ش� �� ���� �ƹ��͵� �� �� ����.
		printf("\n%s�� �߽��� �Ҿ���!", UsrInf.username);
		printf("\n%s�� ���� �ڼ��� ���� ����� �ִ�.", UsrInf.username);
		return;
	}
	printf("\n������ ������� %d�̴�!", BattleVal.user_con);
}

void UserAct() {
	if (BattleVal.user_con < 0) { //������ Con�� -�� �ൿ�Ҵ��̶��
		return;
	}

	int user_act; //�ش��Ͽ� ������ ������ �ൿ
	int key_input1; //���� Ű �Է� 1
	int key_input2; //���� Ű �Է� 2
	int key_input2_continue; //���� Ű ���� Ȯ��

	printf("\n\n");
	if (BattleVal.turn_go_first == USER) { //������ �����̸�
		printf("         Attack");
	}
	else {
		printf("         Counter");
	}
	//printf("                      ESC: item(�̱���)");
	printf("\n\n           ��");
	printf("\nAvoid   ��    ��   Magic");
	printf("\n           ��");
	printf("\n\n          Guard");
	
	printf("\n\nMy HP: "); printf("%d/%d  ", UsrInf.user_hp, UsrInf.user_max_hp);
	for (int i = 0; i < (int)UsrInf.user_hp / 10; i++) {
		printf("��");
	}
	printf("\nEnemy: "); printf("%d/%d  ", MonInf.monster_hp, MonInf.monster_max_hp);
	for (int i = 0; i < (int)MonInf.monster_hp / 10; i++) {
		printf("��");
	}
	
	BattleVal.user_nowturn_attack_count = 0; //���ο� ���� �����Ƿ� �ʱ�ȭ
	BattleVal.user_nowturn_guard_count = 0; //���ο� ���� �����Ƿ� �ʱ�ȭ
	BattleVal.user_nowturn_avoid_count = 0; //���ο� ���� �����Ƿ� �ʱ�ȭ
	BattleVal.user_nowturn_magic_count = 0; //���ο� ���� �����Ƿ� �ʱ�ȭ
	if (BattleVal.turn_go_first == MONSTER) { //���Ͱ� �����̸� ���Ͱ� ���� �ൿ�� ����
		printf("\n");
		MonsterSetCondition();
		MonsterAct();
	}
	printf("\n\n");
	key_input1 = _getch();
	if (key_input1 == KEY_ESC) {
		//printf("������ĭ����");
	}
	if (_kbhit()) { //����Ű�� ������ ��쿡 �����Ͽ� �۵��Ѵ�
		key_input2 = _getch();
		if (key_input2 == KEY_UP) {
			//printf("����");
			//���� ���ݿ� ���� CON�� ���ʽ� �ý��� �����.(��, 3�� �̻� �������� ���ʽ��� ����������) //////
			if (BattleVal.turn_go_first == USER) { //������ �����̸�
				BattleVal.user_nowturn_attack_count++;
				printf("CON+ ATK"); //���� 1�ܰ�
				Sleep(850);
				key_input2_continue = 0;
				if (_kbhit()) {
					key_input2_continue = _getch(); //����ڰ� Ű�� ��� ������ �ִ��� Ȯ��
					key_input2_continue = _getch(); //����ڰ� Ű�� ��� ������ �ִ��� Ȯ��
				}
				if (key_input2_continue == KEY_UP) {
					BattleVal.user_nowturn_attack_count++;
					printf("\nCON+ ATK+"); //���� 2�ܰ�
					Sleep(850);
					key_input2_continue = 0;
					if (_kbhit()) {
						key_input2_continue = _getch(); //����ڰ� Ű�� ��� ������ �ִ��� Ȯ��
						key_input2_continue = _getch(); //����ڰ� Ű�� ��� ������ �ִ��� Ȯ��
					}
					if (key_input2_continue == KEY_UP) {
						BattleVal.user_nowturn_attack_count++;
						printf("\nCON+ ATK++"); //���� 3�ܰ�
						Sleep(500);
					}
				}
				UserAttack(BattleVal.user_nowturn_attack_count); //���� ���� ������ ����
			}
			else { //������ �İ��̸�
				BattleVal.user_nowturn_attack_count++;
				//MonsterAct(); //���Ͱ� �����̹Ƿ� ���Ͱ� ���� �ൿ 
				UserCounter(); //���� ī���� ������ ����
			}
		}
		else if (key_input2 == KEY_DOWN) {
			//printf("�Ʒ���");
		}
		else if (key_input2 == KEY_LEFT) {
			//printf("��������");
		}
		else if (key_input2 == KEY_RIGHT) {
			//printf("����������");
		}
	}
}

void UserAttack(int user_atkcnt) {
	int nowturn_plus_attack_damage = 0;

	switch (user_atkcnt) {
	case 1: //ATK
		printf("%s�� ������ �ڼ��� ����!",UsrInf.username);
		MonsterSetCondition();
		//MonsterAct(); ���� �� �Լ��� ���Ͱ� �İ��ϋ��� �ý����� �ֱ�
		printf("\n\n%s�� ����!", UsrInf.username);
		if (BattleVal.user_con > BattleVal.mon_con) { //������ CON�� �� ���ٸ�
			nowturn_plus_attack_damage = UsrInf.user_str + 10; //(�ӽ� ���ط�)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\nCounter!! %s�� %d�� ������!", MonInf.monstername, nowturn_plus_attack_damage);
			Sleep(500);
		}
		else { //���Ͱ� CON�� �� ���ٸ�
			nowturn_plus_attack_damage = MonInf.monster_str + 10; //(�ӽ� ���ط�)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\n%s�� %d�� ������!",UsrInf.username, nowturn_plus_attack_damage);
			Sleep(500);
		}
		break;
	case 2: //ATK+
		printf("\n\n%s�� ȥ���� ������ ������!", UsrInf.username);
		MonsterSetCondition();
		if (BattleVal.user_con > BattleVal.mon_con) { //������ CON�� �� ���ٸ�
			nowturn_plus_attack_damage = UsrInf.user_str + 30; //(�ӽ� ���ط�)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\nCounter!! %s�� %d�� ������!", MonInf.monstername, nowturn_plus_attack_damage);
			Sleep(500);
		}
		else { //���Ͱ� CON�� �� ���ٸ�
			nowturn_plus_attack_damage = MonInf.monster_str + 30; //(�ӽ� ���ط�)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\n%s�� %d�� ������!", UsrInf.username, nowturn_plus_attack_damage);
			Sleep(500);
		}
		break;
	case 3: //ATK++
		printf("\n\n%s�� ������ ������ ��������!", UsrInf.username);
		MonsterSetCondition();
		if (BattleVal.user_con > BattleVal.mon_con) { //������ CON�� �� ���ٸ�
			nowturn_plus_attack_damage = UsrInf.user_str + 50; //(�ӽ� ���ط�)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\nCounter!! %s�� %d�� ������!", MonInf.monstername, nowturn_plus_attack_damage);
			Sleep(500);
		}
		else { //���Ͱ� CON�� �� ���ٸ�
			nowturn_plus_attack_damage = MonInf.monster_str + 50; //(�ӽ� ���ط�)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\n%s�� %d�� ������!", UsrInf.username, nowturn_plus_attack_damage);
			Sleep(500);
		}
		break;
	}
}

void UserCounter() {
	int nowturn_plus_attack_damage = 0;

	printf("\n\n%s�� ƴ�� ��� �ִ�!", UsrInf.username);
	if (BattleVal.user_con > BattleVal.mon_con) { //������ CON�� �� ���ٸ�
		switch (BattleVal.mon_nowturn_state) {
		case ATK:
			printf("\n%s�� ����!",MonInf.monstername);
			nowturn_plus_attack_damage = UsrInf.user_str + 10 + (MonInf.monster_str/5); //(�ӽ� ���ط�)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			printf("\nCounter!! %s�� %d�� ������!", MonInf.monstername, nowturn_plus_attack_damage);
			break;
		case ATK_P:
			printf("\n%s�� ȥ���� ������ ������!", MonInf.monstername);
			nowturn_plus_attack_damage = UsrInf.user_str + 30 + (MonInf.monster_str/3); //(�ӽ� ���ط�)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			printf("\nCounter!! %s�� %d�� ������!", MonInf.monstername, nowturn_plus_attack_damage);
			break;
		case ATK_PP:
			printf("\n%s�� ������ ������ ��������!", MonInf.monstername);
			nowturn_plus_attack_damage = UsrInf.user_str + 50 + (MonInf.monster_str); //(�ӽ� ���ط�)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			printf("\nCounter!! %s�� %d�� ������!", MonInf.monstername, nowturn_plus_attack_damage);
			break;
		}
	}
	else { //���Ͱ� CON�� �� ���ٸ�
		switch (BattleVal.mon_nowturn_state) {
		case ATK:
			printf("\n%s�� ����!", MonInf.monstername);
			nowturn_plus_attack_damage = MonInf.monster_str + 10; //(�ӽ� ���ط�)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			printf("\n%s�� %d�� ������!", UsrInf.username, nowturn_plus_attack_damage);
			break;
		case ATK_P:
			printf("\n%s�� ȥ���� ������ ������!", MonInf.monstername);
			nowturn_plus_attack_damage = MonInf.monster_str + 30; //(�ӽ� ���ط�)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			printf("\n%s�� %d�� ������!", UsrInf.username, nowturn_plus_attack_damage);
			break;
		case ATK_PP:
			printf("\n%s�� ������ ������ ��������!", MonInf.monstername);
			nowturn_plus_attack_damage = MonInf.monster_str + 50; //(�ӽ� ���ط�)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			printf("\n%s�� %d�� ������!", UsrInf.username, nowturn_plus_attack_damage);
			break;
		}
	}
}

void MonsterSetCondition() {
	int temp_monster_dex;
	srand((unsigned int)time(NULL)); //���� seed�� �ʱ�ȭ

	BattleVal.mon_con = rand() % 100; //0~99
	temp_monster_dex = MonInf.monster_dex;
	BattleVal.mon_con += temp_monster_dex;
}

void MonsterAct() {
	int monster_idk_random_act;
	srand((unsigned int)time(NULL)); //���� seed�� �ʱ�ȭ

	monster_idk_random_act = rand() % 3;
	switch (monster_idk_random_act) {
	case 0:
		BattleVal.mon_nowturn_state = ATK;
		printf("\n%s�� ������ �ڼ��� ����!", MonInf.monstername);
		break;
	case 1:
		BattleVal.mon_nowturn_state = ATK_P;
		printf("\n%s�� ���� ������ �ִ�!", MonInf.monstername);
		break;
	case 2:
		BattleVal.mon_nowturn_state = ATK_PP;
		printf("\n%s�� ��⸦ ���ϰ� �ִ�!", MonInf.monstername);
		break;

	//���� �߰��ؾ� �� �ٸ� ������)
	//%s�� ȸ���� �ڼ��� ���ϰ� �ִ�.
	//%s�� ����� �ڼ��� ���ϰ� �ִ�.
	
		//���� ���Ͱ� �İ��ϋ��� �ൿ�� �ֱ�
		//(���ʹ� ƴ�� ��� �ִ�!)
	}
}