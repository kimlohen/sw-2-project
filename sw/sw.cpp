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
int compare_with_size(const void *a, const void  *b); // 퀵소트 3항


int main() {


	char path[100] = "C:\\Users\\Minsu\\Desktop\\sw2project\\sw"; // 내 컴퓨터에서 찾을 경로
	int count = 0; // 
	word list[5000]; // 찾을 txt파일 수, 단어 수를 넣을 곳
	char s[20]; // 찾으려고 하는 단어
	char s2[20];
	char s3[20];
	FILE *fp; // 파일 포인터
	char *r; // 읽어오는 포인터
	char article[300][300] = { 0 , 0 }; //옮길 공간
	char article2[300][300] = { 0, 0 }; // 두번째 공간
	char article3[300][300] = { 0, 0 }; // 세번째 공간
	char *ptr; // 읽을때 필요한 포인터
	int n;
	int temp;
	char * temp_name;
	char end;

	long h_file;
	char search_Path[100];

	FILE_SEARCH file_search; // 구조체

	printf("텍스트 파일이 들어있는 폴더의 경로를 알려주세요.\\는 2번입력해주셔야 합니다. \n예시: C:\\\\Users\\\\Minsu\\\\Desktop\\\\sw2project\\\\sw\n");
	gets_s(path);

		printf("찾고자 하는 단어를 입력해주세요. ");
		gets_s(s);// 찾고자 하는 단어 입력

		for (int i = 0; ; i++) {
			s2[i] = s[i];
			s3[i] = s[i];
			if (s[i] == NULL) {
				break;
			}
		}

		sprintf_s(search_Path, "%s/*.txt", path);
		if ((h_file = _findfirst(search_Path, &file_search)) == -1L) {
			printf("이 디렉토리에 파일이 없습니다!\n");

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
			list[i].num = 0;

			fp = fopen(list[i].name, "rb");

			if (fp == NULL)
			{
				printf("텍스트 파일을 열 수 없습니다.\n");
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

			for (int k = 0; k < j; k++) {
				for (int w = 0; ; w++) {
					article2[k][w] = article[k][w];
					article3[k][w] = article[k][w];
						if (article[k][w] == NULL) {
							break;
						}
				}
			} //article 복사

			/* for (int k = 0; k < j; k++)
			{
			printf("%s", article[k]);
			} */ // 받아온 파일 확인
			
			for (int k = 0; ; k++) {
				if (s[k] >= 'A' && s[k] <= 'Z') {
					s[k] += 32;
				}
				if (s[k] == NULL) {
					break;
				}
			}//모두 소문자로 바꾸기

			for (int k = 0; k < j; k++) {
				do {

					ptr = strstr(article[k], s);
					if (ptr != NULL) {
						*ptr += 1;
						list[i].num += 1;
					}


				} while (ptr != NULL);
			}// 처음 체크 
			
			if (s2[0] >= 'a' && s2[0] <= 'z') {
				s2[0] -= 32;
			}
			for (int k = 1; ; k++) {
				if (s2[k] >= 'A' && s2[k] <= 'Z') {
					s2[k] += 32;
				}
				if (s2[k] == NULL) {
					break;
				}
			}

			// 첫문자만 대문자로 변환

			for (int k = 0; k < j; k++) {
				do {

					ptr = strstr(article2[k], s2);
					if (ptr != NULL) {
						*ptr += 1;
						list[i].num += 1;
					}


				} while (ptr != NULL);
			}// 첫대문자 체크
			
			for (int k = 0; ; k++) {
				if (s3[k] >= 'a' && s3[k] <= 'z') {
					s3[k] -= 32;
				}
				if (s3[k] == NULL) {
					break;
				}
			}//모두 대문자로 바꾸기

			for (int k = 0; k < j; k++) {
				do {

					ptr = strstr(article3[k], s3);
					if (ptr != NULL) {
						*ptr += 1;
						list[i].num += 1;
					}


				} while (ptr != NULL);
			}// 모든 대문자 체크
			
			

			fclose(fp); // 파일 받아오기 완료
						// printf("\n"); 받아온 파일 확인 시 줄바꿈처리용


		}// 파일 받아서 검색

		 /*
		 for (int i = 0; i < count - 1; i++) {
		 for (int j = 0; j < count - 1; j++) {
		 if (list[j].num < list[j + 1].num) {
		 swap(&list[j], &list[j + 1]);
		 }
		 }
		 }
		 //정렬(일단 버블 소팅)
		 */


		qsort(list, count, sizeof(word), compare_with_size);
		//정렬(퀵소트)


		printf("\n-----------------------------\n\n"); // 깔끔하게 보이는 용도
		for (int i = 0; i < count; i++) {
			if (list[i].num != 0) {
				printf("%d. %s point : %d\n", i + 1, list[i].name, list[i].num);
			}
		} // 출력!

		printf("\n-----------------------------\n"); // 깔끔하게 보이는 용도

				system("pause");
				return 0;
}

void swap(word *a, word *b) {
	word copy;
	copy = *a;
	*a = *b;
	*b = copy;
}// 스왑 함수

int compare_with_size(const void *a, const void  *b)
{
	word* ptr_a = (word*)a;
	word* ptr_b = (word*)b;

	if (ptr_a->num < ptr_b->num) return 1;
	else if (ptr_a->num == ptr_b->num) return 0;
	else return -1;
} //퀵소트 3항
