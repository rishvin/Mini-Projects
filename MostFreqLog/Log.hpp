#pragma once

#include "ServiceDef.hpp"

struct LogNode
{
    LogNode(string logMsg, uint64_t timestamp)
	: logMsg(logMsg), timestamp(timestamp) {}
	string logMsg;
	uint64_t timestamp;
};

class LogController
{
public:
    LogController(uint64_t timeFrame = 5);
    void PushLog(string logName, uint64_t timestamp);
    void GetTopLog(string &logName, uint32_t &count, uint64_t from);
private:
    uint64_t timeFrame;
    MapperService<string> logMapper;
    QueueService<LogNode> logQueue;
};

