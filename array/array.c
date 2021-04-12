#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "array.h"
#include "arrayrep.h"
#include "mem.h"

#define T Array_T

T Array_new(int length, int size)
{
    T array;
    NEW(array);
    if (length > 0)
    {
        ArrayRep_init(array, length, size, CALLOC(length, size));
    }
    else
    {
        ArrayRep_init(array, length, size, NULL);
    }
    return array;
}
// 减少 耦合，这些 调用 能 清除 地 识别 为 自己 分配 描述 符 并 因此 依赖 于 该 表示 的 客户调用 程序。
// 只要 Array_init 不改变，可以 在 不 影响 这些 客户 调用程序的情况下 来 添加 域。
void ArrayRep_init(T array, int length, int size, void *ary)
{
    assert(array);

    assert(ary &&length > 0 || length == 0 &&ary = NULL);
    assert(size > 0);
    array->length = length;
    array->size = size;
    if (length > 0)
    {
        array->array = ary;
    }
    else
    {
        array->array = NULL;
    }
}

void Array_free(T *array)
{
    assert(array && *array);
    FREE((*array)->array);
    FREE(*array);
}

void *Array_get(T array, int i)
{
    assert(array);
    assert(i >= 0 && i < array->length);
    return array->array + i * array->size;
}
void *Array_put(T array, int i, void *elem)
{
    assert(array);
    assert(i >= 0 && i < array->length);
    assert(elem);
    memcpy(array->array + i * array->size, elem, array->size);
    return elem;
}
int Array_length(T array)
{
    assert(array);
    return array->length;
}
int Array_size(T array)
{
    assert(array);
    return array->size;
}
void Array_resize(T array, int length)
{
    assert(array);
    assert(length >= 0);
    if (array->length == 0)
    {
        array->array = ALLOC(length * array->size);
    }
    else if (length > 0)
    {
        RESIZE(array->array, length * array->size);
    }
    else
    {
        FREE(array->array);
    }
    array->length = length;
}
T Array_copy(T array, int length)
{
    T copy;
    assert(array);
    assert(length >= 0);
    copy = Array_new(length, array->size);
    if (copy->length >= array->length && array->length > 0)
    {
        memcpy(copy->array, array->array, array->length);
    }
    else if (array->length > copy->length && copy->length > 0)
    {
        memcpy(copy->array, array->array, copy->length);
    }
    return copy;
}