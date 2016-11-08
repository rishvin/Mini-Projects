#include <iostream>
#include <assert.h>
#include <unordered_map>
#include <queue>
#include <time.h>
#include <unistd.h>
#include "ServiceInc.hpp"

using namespace std;

template<typename T>
QueueServiceNode<T>::QueueServiceNode(T data) :data(data), pNext(nullptr)
{
}

template<typename T>
T& QueueServiceNode<T>::GetData() const
{
    return data;
}

template<typename T>
QueueService<T>::QueueService() : pFront(nullptr), pTail(nullptr)
{
}

template<typename T>
void QueueService<T>::Enque(T data)
{
    QueueServiceNode<T> *pNewNode = nullptr;
    try
    {
        pNewNode = new QueueServiceNode<T>(data);
    }
    catch (...)
    {
        cout << "Failed to allocate memory for new Log queue node" << endl;
        exit(0);
    }
    if (pTail == nullptr)
        pFront = pNewNode;
    else
        pTail->pNext = pNewNode;
    pTail = pNewNode;
}

template<typename T>
bool QueueService<T>::IsEmpty() const
{
    return pFront == nullptr;
}

template<typename T>
T QueueService<T>::Peek() const
{
    return pFront->data;
}

template<typename T>
void QueueService<T>::Deque()
{
    QueueServiceNode<T> *pFrontNode = pFront;
    pFront = pFront->pNext;
    if (pFront == nullptr)
    {
        pTail = nullptr;
    }
    delete(pFrontNode);
}


template<typename T>
MapperServiceNode<T>::MapperServiceNode(T key, int pos)
    :key(key), pos(pos), count(1)
{
}


template<typename T>
MapperService<T>::MapperService(size_t capacity)
    : heapBuffer(capacity, nullptr), heapMapper(), size(0), capacity(capacity)
{
}

template<typename T>
void MapperService<T>::Insert(T key)
{
    if (size == capacity)
    {
        cout << "Log heap capacity reached" << endl;
        return;
    }
    MapperServiceNode<T> *pNode = heapMapper[key];
    if (pNode != nullptr)
    {
        heapBuffer[pNode->pos]->count++;
        Heapify(pNode);
    }
    else
    {
        MapperServiceNode<T> *pNewNode = new MapperServiceNode<T>(key, size);
        heapBuffer[pNewNode->pos] = pNewNode;
        heapMapper[key] = pNewNode;
        Heapify(pNewNode);
        ++size;
    }
}

template<typename T>
void MapperService<T>::Delete(T key)
{
    MapperServiceNode<T> *pNode = heapMapper[key];
    if (pNode == nullptr)
        return;
    pNode->count--;
    DecrHeap(pNode);
    if (pNode->count == 0)
    {
        int pos = pNode->pos;
        heapBuffer[pos] = nullptr;
        heapBuffer[pos] = heapBuffer[size - 1];
        heapBuffer[size - 1] = nullptr;
        Heapify(heapBuffer[pos]);
        heapMapper.erase(pNode->key);
        delete(pNode);
        --size;
    }
}

template<typename T>
bool MapperService<T>::IsEmpty() const
{
    return size == 0;
}

template<typename T>
void MapperService<T>::GetMaxLog(T &key, uint32_t &count)
{
    key = heapBuffer[0]->key;
    count = heapBuffer[0]->count;
}

template<typename T>
void MapperService<T>::Dump()
{
    if (size == 0)
    return;
    queue<MapperServiceNode<T>*> q;
    q.push(heapBuffer[0]);
    while (!q.empty())
    {
        MapperServiceNode<T> *pNode = q.front();
        q.pop();
        cout << pNode->key.c_str() << " " << pNode->count << " ";
        MapperServiceNode<T> *pLeftChild = GetChild(pNode, true);
        MapperServiceNode<T> *pRightChild = GetChild(pNode, false);
        if (pLeftChild)
            q.push(pLeftChild);
        if (pRightChild)
            q.push(pRightChild);
    }
}

template<typename T>
MapperServiceNode<T>* MapperService<T>::GetParent(MapperServiceNode<T> *pNode) const
{
    return heapBuffer[(pNode->pos - 1) / 2];
}

template<typename T>
MapperServiceNode<T>* MapperService<T>::GetChild(MapperServiceNode<T> *pNode,
		                                         bool isLeftChild) const
{
    int pos = pNode->pos * 2 + 1;
    if (!isLeftChild)
    {
        ++pos;
    }
    return pos < (int)capacity ? heapBuffer[pos] : nullptr;
}

template<typename T>
void MapperService<T>::Heapify(MapperServiceNode<T> *pNode)
{
    if (pNode == nullptr)
        return;
    MapperServiceNode<T> *pParent = GetParent(pNode);
    if (pParent != nullptr)
    {
        if (pParent->count < pNode->count)
        {
            swap(pParent->pos, pNode->pos);
            swap(heapBuffer[pParent->pos], heapBuffer[pNode->pos]);
            Heapify(pParent);
        }
    }
}

template<typename T>
void MapperService<T>::DecrHeap(MapperServiceNode<T> *pNode)
{
    if (pNode == nullptr)
        return;
    MapperServiceNode<T> *pLeftChild = GetChild(pNode, true);
    MapperServiceNode<T> *pRightChild = GetChild(pNode, false);

    MapperServiceNode<T> *pMax = pNode;
    if (pLeftChild && pLeftChild->count > pNode->count)
    {
        pMax = pLeftChild;
    }
    if (pRightChild && pRightChild->count > pNode->count)
    {
        pMax = pRightChild;
    }
    if (pMax != pNode)
    {
        swap(pMax->pos, pNode->pos);
        swap(heapBuffer[pMax->pos], heapBuffer[pNode->pos]);
        return DecrHeap(pMax);
    }
}
