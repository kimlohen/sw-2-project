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
int compare_with_size(const void *a, const void  *b); // ����Ʈ

int main() {


	char path[100] = "C:\\Users\\Minsu\\Desktop\\sw2project\\sw"; // ã�� ���
	int count = 0; // 
	word list[5000]; // ã�� txt���� ��, �ܾ� ���� ���� ��
	char s[20]; // ã������ �ϴ� �ܾ�
	FILE *fp; // ���� ������
	char *r; // �о���� ������
	char article[500][500] = { 0 , 0 }; //�ű� ����
	char article2[500][500]; //ù���� �빮�� �˻�
	char article3[500][500]; //������ �빮�� �˻�
	char *ptr; // ������ �ʿ��� ������
	int n;
	int temp;
	char * temp_name;

	long h_file;
	char search_Path[100];

	FILE_SEARCH file_search; // ����ü

	printf("�ؽ�Ʈ ������ ����ִ� ������ ��θ� �˷��ּ���.\\�� 2���Է����ּž� �մϴ�. \n����: C:\\\\Users\\\\Minsu\\\\Desktop\\\\sw2project\\\\sw\n");
	gets(path);

	printf("ã���� �ϴ� �ܾ �ҹ��ڷ� �Է����ּ���. ");
	gets(s);// ã���� �ϴ� �ܾ� �Է�

	sprintf_s(search_Path, "%s/*.txt", path);
	if ((h_file = _findfirst(search_Path, &file_search)) == -1L) {
		printf("No files in current directory!\n");

	}
	else {

		do {
			strcpy(list[count].name, file_search.name);
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
			printf("������ �� �� �����ϴ�.\n");
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

		/* for (int k = 0; k < j; k++){
		printf("%s", article[k]);
		} */ // �޾ƿ� ���� Ȯ��

		for (int k = 0; k < j; k++) {
			strcpy(article2[k], article[k]);
			strcp(article3[k], article2[k]);
		}

		for (int k = 0; k < j; k++) {
			do {

				ptr = strstr(article[k], s);
				if (ptr != NULL) {
					*ptr += 1;
					n++;
				}


			} while (ptr != NULL);
		} // ���ڿ� �˻�(�ҹ���)

		if ('a' <= s[0] && s[0] <= 'z') {
			s[0] -= 32;
		}//ù ���� �빮�� ����

		for (int k = 0; k < j; k++) {
			do {

				ptr = strstr(article2[k], s);
				if (ptr != NULL) {
					*ptr += 1;
					n++;
				}


			} while (ptr != NULL);
		} // ���ڿ� �˻�(�빮��)

		for (int k = 0; ; k++) {
			if ('a' <= s[k] && s[k] <= 'z') {
				s[k] -= 32;
			}
			if (s[k] == NULL) {
				break;
			}
		}//��� ���� �빮�� ����

		for (int k = 0; k < j; k++) {
			do {

				ptr = strstr(article3[k], s);
				if (ptr != NULL) {
					*ptr += 1;
					n++;
				}


			} while (ptr != NULL);
		} // ���ڿ� �˻�(��� �빮��)


		fclose(fp); // ���� �޾ƿ��� �Ϸ�
					// printf("\n"); �޾ƿ� ���� Ȯ�� �� �ٹٲ�ó����

		list[i].num = n;

	}// ���� �޾Ƽ� �˻�

	 /*
	 for (int i = 0; i < count - 1; i++) {
	 for (int j = 0; j < count - 1; j++) {
	 if (list[j].num < list[j + 1].num) {
	 swap(&list[j], &list[j + 1]);
	 }
	 }
	 } // �����Ʈ
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
} //����Ʈ