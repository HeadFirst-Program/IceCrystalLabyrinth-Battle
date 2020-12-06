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
		UsrInf.user_str = 64;
		UsrInf.user_vit = 30;
		UsrInf.user_dex = 39;
		UsrInf.user_agi = 34;
		UsrInf.user_int = 29;
		printf("쉬움 난이도 설정이 완료되었습니다.");
		break;
	case 2:
		UsrInf.user_hp = 140;
		UsrInf.user_str = 37;
		UsrInf.user_vit = 36;
		UsrInf.user_dex = 31;
		UsrInf.user_agi = 37;
		UsrInf.user_int = 30;
		printf("보통 난이도 설정이 완료되었습니다.");
		break;
	case 3:
		UsrInf.user_hp = 110;
		UsrInf.user_str = 24;
		UsrInf.user_vit = 22;
		UsrInf.user_dex = 20;
		UsrInf.user_agi = 24;
		UsrInf.user_int = 16;
		printf("어려움 난이도 설정이 완료되었습니다.");
		break;
	default:
		UsrInf.user_hp = 140;
		UsrInf.user_str = 37;
		UsrInf.user_vit = 36;
		UsrInf.user_dex = 31;
		UsrInf.user_agi = 37;
		UsrInf.user_int = 30;
		printf("이상한 값이군요.. 그냥 보통난이도로 셋팅할께요.");
		printf("\n보통 난이도 설정이 완료되었습니다.");
		break;
	}
}

void BattleTurnStartMessage(int turn_num) {
	//최초턴일경우 "(적이름)이 나타났다!" "(유저닉) 『간다!』" 출력하기
	//이후 "(숫자)턴 선공" 이나 "(숫자)턴 후공" 을 출력하기.
	printf("\n\n\n");
	if (turn_num == 1) {
		Sleep(1000);
		printf("몬스터 출현!");
		printf("\n%s:『간다!』", UsrInf.username);
	}

	srand((unsigned int)time(NULL)); //랜덤 seed값 초기화
	int turn_first_second_select; //선공,후공 정하기
	turn_first_second_select = rand();

	printf("\n\n-%d턴 ", turn_num);
	if (turn_first_second_select % 2 == 1) {
		BattleVal.turn_go_first = USER;
		BattleVal.turn_go_second = MONSTER;
		printf("선공---");
	}
	else {
		BattleVal.turn_go_first = MONSTER;
		BattleVal.turn_go_second = USER;
		printf("후공---");
	}
}

void SetCondition() {
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

CalcForcedStop:
	BattleVal.user_con = temp_condition; //유저 Con값 최종 저장
	if (BattleVal.user_con < 0) { //만약 유저가 Con값이 마이너스(-)라면 유저는 해당 턴 동안 아무것도 할 수 없다.
		printf("\n%s는 중심을 잃었다!", UsrInf.username);
		printf("\n%s는 자세를 수복하는 중이다.", UsrInf.username);
		return;
	}
	printf("\n지금의 컨디션은 %d이다!", BattleVal.user_con);
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