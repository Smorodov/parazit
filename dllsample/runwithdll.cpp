#include "pipe.h"
#include <Windows.h>
#include <detours.h>
#include <stdio.h>
#include <tchar.h>

#include <chrono>
#include <mutex>
#include <thread>
#include <filesystem>
using namespace ::std::literals;


//#define DLL_NAME "dllsample.dll"
// to view logs run syslog before running this project
#define DLL_NAME "traceapi.dll"
#define CLIENT_APP_NAME "dummy.exe"
// 
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

  std::filesystem::path dll_path = DLL_NAME;
  std::string DllAbsolutePath = std::filesystem::absolute(dll_path).string();
  std::cout << "Injecting " << DllAbsolutePath << std::endl;

  std::filesystem::path client_app_path = CLIENT_APP_NAME;
  std::string  ClientAppAbsolutePath = std::filesystem::absolute(client_app_path).string();
  std::cout << "Into " << ClientAppAbsolutePath << std::endl;

  //CLIENT_APP_NAME 
    pipe.Open(ClientAppAbsolutePath.c_str(), DllAbsolutePath.c_str() );

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
    // let thteads to work
    std::this_thread::sleep_for(5s);
    std::cout << "------" << std::endl;
    pipe_sender.request_stop();
    pipe_receiver.request_stop();

    std::cout << "end" << std::endl;
    pipe.Close();
    return 0;
}