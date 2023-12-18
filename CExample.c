// gcc -otestc CExample.c
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "memory.h"

typedef struct iSortStrategy ISortStrategy;
typedef int* (*SortFunc)(int* arr, int size);

struct iSortStrategy
{
	SortFunc Sort;
};	

static int* SortFuncInstance(int* arr, int size, bool isAcending)
{
	int* result = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		result[i] = arr[i];
	}

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (isAcending) {
				if (result[i] > result[j]) {
					int temp = result[i];
					result[i] = result[j];
					result[j] = temp;
				}
			}
			else {
				if (result[i] < result[j]) {
					int temp = result[i];
					result[i] = result[j];
					result[j] = temp;
				}
			}
		}
	}

	return result;
}

static int* SortAcendingFunc(int* arr, int size)
{
	printf("In SortAcendingFunc\n");
	return SortFuncInstance(arr, size, true);
}

static int* SortDecendingFunc(int* arr, int size)
{
	printf("In SortDecendingFunc\n");
	return SortFuncInstance(arr, size, false);
}

ISortStrategy* CreateAcendingSortStrategy()
{
	ISortStrategy* strategy = (ISortStrategy*)malloc(sizeof(ISortStrategy));
	strategy->Sort = SortAcendingFunc;
	return strategy;
}

ISortStrategy* CreateDecendingSortStrategy()
{
	ISortStrategy* strategy = (ISortStrategy*)malloc(sizeof(ISortStrategy));
	strategy->Sort = SortDecendingFunc;
	return strategy;
}

void DestroySortStrategy(ISortStrategy** strategy)
{
	if (*strategy) {
		free(*strategy);
		*strategy = NULL;
	}
}

const char* Arr2Str(int* arr, int size)
{
	char* result = (char*)malloc(sizeof(char) * 2048);
	memset(result, 0, sizeof(char) * 2048);
	strcat(result, "[");
	char temp[256];
	for (int i = 0; i < size; i++)
	{
		sprintf(temp, "%d", arr[i]);
		strcat(result, temp);
		strcat(result, " ");
	}
	strcat(result, "]");
	return result;
}

void DoSomething(ISortStrategy* strategy, int* arr, int size)
{
	const char* arrStr = Arr2Str(arr, size);
	printf("Do something before sorting, list: %s\n", arrStr);
	free((void*)arrStr);

	int* result = strategy->Sort(arr, size);
	
	arrStr = Arr2Str(result, size);
	printf("Do something after sorting, list: %s\n", arrStr);
	free((void*)arrStr);

	free(result);
}

int main(int argc, const char** argv)
{
	int arr[] = {1, 5, 4, 3, 2, 8};
	ISortStrategy* acendingStrategy = CreateAcendingSortStrategy();
	DoSomething(acendingStrategy, arr, sizeof(arr) / sizeof(int));

	printf("\n=====\n");
	ISortStrategy* decendingStrategy = CreateDecendingSortStrategy();
	DoSomething(decendingStrategy, arr, sizeof(arr) / sizeof(int));

	DestroySortStrategy(&acendingStrategy);
	DestroySortStrategy(&decendingStrategy);
	return EXIT_SUCCESS;
}
