#include <hrlib.h>
#include <LoaderTest.h>
#include <iostream>

void LogTest(int n)
{
    // hrcpp::hrlogger::Logger::Info("%d", n);
    HR_INFO("%d", n)
    for (int i = 0; i < 1000; ++i)
    {
        int n = i * i;
    }
    for (int i = 0; i < 100; ++i)
    {
        // hrcpp::hrlogger::Logger::Warn("hey %d %d", n ,i);
        HR_WARN("hey %d %d", n, i)
    }
}

int main()
{
    hrcpp::hrlogger::Logger::EnableFileOutput();
    hrcpp::HotReloader reloader;

    reloader.addSourceDirectory("src", true);
    reloader.addSourceDirectory("F://VICTORIA ORGANIZATION//Reloader//HRTest//src");

    foo();
    while (true)
    {
        reloader.update();
    }
    // std::thread threads[10];
    // for (int i = 0; i < 10; ++i)
    //{
    //     threads[i] = std::thread(LogTest, i);
    // }
    // for (int i = 0; i < 10; ++i)
    //{
    //     threads[i].join();
    // }

    return 0;
}
