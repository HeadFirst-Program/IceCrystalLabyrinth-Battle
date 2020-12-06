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
		UsrInf.user_str = 64;
		UsrInf.user_vit = 30;
		UsrInf.user_dex = 39;
		UsrInf.user_agi = 34;
		UsrInf.user_int = 29;
		printf("���� ���̵� ������ �Ϸ�Ǿ����ϴ�.");
		break;
	case 2:
		UsrInf.user_hp = 140;
		UsrInf.user_str = 37;
		UsrInf.user_vit = 36;
		UsrInf.user_dex = 31;
		UsrInf.user_agi = 37;
		UsrInf.user_int = 30;
		printf("���� ���̵� ������ �Ϸ�Ǿ����ϴ�.");
		break;
	case 3:
		UsrInf.user_hp = 110;
		UsrInf.user_str = 24;
		UsrInf.user_vit = 22;
		UsrInf.user_dex = 20;
		UsrInf.user_agi = 24;
		UsrInf.user_int = 16;
		printf("����� ���̵� ������ �Ϸ�Ǿ����ϴ�.");
		break;
	default:
		UsrInf.user_hp = 140;
		UsrInf.user_str = 37;
		UsrInf.user_vit = 36;
		UsrInf.user_dex = 31;
		UsrInf.user_agi = 37;
		UsrInf.user_int = 30;
		printf("�̻��� ���̱���.. �׳� ���볭�̵��� �����Ҳ���.");
		printf("\n���� ���̵� ������ �Ϸ�Ǿ����ϴ�.");
		break;
	}
}

void BattleTurnStartMessage(int turn_num) {
	//�������ϰ�� "(���̸�)�� ��Ÿ����!" "(������) ������!��" ����ϱ�
	//���� "(����)�� ����" �̳� "(����)�� �İ�" �� ����ϱ�.
	printf("\n\n\n");
	if (turn_num == 1) {
		Sleep(1000);
		printf("���� ����!");
		printf("\n%s:������!��", UsrInf.username);
	}

	srand((unsigned int)time(NULL)); //���� seed�� �ʱ�ȭ
	int turn_first_second_select; //����,�İ� ���ϱ�
	turn_first_second_select = rand();

	printf("\n\n-%d�� ", turn_num);
	if (turn_first_second_select % 2 == 1) {
		BattleVal.turn_go_first = USER;
		BattleVal.turn_go_second = MONSTER;
		printf("����---");
	}
	else {
		BattleVal.turn_go_first = MONSTER;
		BattleVal.turn_go_second = USER;
		printf("�İ�---");
	}
}

void SetCondition() {
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

CalcForcedStop:
	BattleVal.user_con = temp_condition; //���� Con�� ���� ����
	if (BattleVal.user_con < 0) { //���� ������ Con���� ���̳ʽ�(-)��� ������ �ش� �� ���� �ƹ��͵� �� �� ����.
		printf("\n%s�� �߽��� �Ҿ���!", UsrInf.username);
		printf("\n%s�� �ڼ��� �����ϴ� ���̴�.", UsrInf.username);
		return;
	}
	printf("\n������ ������� %d�̴�!", BattleVal.user_con);
}

void UserAct() {
	if (BattleVal.user_con < 0) {
		return;
	}

	printf("\n\n");
	if (BattleVal.turn_go_first == USER) {
		printf("Attack");
	}
	else {
		printf("Counter");
	}
	printf("\nMagic");
	printf("\nGuard");
	printf("\nAvoid");

	

}