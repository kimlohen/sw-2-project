#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>

typedef struct _finddata_t  FILE_SEARCH;

typedef struct Word {
	char name[50]; // 파일명
	int num; // 파일 내 단어수
}word;

void swap(word * a, word * b); // 구조체 치환


int main() {


	char path[100] = "C:\\Users\\Minsu\\Desktop\\sw2project\\sw"; // 찾을 경로
	int count = 0; // 
	word list[100]; // 찾을 txt파일 수, 단어 수를 넣을 곳
	char s[20]; // 찾으려고 하는 단어
	FILE *fp; // 파일 포인터
	char *r; // 읽어오는 포인터
	char article[100][100] = { 0 , 0 }; //옮길 공간
	char *ptr; // 읽을때 필요한 포인터
	int n;
	int temp;
	char * temp_name;

	long h_file;
	char search_Path[100];

	FILE_SEARCH file_search; // 구조체

	printf("찾고자 하는 단어를 입력해주세요. ");
	gets_s(s);// 찾고자 하는 단어 입력

	sprintf_s(search_Path, "%s/*.txt", path);
	if ((h_file = _findfirst(search_Path, &file_search)) == -1L) {
		printf("No files in current directory!\n");

	}
	else {

		do {
			strcpy_s(list[count].name, file_search.name);
			count++;

		} while (_findnext(h_file, &file_search) == 0);

		_findclose(h_file);
	}

	/* for (int i = 0; i < count; i++) {
		printf("%s\n", list[i].name);
	} */ // 복사 확인

	for (int i = 0; i < count; i++) {
		n = 0;

		fp = fopen(list[i].name, "rb");

		if (fp == NULL)
		{
			printf("Cannot open the textfile.\n");
			return 0;
		}
		int j = 0;

		while (1)
		{
			r = fgets(article[j], sizeof(article[j]), fp);
			if (r == NULL)
				break;
			j++;
		}

		/* for (int k = 0; k < j; k++)
		{
			printf("%s", article[k]); 
		} */ // 받아온 파일 확인

		for (int k = 0; k < j; k++) {
			do {

				ptr = strstr(article[k], s);
				if (ptr != NULL) {
					*ptr += 1;
					n++;
				}
				
			
			} while (ptr != NULL);
		}

		fclose(fp); // 파일 받아오기 완료
		// printf("\n"); 받아온 파일 확인 시 줄바꿈처리용

		list[i].num = n;

	}// 파일 받아서 검색


	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1; j++) {
		if (list[j].num < list[j + 1].num) {
			swap(&list[j], &list[j + 1]);
		}
		}
	}
	//정렬(일단 버블 소팅)

	printf("\n-----------------------------\n"); // 깔끔하게 보이는 용도
	for (int i = 0; i < count; i++) {
		printf("%d. %s point : %d\n", i+1, list[i].name, list[i].num);
	} // 출력!

	printf("\n-----------------------------\n"); // 깔끔하게 보이는 용도

	return 0;
}

void swap(word *a, word *b) {
	word copy;
	copy = *a;
	*a = *b;
	*b = copy;
}// 스왑 함수
