
#include "database.h"
#include "sensor.h"

#include <uv/include/uv11.hpp>

int main(int argc, char** argv)
{
    uv::EventLoop* loop = uv::EventLoop::DefaultLoop();
    uv::TcpServer::SetBufferMode(uv::GlobalConfig::BufferMode::CycleBuffer);
    uv::SocketAddr addr("127.0.0.1", 12001);
    uv::TcpServer server(loop);

    server.setMessageCallback([](uv::TcpConnectionPtr ptr, const char* data, ssize_t size)
        {
            printf("Msg Received : %s\n", data);
        });

    loop->run();
}