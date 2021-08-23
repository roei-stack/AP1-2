
#include "../Sockets/Socket.h"

using namespace std;

int main() {
    Socket client(UDP, CLIENT, "127.0.0.1", 12349);
    client.send("HELLO!");
    cout << "SERVER REPLIED: " << client.receive() << endl;
    client.close();
    return 0;
}
