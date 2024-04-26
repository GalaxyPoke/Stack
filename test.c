#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
typedef int STDataType;
typedef struct Stack
{
    STDataType* a;       // 指向动态数组的指针，用于存储栈中的元素
    int top;             // 栈顶的索引，指向栈顶元素
    int capacity;        // 栈的容量，表示栈数组可以容纳的最大元素数量
} Stack;

void StackInit(Stack* ps)
{
    assert(ps);
    ps->a = (STDataType*)malloc(sizeof(STDataType) * 4);
    ps->capacity = 0;
    // 这里需要注意的是当 top=0 时指向的是栈顶元素的下一个位置
    //                   top=-1 时指向的是栈顶元素
    // 这里也可以理解为顺序表中 size 有效数据的意思
    ps->top = -1;

}

void StackDestroy(Stack* ps)
{
    assert(ps);  // 确保传入的栈指针不为空，防止未定义行为
    free(ps->a);  // 释放栈使用的动态数组内存
    ps->a = NULL;  // 将指向动态数组的指针设为NULL，避免悬挂指针（dangling pointer）
    ps->top = -1;  // 将栈顶索引重置为0
    ps->capacity = 0;  // 将栈的容量设置为0

    // 注意：此处没有释放栈结构本身的内存，仅释放了其内部的动态数组
}

void STPush(Stack* ps, STDataType x)
{
	// 此时需要保证传入的栈，不是空
	assert(ps);

	// 扩容
	// 判断是否需要扩容
	if (ps->top == ps->capacity)
	{
		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		STDataType* temp = (STDataType*)realloc(ps->a, sizeof(STDataType) * newcapacity);
		// 防止返回的是空指针
		if (temp == NULL)
		{
			perror("realloc fail!");
			exit(-1);
		}
		ps->a = temp;
		ps->capacity = newcapacity;
	}
	// 进行尾插数据
	ps->a[ps->top] = x;
	ps->top++;
}

void StackPop(Stack* ps)
{
	assert(ps);
	assert(!StackEmpty(ps));//检测栈是否为空

	ps->top--;//栈顶下移
}

STDataType StackTop(Stack* ps)
{
	assert(ps);                     // 确保传入的栈指针非空
	assert(!StackEmpty(ps));        // 确保栈不为空，防止访问空栈

	return ps->a[ps->top - 1];     // 返回栈顶元素
	//ps->a[ps->top - 1]：这部分代码访问栈中的数组 a，并获取栈顶元素。
	//这里使用 ps->top - 1 是因为 top 通常表示下一个可插入元素的位置，
	//所以栈顶的实际元素位于 top - 1 的位置。
}

bool StackEmpty(Stack* ps)
{
	assert(ps);      // 断言检查，确保传入的栈指针非空
	return ps->top == 0; // 返回栈是否为空的判断结果
}

int StackSize(Stack* ps)
{
	assert(ps);

	return ps->top;//top的值便是栈中有效元素的个数
}



