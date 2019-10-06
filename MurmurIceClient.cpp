#include <Ice/Ice.h>
#include <Murmur.h>
#include <stdexcept>

using namespace std;
using namespace Murmur;

int main(int argc, char* argv[]) {
    try {
        Ice::CommunicatorHolder ich(argc, argv);
        auto base = ich->stringToProxy("Meta:tcp -h 127.0.0.1 -p 6502");
        auto meta = Ice::checkedCast<MetaPrx>(base);
        if (!meta) {
            throw std::runtime_error("Invalid proxy");
        }
       
        ServerList bootedServers = meta->getBootedServers();
        auto server = bootedServers.front();

        UserMap userMap = server->getUsers();
        for(map<int, User>::const_iterator it = userMap.begin();
            it != userMap.end(); ++it) {
            std::cout << it->second.name << endl;
        } 

    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
