#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// node 구조체 선언
typedef struct {
    char word[32];
    int cnt;
} node;

int n_word = 0;
node node_arr[1000];

// 알파벳이면 1, 아니면 0
int is_alphabet(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

// 유효한 단어면 1, 아니면 0
int is_word(char* str) {
    int len = strlen(str);
    int i;

    // 첫 문자가 알파벳이 아니면 제거
    if (!is_alphabet(str[0])) {
        for (i = 0; i < len; i++)
            str[i] = str[i + 1];
        len--;
    }

    // 알파벳이 아닌 문자가 중간에 있으면 배제
    for (i = 0; i < len; i++) {
        if (!is_alphabet(str[i]) && i != len - 1)
            return 0;
    }

    // 마지막 문자가 알파벳이 아니면 제거
    if (len > 0 && !is_alphabet(str[len - 1]))
        str[len - 1] = '\0';

    if (strlen(str) == 0)
        return 0;

    return 1;
}

void process_insert(node tnode) {
    int i, j;

    // 배열이 비어있으면 바로 삽입
    if (n_word == 0) {
        node_arr[n_word++] = tnode;
        return;
    }

    // 이미 배열에 있다면 cnt 증가 후 재삽입
    for (i = 0; i < n_word; i++) {
        if (strcmp(tnode.word, node_arr[i].word) == 0) {
            // cnt 증가
            tnode.cnt = node_arr[i].cnt + 1;
            // i번째 노드 제거
            for (j = i; j < n_word - 1; j++)
                node_arr[j] = node_arr[j + 1];
            // n_word 감소
            n_word--;
            break;
        }
    }

    // cnt 기준으로 정렬된 위치에 삽입
    // 삽입 위치 찾기
    for (i = 0; i < n_word; i++) {
        if (tnode.cnt > node_arr[i].cnt)
            break;
    }
    // 뒤로 밀기
    for (j = n_word; j > i; j--)
        node_arr[j] = node_arr[j - 1];
    // 삽입 및 n_word 증가
    node_arr[i] = tnode;
    n_word++;
}

void main() {
    FILE* fp = fopen("test.txt", "r");
    if (fp == NULL) {
        perror("Failed to open the file.");
        exit(0);
    }

    char word[256];
    int i;

    // 배열에 단어 삽입
    while (fscanf(fp, "%s", word) != EOF) {
        // 배제되는 단어면 건너뛰기
        if (!is_word(word))
            continue;

        printf("%s ", word);

        // node 생성 후 삽입
        node tnode;
        strcpy(tnode.word, word);
        tnode.cnt = 1;
        process_insert(tnode);
    }
    printf("\n\n");

    // 상위 10개 출력
    int top = (n_word < 10) ? n_word : 10;
    for (i = 0; i < top; i++)
        printf("[%d] %s\n", node_arr[i].cnt, node_arr[i].word);

    fclose(fp);
}