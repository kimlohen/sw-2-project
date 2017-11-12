#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>

typedef struct _finddata_t  FILE_SEARCH;

typedef struct Word {
	char name[50]; // 파일명
	int count; // 단어수
}word;

void GetfileList(char* path);

int main() {
	

	char path[100] = "C:\\Users\\Minsu\\Desktop\\sw2project"; // 찾을 경로
	GetfileList(path);



	return 0;
}

void GetfileList(char* path) {
	long h_file;
	char search_Path[100];

	FILE_SEARCH file_search; // 구조체

	sprintf_s(search_Path, "%s/*.txt", path);
	if ((h_file = _findfirst(search_Path, &file_search)) == -1L) {
		printf("No files in current directory!\n");
		
	}
	else {

		do {
			printf("%s\n", file_search.name);

		} while (_findnext(h_file, &file_search) == 0);

		_findclose(h_file);
	}
}

//http://sks3297.tistory.com/category/Language/C 파일 리스트 가져오기 참조