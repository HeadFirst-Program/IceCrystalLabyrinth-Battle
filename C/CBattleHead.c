#define _CRT_SECURE_NO_WARNINGS
#include "CBattleHead.h"

//CUI 관련
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

	printf("[[빙정의 미궁 전투시스템 클론 프로젝트 by VDoring]]");
	printf("\n당신의 이름은? : ");
	scanf("%s", UsrInf.username);

	printf("\n난이도를 선택하세요 >");
	printf("\n[1]쉬움\t[2]보통\t[3]어려움");
	printf("\n숫자입력 : ");
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

		strcpy(MonInf.monstername, "말랑한 스펀지");
		MonInf.monster_hp = 100;
		MonInf.monster_max_hp = 100;
		MonInf.monster_str = 30;
		MonInf.monster_vit = 60;
		MonInf.monster_dex = 30;
		MonInf.monster_agi = 35;
		MonInf.monster_int = 30;

		printf("쉬움 난이도 설정이 완료되었습니다.");
		break;
	case 2:
		UsrInf.user_hp = 140;
		UsrInf.user_max_hp = 140;
		UsrInf.user_str = 37;
		UsrInf.user_vit = 36;
		UsrInf.user_dex = 31; //테스트값
		UsrInf.user_agi = 37;
		UsrInf.user_int = 30;
		BattleVal.user_attack_count = 0;
		BattleVal.user_guard_count = 0;
		BattleVal.user_avoid_count = 0;
		BattleVal.user_magic_count = 0;
		BattleVal.user_estrus_count = 0;

		strcpy(MonInf.monstername, "보통 스펀지");
		MonInf.monster_hp = 150;
		MonInf.monster_max_hp = 150;
		MonInf.monster_str = 40;
		MonInf.monster_vit = 40;
		MonInf.monster_dex = 35;
		MonInf.monster_agi = 35;
		MonInf.monster_int = 35;

		printf("보통 난이도 설정이 완료되었습니다.");
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

		strcpy(MonInf.monstername, "딱딱한 스펀지");
		MonInf.monster_hp = 200;
		MonInf.monster_max_hp = 200;
		MonInf.monster_str = 50;
		MonInf.monster_vit = 50;
		MonInf.monster_dex = 50;
		MonInf.monster_agi = 50;
		MonInf.monster_int = 50;

		printf("어려움 난이도 설정이 완료되었습니다.");
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

		strcpy(MonInf.monstername, "보통 스펀지");
		MonInf.monster_hp = 150;
		MonInf.monster_max_hp = 150;
		MonInf.monster_str = 40;
		MonInf.monster_vit = 40;
		MonInf.monster_dex = 35;
		MonInf.monster_agi = 35;
		MonInf.monster_int = 35;

		printf("이상한 이름이군요.. 그냥 보통난이도로 셋팅할께요.");
		printf("\n보통 난이도 설정이 완료되었습니다.");
		break;
	}
}

void BattleTurnStartMessage(int turn_num) {
	printf("\n\n\n");
	if (turn_num == 1) {
		Sleep(1000);
		printf("%s 출현!", MonInf.monstername);
		printf("\n%s:『간다!』", UsrInf.username);
	}

	srand((unsigned int)time(NULL)); //랜덤 seed값 초기화
	int turn_first_second_select; //선공,후공 정하기
	turn_first_second_select = rand();

	printf("\n\n-%d턴 ", turn_num);
	if (turn_first_second_select % 2 == 1) {
		BattleVal.turn_go_first = USER;
		BattleVal.turn_go_second = MONSTER;
		printf("선공---------------");
	}
	else {
		BattleVal.turn_go_first = MONSTER;
		BattleVal.turn_go_second = USER;
		printf("후공---------------");
	}
}

void UserSetCondition() {
#define MAX_RAND_NUM 20
	srand((unsigned int)time(NULL)); //랜덤 seed값 초기화
	CursorView(0);

	int condition_rand_arr[MAX_RAND_NUM]; //랜덤으로 정해지는 Con값 저장
	int visible_i = 0; //화면에 출력하기 위해 사용되는 변수 i

	for (int i = 0; i < MAX_RAND_NUM; i++) { //랜덤 수 정하기(범위:0~99)
		condition_rand_arr[i] = rand() % 100;
	}
	
	int key_input; //키 입력 값 저장
	int is_double_backspace = 0; //(CUI) 이미 백스페이스를 2번 하였는지 여부
	int temp_condition = 0; //유저가 랜덤선택한 초기 Con값
	printf("\n※결정 키를 눌러주세요.");
	printf("\nCON : ");
	while (1) {
		if (condition_rand_arr[visible_i] < 10) { //만약 랜덤숫자가 1자리수인경우 CUI가 꼬이지 않게 별도 설정
			printf("  ");
			printf("\b\b");
			is_double_backspace = 1;
		}

		printf("%d", condition_rand_arr[visible_i]); //랜덤숫자 출력
		Sleep(60);

		if (is_double_backspace == 1) { //1자리수인 랜덤숫자에 의해 이미 CUI조정이 되었을 경우
			printf("\b");
			is_double_backspace = 0;
		}
		else { //랜덤숫자가 2자리일경우
			printf("\b\b");
		}

		//key_input = _getch(); // 입력값을 읽을때 까지 대기했다가 읽으면 다음 문장 실행
		if (_kbhit()) {
			key_input = _getch();
			if((key_input == KEY_Z) || (key_input == KEY_ENTER)) {
				temp_condition = condition_rand_arr[visible_i]; //유저가 선택한 Con값 저장
				break;
			}
		}

		if (visible_i >= MAX_RAND_NUM - 1) { //condition_rand_arr배열을 끝까지 표시했을경우 처음으로 돌아감
			visible_i = 0;
		}
		visible_i++;
	}

	switch (BattleVal.user_attack_count) { //유저의 Attack 휫수에 따른 Con값 +
	case 9:
		temp_condition += 9;
		//printf(GREEN"+9"); 이 에니매이션 표시 부분은 추후 Attack 시스템이 다 만들어지면 넣기!
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

	switch (BattleVal.user_guard_count) { //유저의 Guard 휫수에 따른 Con값 +
	case 9:
		temp_condition += 9;
		//printf(GREEN"+9"); 이 에니매이션 표시 부분은 추후 Defence 시스템이 다 만들어지면 넣기!
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

	switch (BattleVal.user_avoid_count) { //유저의 Avoid 휫수에 따른 Con값 -
	case 3:
		temp_condition -= 3;
		//printf(RED"-3"); 이 에니매이션 표시 부분은 추후 시스템이 다 만들어지면 넣기!
	case 2:
		temp_condition -= 2;
	case 1:
		temp_condition -= 1;
	}
	if (temp_condition < 0) { //만약 Con값 계산도중 Con값이 마이너스(-)라면
		goto CalcForcedStop;
	}

	switch (BattleVal.user_magic_count) { //유저의 Magic 휫수에 따른 Con값 -
	case 6:
		temp_condition -= 6;
		//printf(RED"-6"); 이 에니매이션 표시 부분은 추후 시스템이 다 만들어지면 넣기!
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
	if (temp_condition < 0) { //만약 Con값 계산도중 Con값이 마이너스(-)라면
		goto CalcForcedStop;
	}

	switch (BattleVal.user_estrus_count) { //유저의 ♡ 개수에 따른 Con값 -
	case 3:
		temp_condition -= 19;
		//printf(RED"-19"); 이 에니매이션 표시 부분은 추후 시스템이 다 만들어지면 넣기!
	case 2:
		temp_condition -= 13;
	case 1:
		temp_condition -= 7;
	}
	if (temp_condition < 0) { //만약 Con값 계산도중 Con값이 마이너스(-)라면
		goto CalcForcedStop;
	}

	temp_condition += UsrInf.user_dex; //유저의 DEX 스탯의 수만큼 Con값 +
	//printf(GREEN"+DEX"); 이 에니매이션 표시 부분은 추후 시스템이 다 만들어지면 넣기!

CalcForcedStop:
	BattleVal.user_con = temp_condition; //유저 Con값 최종 저장
	if (BattleVal.user_con < 0) { //만약 유저가 Con값이 마이너스(-)라면 유저는 해당 턴 동안 아무것도 할 수 없다.
		printf("\n%s는 중심을 잃었다!", UsrInf.username);
		printf("\n%s는 몸의 자세를 고쳐 세우고 있다.", UsrInf.username);
		return;
	}
	printf("\n지금의 컨디션은 %d이다!", BattleVal.user_con);
}

void UserAct() {
	if (BattleVal.user_con < 0) { //유저의 Con이 -라 행동불능이라면
		return;
	}

	int user_act; //해당턴에 유저가 선택한 행동
	int key_input1; //유저 키 입력 1
	int key_input2; //유저 키 입력 2
	int key_input2_continue; //유저 키 유지 확인

	printf("\n\n");
	if (BattleVal.turn_go_first == USER) { //유저가 선공이면
		printf("         Attack");
	}
	else {
		printf("         Counter");
	}
	//printf("                      ESC: item(미구현)");
	printf("\n\n           ↑");
	printf("\nAvoid   ←    →   Magic");
	printf("\n           ↓");
	printf("\n\n          Guard");
	
	printf("\n\nMy HP: "); printf("%d/%d  ", UsrInf.user_hp, UsrInf.user_max_hp);
	for (int i = 0; i < (int)UsrInf.user_hp / 10; i++) {
		printf("■");
	}
	printf("\nEnemy: "); printf("%d/%d  ", MonInf.monster_hp, MonInf.monster_max_hp);
	for (int i = 0; i < (int)MonInf.monster_hp / 10; i++) {
		printf("■");
	}
	
	BattleVal.user_nowturn_attack_count = 0; //새로운 턴이 왔으므로 초기화
	BattleVal.user_nowturn_guard_count = 0; //새로운 턴이 왔으므로 초기화
	BattleVal.user_nowturn_avoid_count = 0; //새로운 턴이 왔으므로 초기화
	BattleVal.user_nowturn_magic_count = 0; //새로운 턴이 왔으므로 초기화
	if (BattleVal.turn_go_first == MONSTER) { //몬스터가 선공이면 몬스터가 먼저 행동을 취함
		printf("\n");
		MonsterSetCondition();
		MonsterAct();
	}
	printf("\n\n");
	key_input1 = _getch();
	if (key_input1 == KEY_ESC) {
		//printf("아이템칸으로");
	}
	if (_kbhit()) { //방향키를 눌렀을 경우에 한정하여 작동한다
		key_input2 = _getch();
		if (key_input2 == KEY_UP) {
			//printf("위로");
			//추후 공격에 따른 CON값 보너스 시스템 만들기.(단, 3턴 이상 지나가면 보너스가 없어져야함) //////
			if (BattleVal.turn_go_first == USER) { //유저가 선공이면
				BattleVal.user_nowturn_attack_count++;
				printf("CON+ ATK"); //공격 1단계
				Sleep(850);
				key_input2_continue = 0;
				if (_kbhit()) {
					key_input2_continue = _getch(); //사용자가 키를 계속 누르고 있는지 확인
					key_input2_continue = _getch(); //사용자가 키를 계속 누르고 있는지 확인
				}
				if (key_input2_continue == KEY_UP) {
					BattleVal.user_nowturn_attack_count++;
					printf("\nCON+ ATK+"); //공격 2단계
					Sleep(850);
					key_input2_continue = 0;
					if (_kbhit()) {
						key_input2_continue = _getch(); //사용자가 키를 계속 누르고 있는지 확인
						key_input2_continue = _getch(); //사용자가 키를 계속 누르고 있는지 확인
					}
					if (key_input2_continue == KEY_UP) {
						BattleVal.user_nowturn_attack_count++;
						printf("\nCON+ ATK++"); //공격 3단계
						Sleep(500);
					}
				}
				UserAttack(BattleVal.user_nowturn_attack_count); //유저 공격 데미지 연산
			}
			else { //유저가 후공이면
				BattleVal.user_nowturn_attack_count++;
				//MonsterAct(); //몬스터가 선공이므로 몬스터가 먼저 행동 
				UserCounter(); //유저 카운터 데미지 연산
			}
		}
		else if (key_input2 == KEY_DOWN) {
			//printf("아래로");
		}
		else if (key_input2 == KEY_LEFT) {
			//printf("왼쪽으로");
		}
		else if (key_input2 == KEY_RIGHT) {
			//printf("오른쪽으로");
		}
	}
}

void UserAttack(int user_atkcnt) {
	int nowturn_plus_attack_damage = 0;

	switch (user_atkcnt) {
	case 1: //ATK
		printf("%s는 공격의 자세에 들어갔다!",UsrInf.username);
		MonsterSetCondition();
		//MonsterAct(); 추후 이 함수에 몬스터가 후공일떄의 시스템을 넣기
		printf("\n\n%s의 공격!", UsrInf.username);
		if (BattleVal.user_con > BattleVal.mon_con) { //유저가 CON이 더 높다면
			nowturn_plus_attack_damage = UsrInf.user_str + 10; //(임시 피해량)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\nCounter!! %s에 %d의 데미지!", MonInf.monstername, nowturn_plus_attack_damage);
			Sleep(500);
		}
		else { //몬스터가 CON이 더 높다면
			nowturn_plus_attack_damage = MonInf.monster_str + 10; //(임시 피해량)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\n%s에 %d의 데미지!",UsrInf.username, nowturn_plus_attack_damage);
			Sleep(500);
		}
		break;
	case 2: //ATK+
		printf("\n\n%s는 혼신의 공격을 밝힌다!", UsrInf.username);
		MonsterSetCondition();
		if (BattleVal.user_con > BattleVal.mon_con) { //유저가 CON이 더 높다면
			nowturn_plus_attack_damage = UsrInf.user_str + 30; //(임시 피해량)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\nCounter!! %s에 %d의 데미지!", MonInf.monstername, nowturn_plus_attack_damage);
			Sleep(500);
		}
		else { //몬스터가 CON이 더 높다면
			nowturn_plus_attack_damage = MonInf.monster_str + 30; //(임시 피해량)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\n%s에 %d의 데미지!", UsrInf.username, nowturn_plus_attack_damage);
			Sleep(500);
		}
		break;
	case 3: //ATK++
		printf("\n\n%s는 전력의 공격을 내지른다!", UsrInf.username);
		MonsterSetCondition();
		if (BattleVal.user_con > BattleVal.mon_con) { //유저가 CON이 더 높다면
			nowturn_plus_attack_damage = UsrInf.user_str + 50; //(임시 피해량)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\nCounter!! %s에 %d의 데미지!", MonInf.monstername, nowturn_plus_attack_damage);
			Sleep(500);
		}
		else { //몬스터가 CON이 더 높다면
			nowturn_plus_attack_damage = MonInf.monster_str + 50; //(임시 피해량)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			Sleep(500);
			printf("\n%s에 %d의 데미지!", UsrInf.username, nowturn_plus_attack_damage);
			Sleep(500);
		}
		break;
	}
}

void UserCounter() {
	int nowturn_plus_attack_damage = 0;

	printf("\n\n%s는 틈을 듣고 있다!", UsrInf.username);
	if (BattleVal.user_con > BattleVal.mon_con) { //유저가 CON이 더 높다면
		switch (BattleVal.mon_nowturn_state) {
		case ATK:
			printf("\n%s의 공격!",MonInf.monstername);
			nowturn_plus_attack_damage = UsrInf.user_str + 10 + (MonInf.monster_str/5); //(임시 피해량)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			printf("\nCounter!! %s에 %d의 데미지!", MonInf.monstername, nowturn_plus_attack_damage);
			break;
		case ATK_P:
			printf("\n%s는 혼신의 공격을 밝힌다!", MonInf.monstername);
			nowturn_plus_attack_damage = UsrInf.user_str + 30 + (MonInf.monster_str/3); //(임시 피해량)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			printf("\nCounter!! %s에 %d의 데미지!", MonInf.monstername, nowturn_plus_attack_damage);
			break;
		case ATK_PP:
			printf("\n%s는 전력의 공격을 내지른다!", MonInf.monstername);
			nowturn_plus_attack_damage = UsrInf.user_str + 50 + (MonInf.monster_str); //(임시 피해량)
			MonInf.monster_hp -= nowturn_plus_attack_damage;
			printf("\nCounter!! %s에 %d의 데미지!", MonInf.monstername, nowturn_plus_attack_damage);
			break;
		}
	}
	else { //몬스터가 CON이 더 높다면
		switch (BattleVal.mon_nowturn_state) {
		case ATK:
			printf("\n%s의 공격!", MonInf.monstername);
			nowturn_plus_attack_damage = MonInf.monster_str + 10; //(임시 피해량)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			printf("\n%s에 %d의 데미지!", UsrInf.username, nowturn_plus_attack_damage);
			break;
		case ATK_P:
			printf("\n%s는 혼신의 공격을 밝힌다!", MonInf.monstername);
			nowturn_plus_attack_damage = MonInf.monster_str + 30; //(임시 피해량)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			printf("\n%s에 %d의 데미지!", UsrInf.username, nowturn_plus_attack_damage);
			break;
		case ATK_PP:
			printf("\n%s는 전력의 공격을 내지른다!", MonInf.monstername);
			nowturn_plus_attack_damage = MonInf.monster_str + 50; //(임시 피해량)
			UsrInf.user_hp -= nowturn_plus_attack_damage;
			printf("\n%s에 %d의 데미지!", UsrInf.username, nowturn_plus_attack_damage);
			break;
		}
	}
}

void MonsterSetCondition() {
	int temp_monster_dex;
	srand((unsigned int)time(NULL)); //랜덤 seed값 초기화

	BattleVal.mon_con = rand() % 100; //0~99
	temp_monster_dex = MonInf.monster_dex;
	BattleVal.mon_con += temp_monster_dex;
}

void MonsterAct() {
	int monster_idk_random_act;
	srand((unsigned int)time(NULL)); //랜덤 seed값 초기화

	monster_idk_random_act = rand() % 3;
	switch (monster_idk_random_act) {
	case 0:
		BattleVal.mon_nowturn_state = ATK;
		printf("\n%s는 공격의 자세에 들어갔다!", MonInf.monstername);
		break;
	case 1:
		BattleVal.mon_nowturn_state = ATK_P;
		printf("\n%s는 힘을 모으고 있다!", MonInf.monstername);
		break;
	case 2:
		BattleVal.mon_nowturn_state = ATK_PP;
		printf("\n%s는 살기를 발하고 있다!", MonInf.monstername);
		break;

	//추후 추가해야 할 다른 선택지)
	//%s는 회피의 자세를 취하고 있다.
	//%s는 방어의 자세를 취하고 있다.
	
		//추후 몬스터가 후공일떄의 행동도 넣기
		//(몬스터는 틈을 듣고 있다!)
	}
}