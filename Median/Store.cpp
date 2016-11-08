#include "Store.hpp"
#include <algorithm>

SortedStore::SortedStore(size_t capacity) : capacity(capacity)
{
}

void SortedStore::Insert(int number)
{
    store[number]++;
}

SortedStoreNode SortedStore::GetNext(SortedStoreNode storeNode)
{
    SortedStoreNode returnNode(storeNode.number, -1);
    auto itr = store.find(storeNode.number);
    if (itr != end(store))
    {
        if (storeNode.pos + 1 < itr->second)
        {
            returnNode.number = storeNode.number;
            returnNode.pos = storeNode.pos + 1;
        }
        else
        {
            ++itr;
            if (itr != end(store))
            {
                returnNode.number = itr->first;
                returnNode.pos = 0;
            }
        }
    }
    return returnNode;
}

SortedStoreNode SortedStore::GetPrev(SortedStoreNode storeNode)
{
    SortedStoreNode returnNode(storeNode.number, -1);
    auto itr = store.find(storeNode.number);
    if (itr != end(store))
    {
        if (storeNode.pos - 1 >= 0)
        {
            returnNode.number = storeNode.number;
            returnNode.pos = storeNode.pos - 1;
        }
        else
        {
            if (itr != begin(store))
            {
                --itr;
                returnNode.number = itr->first;
                returnNode.pos = itr->second - 1;
            }
        }
    }
    return returnNode;
}

SortedStoreNode SortedStore::GetFirst()
{
    auto itr = store.begin();
    if (itr != store.end())
    {
        return SortedStoreNode(itr->first, 0);
    }
    return SortedStoreNode(0, -1);
}

SortedStoreNode SortedStore::GetLast()
{
    auto itr = store.rbegin();
    if (itr != store.rend())
    {
        return SortedStoreNode(itr->first, itr->second - 1);
    }
    return SortedStoreNode(0, -1);
}


void StoreTracker::Insert(int shardId)
{
    tracker.insert(shardId);
}

int StoreTracker::GetFirst()
{
	auto itr = tracker.begin();
	return itr != tracker.end() ? *itr : -1;
}

int StoreTracker::GetNext(int shardId)
{
    auto itr = tracker.find(shardId);
    if (itr != end(tracker))
    {
        ++itr;
    }
    return itr != end(tracker) ? *itr : -1;
}

int StoreTracker::GetPrev(int shardId)
{
    auto itr = tracker.find(shardId);
    if (itr != end(tracker))
    {
        return itr != begin(tracker) ? *(--itr) : -1;
    }
    return -1;
}


StoreMngr::StoreMngr(size_t capacity)
: capacity(capacity), stores(), storeTracker()
{
}

void StoreMngr::Insert(int number)
{
    int id = GetStoreId(number);
    SortedStore *pStore = GetStore(id);
    if (pStore == nullptr)
    {
        pStore = InsertStore(id);
		storeTracker.Insert(id);
    }
    pStore->Insert(number);
}

StoreNode StoreMngr::GetFirst()
{
    int id = storeTracker.GetFirst();
    if (id != -1)
    {
        SortedStore *pStore = GetStore(id);
        SortedStoreNode node = pStore->GetFirst();
        return StoreNode(id, node.number, node.pos);
    }
    return StoreNode(-1, 0, -1);
}

StoreNode StoreMngr::GetNext(StoreNode storeNode)
{
    int id = storeNode.storeId;
    SortedStoreNode node(storeNode.node.number, storeNode.node.pos);
    SortedStore *pStore = GetStore(id);
    if (pStore != nullptr)
    {
        node = pStore->GetNext(node);
        if (node.pos == -1)
        {
            id = storeTracker.GetNext(id);
            pStore = GetStore(id);
            node = pStore->GetFirst();
        }
        return StoreNode(id, node.number, node.pos);
    }
    return StoreNode(-1, 0, -1);
}

StoreNode StoreMngr::GetPrev(StoreNode storeNode)
{
    int id = storeNode.storeId;
    SortedStoreNode node(storeNode.node.number, storeNode.node.pos);
    SortedStore *pStore = GetStore(id);
    if (pStore != nullptr)
    {
        node = pStore->GetPrev(node);
        if (node.pos == -1)
        {
            id = storeTracker.GetPrev(id);
            pStore = GetStore(id);
            node = pStore->GetLast();
        }
        return StoreNode(id, node.number, node.pos);
    }
    return StoreNode(-1, 0, -1);
}

int StoreMngr::GetStoreId(int number)
{
    return number / capacity;
}

SortedStore* StoreMngr::InsertStore(int storeId)
{
    if (stores.size() <= storeId)
        stores.resize(storeId + 1);
    if (stores[storeId] == nullptr)
    {
        stores[storeId] = new SortedStore(capacity);
    }
    return stores[storeId];
}


SortedStore* StoreMngr::GetStore(int storeId)
{
    if (storeId >= stores.size())
        return nullptr;
    return stores[storeId];
}
