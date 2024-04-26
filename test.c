#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
typedef int STDataType;
typedef struct Stack
{
    STDataType* a;       // ָ��̬�����ָ�룬���ڴ洢ջ�е�Ԫ��
    int top;             // ջ����������ָ��ջ��Ԫ��
    int capacity;        // ջ����������ʾջ����������ɵ����Ԫ������
} Stack;

void StackInit(Stack* ps)
{
    assert(ps);
    ps->a = (STDataType*)malloc(sizeof(STDataType) * 4);
    ps->capacity = 0;
    // ������Ҫע����ǵ� top=0 ʱָ�����ջ��Ԫ�ص���һ��λ��
    //                   top=-1 ʱָ�����ջ��Ԫ��
    // ����Ҳ�������Ϊ˳����� size ��Ч���ݵ���˼
    ps->top = -1;

}

void StackDestroy(Stack* ps)
{
    assert(ps);  // ȷ�������ջָ�벻Ϊ�գ���ֹδ������Ϊ
    free(ps->a);  // �ͷ�ջʹ�õĶ�̬�����ڴ�
    ps->a = NULL;  // ��ָ��̬�����ָ����ΪNULL����������ָ�루dangling pointer��
    ps->top = -1;  // ��ջ����������Ϊ0
    ps->capacity = 0;  // ��ջ����������Ϊ0

    // ע�⣺�˴�û���ͷ�ջ�ṹ������ڴ棬���ͷ������ڲ��Ķ�̬����
}

void STPush(Stack* ps, STDataType x)
{
	// ��ʱ��Ҫ��֤�����ջ�����ǿ�
	assert(ps);

	// ����
	// �ж��Ƿ���Ҫ����
	if (ps->top == ps->capacity)
	{
		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		STDataType* temp = (STDataType*)realloc(ps->a, sizeof(STDataType) * newcapacity);
		// ��ֹ���ص��ǿ�ָ��
		if (temp == NULL)
		{
			perror("realloc fail!");
			exit(-1);
		}
		ps->a = temp;
		ps->capacity = newcapacity;
	}
	// ����β������
	ps->a[ps->top] = x;
	ps->top++;
}

void StackPop(Stack* ps)
{
	assert(ps);
	assert(!StackEmpty(ps));//���ջ�Ƿ�Ϊ��

	ps->top--;//ջ������
}

STDataType StackTop(Stack* ps)
{
	assert(ps);                     // ȷ�������ջָ��ǿ�
	assert(!StackEmpty(ps));        // ȷ��ջ��Ϊ�գ���ֹ���ʿ�ջ

	return ps->a[ps->top - 1];     // ����ջ��Ԫ��
	//ps->a[ps->top - 1]���ⲿ�ִ������ջ�е����� a������ȡջ��Ԫ�ء�
	//����ʹ�� ps->top - 1 ����Ϊ top ͨ����ʾ��һ���ɲ���Ԫ�ص�λ�ã�
	//����ջ����ʵ��Ԫ��λ�� top - 1 ��λ�á�
}

bool StackEmpty(Stack* ps)
{
	assert(ps);      // ���Լ�飬ȷ�������ջָ��ǿ�
	return ps->top == 0; // ����ջ�Ƿ�Ϊ�յ��жϽ��
}

int StackSize(Stack* ps)
{
	assert(ps);

	return ps->top;//top��ֵ����ջ����ЧԪ�صĸ���
}



