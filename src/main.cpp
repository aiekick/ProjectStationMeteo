
#include "database.h"
#include "sensor.h"

#include <uv/include/uv11.hpp>

int main(int argc, char** argv)
{
    uv::EventLoop* loop = uv::EventLoop::DefaultLoop();
    uv::SocketAddr addr("0.0.0.0", 12001, uv::SocketAddr::Ipv4);

    uv::TcpServer server(loop);
    server.setMessageCallback([](uv::TcpConnectionPtr ptr, const char* data, ssize_t size)
        {
            printf("Msg Received : %s\n", data);
        });

    server.bindAndListen(addr);
    loop->run();
}
