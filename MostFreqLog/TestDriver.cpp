#include "Log.hpp"

int main()
{
    LogController logController(600);
    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());

    logController.PushLog("Mesos timeout", clock());
    logController.PushLog("Mesos timeout", clock());
    logController.PushLog("Mesos timeout", clock());
    logController.PushLog("Mesos timeout", clock());
    logController.PushLog("Mesos timeout", clock());

    sleep(5);

    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());
    logController.PushLog("Spark timeout", clock());


    logController.PushLog("Mesos timeout", clock());
    logController.PushLog("Mesos timeout", clock());

    logController.PushLog("Zookeeper timeout", clock());
    logController.PushLog("Zookeeper timeout", clock());
    logController.PushLog("Zookeeper timeout", clock());
    logController.PushLog("Zookeeper timeout", clock());
    logController.PushLog("Zookeeper timeout", clock());
    logController.PushLog("Zookeeper timeout", clock());
    logController.PushLog("Zookeeper timeout", clock());

    logController.PushLog("Cassandra timeout", clock());
    logController.PushLog("Cassandra timeout", clock());
    logController.PushLog("Cassandra timeout", clock());

    string logName;
    uint32_t count = 0;
    logController.GetTopLog(logName, count, clock());
        cout << "Top Log = " << logName.c_str() << " " << count << endl;
    return 0;
}
