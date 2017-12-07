#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>

typedef struct _finddata_t  FILE_SEARCH;

typedef struct Word {
	char name[50]; // ���ϸ�
	int num; // ���� �� �ܾ��
}word;

void swap(word * a, word * b); // ����ü ġȯ
int compare_with_size(const void *a, const void  *b); // ����Ʈ 3��


int main() {


	char path[100] = "C:\\Users\\Minsu\\Desktop\\sw2project\\sw"; // �� ��ǻ�Ϳ��� ã�� ���
	int count = 0; // 
	word list[5000]; // ã�� txt���� ��, �ܾ� ���� ���� ��
	char s[20]; // ã������ �ϴ� �ܾ�
	char s2[20];
	char s3[20];
	FILE *fp; // ���� ������
	char *r; // �о���� ������
	char article[300][300] = { 0 , 0 }; //�ű� ����
	char article2[300][300] = { 0, 0 }; // �ι�° ����
	char article3[300][300] = { 0, 0 }; // ����° ����
	char *ptr; // ������ �ʿ��� ������
	int n;
	int temp;
	char * temp_name;
	char end;

	long h_file;
	char search_Path[100];

	FILE_SEARCH file_search; // ����ü

	printf("�ؽ�Ʈ ������ ����ִ� ������ ��θ� �˷��ּ���.\\�� 2���Է����ּž� �մϴ�. \n����: C:\\\\Users\\\\Minsu\\\\Desktop\\\\sw2project\\\\sw\n");
	gets_s(path);

		printf("ã���� �ϴ� �ܾ �Է����ּ���. ");
		gets_s(s);// ã���� �ϴ� �ܾ� �Է�

		for (int i = 0; ; i++) {
			s2[i] = s[i];
			s3[i] = s[i];
			if (s[i] == NULL) {
				break;
			}
		}

		sprintf_s(search_Path, "%s/*.txt", path);
		if ((h_file = _findfirst(search_Path, &file_search)) == -1L) {
			printf("�� ���丮�� ������ �����ϴ�!\n");

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
		} */ // ���� Ȯ��

		for (int i = 0; i < count; i++) {
			list[i].num = 0;

			fp = fopen(list[i].name, "rb");

			if (fp == NULL)
			{
				printf("�ؽ�Ʈ ������ �� �� �����ϴ�.\n");
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
			} //article ����

			/* for (int k = 0; k < j; k++)
			{
			printf("%s", article[k]);
			} */ // �޾ƿ� ���� Ȯ��
			
			for (int k = 0; ; k++) {
				if (s[k] >= 'A' && s[k] <= 'Z') {
					s[k] += 32;
				}
				if (s[k] == NULL) {
					break;
				}
			}//��� �ҹ��ڷ� �ٲٱ�

			for (int k = 0; k < j; k++) {
				do {

					ptr = strstr(article[k], s);
					if (ptr != NULL) {
						*ptr += 1;
						list[i].num += 1;
					}


				} while (ptr != NULL);
			}// ó�� üũ 
			
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

			// ù���ڸ� �빮�ڷ� ��ȯ

			for (int k = 0; k < j; k++) {
				do {

					ptr = strstr(article2[k], s2);
					if (ptr != NULL) {
						*ptr += 1;
						list[i].num += 1;
					}


				} while (ptr != NULL);
			}// ù�빮�� üũ
			
			for (int k = 0; ; k++) {
				if (s3[k] >= 'a' && s3[k] <= 'z') {
					s3[k] -= 32;
				}
				if (s3[k] == NULL) {
					break;
				}
			}//��� �빮�ڷ� �ٲٱ�

			for (int k = 0; k < j; k++) {
				do {

					ptr = strstr(article3[k], s3);
					if (ptr != NULL) {
						*ptr += 1;
						list[i].num += 1;
					}


				} while (ptr != NULL);
			}// ��� �빮�� üũ
			
			

			fclose(fp); // ���� �޾ƿ��� �Ϸ�
						// printf("\n"); �޾ƿ� ���� Ȯ�� �� �ٹٲ�ó����


		}// ���� �޾Ƽ� �˻�

		 /*
		 for (int i = 0; i < count - 1; i++) {
		 for (int j = 0; j < count - 1; j++) {
		 if (list[j].num < list[j + 1].num) {
		 swap(&list[j], &list[j + 1]);
		 }
		 }
		 }
		 //����(�ϴ� ���� ����)
		 */


		qsort(list, count, sizeof(word), compare_with_size);
		//����(����Ʈ)


		printf("\n-----------------------------\n\n"); // ����ϰ� ���̴� �뵵
		for (int i = 0; i < count; i++) {
			if (list[i].num != 0) {
				printf("%d. %s point : %d\n", i + 1, list[i].name, list[i].num);
			}
		} // ���!

		printf("\n-----------------------------\n"); // ����ϰ� ���̴� �뵵

				system("pause");
				return 0;
}

void swap(word *a, word *b) {
	word copy;
	copy = *a;
	*a = *b;
	*b = copy;
}// ���� �Լ�

int compare_with_size(const void *a, const void  *b)
{
	word* ptr_a = (word*)a;
	word* ptr_b = (word*)b;

	if (ptr_a->num < ptr_b->num) return 1;
	else if (ptr_a->num == ptr_b->num) return 0;
	else return -1;
} //����Ʈ 3��
