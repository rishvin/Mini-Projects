#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T>
class QueueService;

template<typename T>
class MapperService;

template<typename T>
class QueueServiceNode
{
public:
	QueueServiceNode(T data);
    T& GetData() const;
private:
    T data;
    QueueServiceNode<T> *pNext;
    friend class QueueService<T>;
};

template<typename T>
class QueueService
{
public:
	QueueService();
    void Enque(T data);
    void Deque();
    T Peek() const;
    bool IsEmpty() const;
private:
    QueueServiceNode<T> *pFront;
    QueueServiceNode<T> *pTail;
};

template<typename T>
class MapperServiceNode
{
public:
	MapperServiceNode(T key, int pos);
private:
    T key;
    int pos;
    uint32_t count;
    friend class MapperService<T>;
};

template<typename T>
class MapperService
{
public:
	MapperService(size_t capacity);
    void Insert(T key);
    void Delete(T key);
    bool IsEmpty() const;
    void GetMaxLog(T &key, uint32_t &count);
    void Dump();
private:
    MapperServiceNode<T>* GetParent(MapperServiceNode<T> *pNode) const;
    MapperServiceNode<T>* GetChild(MapperServiceNode<T> *pNode, bool isLeftChild) const;
    void Heapify(MapperServiceNode<T> *pNode);
    void DecrHeap(MapperServiceNode<T> *pNode);
    vector<MapperServiceNode<T>*> heapBuffer;
    unordered_map<string, MapperServiceNode<T>*> heapMapper;
    size_t size;
    size_t capacity;
};

