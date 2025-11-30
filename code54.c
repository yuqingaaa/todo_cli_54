#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TODO 100
#define MAX_LEN 200

// 待办事项结构体
typedef struct {
	char content[MAX_LEN];
	int completed; // 0=未完成, 1=已完成
} Todo;

Todo todos[MAX_TODO];
int todo_count = 0;

// 加载待办（从文件）
void load_todos() {
	FILE *fp = fopen("todos.txt", "r");
	if (!fp) return;
	while (fscanf(fp, "%d %[^\n]", &todos[todo_count].completed, todos[todo_count].content) != EOF) {
		todo_count++;
	}
	fclose(fp);
}

// 保存待办（到文件）
void save_todos() {
	FILE *fp = fopen("todos.txt", "w");
	for (int i = 0; i < todo_count; i++) {
		fprintf(fp, "%d %s\n", todos[i].completed, todos[i].content);
	}
	fclose(fp);
}

// 添加待办
void add_todo() {
	if (todo_count >= MAX_TODO) {
		printf("待办数量已达上限！\n");
		return;
	}
	printf("输入待办内容：");
	getchar(); // 清除缓冲区
	fgets(todos[todo_count].content, MAX_LEN, stdin);
	todos[todo_count].content[strcspn(todos[todo_count].content, "\n")] = '\0'; // 去掉换行符
	todos[todo_count].completed = 0;
	todo_count++;
	save_todos();
	printf("添加成功！\n");
}

// 查看待办
void list_todos() {
	if (todo_count == 0) {
		printf("暂无待办事项！\n");
		return;
	}
	printf("===== 待办列表 =====\n");
	for (int i = 0; i < todo_count; i++) {
		printf("%d. [%s] %s\n", i+1, todos[i].completed ? "√" : " ", todos[i].content);
	}
}

// 删除待办
void delete_todo() {
	list_todos();
	if (todo_count == 0) return;
	int idx;
	printf("输入要删除的序号：");
	scanf("%d", &idx);
	if (idx < 1 || idx > todo_count) {
		printf("序号无效！\n");
		return;
	}
	for (int i = idx-1; i < todo_count-1; i++) {
		todos[i] = todos[i+1];
	}
	todo_count--;
	save_todos();
	printf("删除成功！\n");
}

void toggle_todo() {
	list_todos();
	if (todo_count == 0) return;
	int idx;
	printf("输入要标记的序号：");
	scanf("%d", &idx);
	if (idx < 1 || idx > todo_count) {
		printf("序号无效！\n");
		return;
	}
	todos[idx-1].completed = !todos[idx-1].completed;
	save_todos();
	printf("标记成功！\n");
}
int main() {
	load_todos();
	int choice;
	while (1) {
		printf("\n===== 待办工具 =====\n");
		printf("1. 添加待办\n2. 查看待办\n3. 删除待办\n4. 退出\n");
		printf("选择操作：");
		scanf("%d", &choice);
		switch (choice) {
			case 1: add_todo(); break;
			case 2: list_todos(); break;
			case 3: delete_todo(); break;
			printf("4. 标记完成/未完成\n");
			case 4: toggle_todo(); break;
			default: printf("无效选择！\n");
		}
	}
	return 0;
}

