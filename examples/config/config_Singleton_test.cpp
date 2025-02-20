#include <iostream>
#include <thread>

#include <tools/base/Singleton.h>
#include <tools/base/CurrentThread.h>
#include <tools/log/log.h>
#include <tools/config/ConfigFile.h>


void threadFunc(){
    ConfigFile & cf = Singleton<ConfigFile>::instance();
    std::cout << "ConfigFile instance: " << &cf << ", CurrentThread: " << CurrentThread::get_tid() << std::endl;

    std::cout << cf.get<std::string>("StringTest") << ", CurrentThread: " << CurrentThread::get_tid() << std::endl;

    int int_val = cf.get<int>("IntTest");
    std::cout << int_val << ", CurrentThread: " << CurrentThread::get_tid() << std::endl;

    double double_val = cf.get<double>("DoubleTest");
    std::cout << double_val << ", CurrentThread: " << CurrentThread::get_tid() << std::endl;
}

int main(){
    ConfigFile & cf = Singleton<ConfigFile>::instance();

    const char * configFileName = "config_test.conf";
    if(cf.load(configFileName)){
        LOG_FATAL("Failed to load config file: %s", configFileName);
    }

    std::thread t(threadFunc);
    t.join();

    std::cout << "ConfigFile instance: " << &cf << ", CurrentThread: " << CurrentThread::get_tid() << std::endl;

    std::cout << cf.get<std::string>("StringTest") << ", CurrentThread: " << CurrentThread::get_tid() << std::endl;

    int int_val = cf.get<int>("IntTest");
    std::cout << int_val << ", CurrentThread: " << CurrentThread::get_tid() << std::endl;

    double double_val = cf.get<double>("DoubleTest");
    std::cout << double_val << ", CurrentThread: " << CurrentThread::get_tid() << std::endl;

    return 0;
}