#include "Log.hpp"

LogController::LogController(uint64_t timeFrame)
    :timeFrame(timeFrame), logMapper(50), logQueue()
{
}
void LogController::PushLog(string logMsg, uint64_t timestamp)
{
    logQueue.Enque(LogNode(logMsg, timestamp));
    logMapper.Insert(logMsg);
}
void LogController::GetTopLog(string &logName, uint32_t &count, uint64_t from = clock())
{
    while (!logQueue.IsEmpty())
    {
        LogNode node = logQueue.Peek();
        if ((from - node.timestamp) <= timeFrame)
            break;
        logQueue.Deque();
        cout << "Deleting " << node.logMsg << endl;
        logMapper.Delete(node.logMsg);
    }
    if (!logMapper.IsEmpty())
        logMapper.GetMaxLog(logName, count);
}
