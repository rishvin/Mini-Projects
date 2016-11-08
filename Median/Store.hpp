#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class StoreMngr;

class SortedStoreNode
{
public:
    SortedStoreNode(int number, int pos)
    : number(number), pos(pos)
    {
    }
    int number;
    int pos;
};

class SortedStore
{
public:
    SortedStore(size_t capacity);
    void Insert(int number);
    SortedStoreNode GetNext(SortedStoreNode storeNode);
    SortedStoreNode GetPrev(SortedStoreNode storeNode);
    SortedStoreNode GetFirst();
    SortedStoreNode GetLast();
private:
    size_t capacity;
    map<int, int> store;
};

class StoreTracker
{
public:
    void Insert(int shardId);
	int GetFirst();
    int GetNext(int shardId);
    int GetPrev(int shardId);
private:
    set<int> tracker;
};

class StoreNode
{
public:
    StoreNode(int storeId, int number, int pos)
        : storeId(storeId), node(number, pos)
    {
    }
    int GetData() const { return node.number; }
private:
    int storeId;
    SortedStoreNode node;
    friend class StoreMngr;
};

class StoreMngr
{
public:
    StoreMngr(size_t capacity);
    void Insert(int number);
    StoreNode GetFirst();
    StoreNode GetNext(StoreNode storeNode);
    StoreNode GetPrev(StoreNode storeNode);
private:
    SortedStore* InsertStore(int storeId);
    SortedStore* GetStore(int storeId);
    int GetStoreId(int number);
    size_t capacity;
    vector<SortedStore*> stores;
	StoreTracker storeTracker;
};

