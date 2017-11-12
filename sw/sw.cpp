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


int main() {


	char path[100] = "C:\\Users\\Minsu\\Desktop\\sw2project\\sw"; // ã�� ���
	int count = 0; // 
	word list[100]; // ã�� txt���� ��, �ܾ� ���� ���� ��
	char s[20]; // ã������ �ϴ� �ܾ�
	FILE *fp; // ���� ������
	char *r; // �о���� ������
	char article[100][100] = { 0 , 0 }; //�ű� ����
	char *ptr; // ������ �ʿ��� ������
	int n;
	int temp;
	char * temp_name;

	long h_file;
	char search_Path[100];

	FILE_SEARCH file_search; // ����ü

	printf("ã���� �ϴ� �ܾ �Է����ּ���. ");
	gets_s(s);// ã���� �ϴ� �ܾ� �Է�

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
	} */ // ���� Ȯ��

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
		} */ // �޾ƿ� ���� Ȯ��

		for (int k = 0; k < j; k++) {
			do {

				ptr = strstr(article[k], s);
				if (ptr != NULL) {
					*ptr += 1;
					n++;
				}
				
			
			} while (ptr != NULL);
		}

		fclose(fp); // ���� �޾ƿ��� �Ϸ�
		// printf("\n"); �޾ƿ� ���� Ȯ�� �� �ٹٲ�ó����

		list[i].num = n;

	}// ���� �޾Ƽ� �˻�


	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1; j++) {
		if (list[j].num < list[j + 1].num) {
			swap(&list[j], &list[j + 1]);
		}
		}
	}
	//����(�ϴ� ���� ����)

	printf("\n-----------------------------\n"); // ����ϰ� ���̴� �뵵
	for (int i = 0; i < count; i++) {
		printf("%d. %s point : %d\n", i+1, list[i].name, list[i].num);
	} // ���!

	printf("\n-----------------------------\n"); // ����ϰ� ���̴� �뵵

	return 0;
}

void swap(word *a, word *b) {
	word copy;
	copy = *a;
	*a = *b;
	*b = copy;
}// ���� �Լ�
