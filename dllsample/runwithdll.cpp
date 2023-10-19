#include "pipe.h"
#include <Windows.h>
#include <detours.h>
#include <stdio.h>
#include <tchar.h>

#include <chrono>
#include <mutex>
#include <thread>
using namespace ::std::literals;


#define DLL_NAME "Z:\\Projects2022\\detours-cmake\\build\\DEBUG\\dllsample.dll"
// #define DLL_NAME "Z:\\Projects2022\\detours-cmake\\build\\DEBUG\\traceapi.dll"
 // #define DLL_NAME NULL
//-------------------------------------------------------------------------
std::vector<std::string> cmds = {
    "test1",
    "test2",
    "test3",
    "test4",
    "quit"
};

int main()
{
    Pipe pipe;
    pipe.Open("dummy", DLL_NAME);

    std::jthread pipe_sender([&pipe](std::stop_token stoken) {
        char buf[16384] = { 0 };
        int i = 0;
        while (!stoken.stop_requested()) {
            if (i < cmds.size()) {
                sprintf(buf, "%s\n", cmds[i].c_str());
                auto sz = strlen(buf);
                pipe.Write(buf, sz);

                ++i;
                std::this_thread::sleep_for(0.1s);
            }
        }
    });

    std::jthread pipe_receiver([&pipe](std::stop_token stoken) {
        char buf[16384];
        while (!stoken.stop_requested()) {
            memset(buf, 0, 16384);
            size_t res = 0;
            do {
                res = pipe.Read(buf, 16384);
                buf[res] = 0;
                std::cout << buf;
            } while (res > 0);
        }
    });
    std::this_thread::sleep_for(500s);
    std::cout << "------" << std::endl;
    pipe_sender.request_stop();
    pipe_receiver.request_stop();

    std::cout << "end" << std::endl;
    pipe.Close();
    return 0;
}