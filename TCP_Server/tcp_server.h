#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QTcpServer>
#include <QTcpSocket>

#include <QMap>
#include <QObject>

#include <array>
#include <set>

#include "../DataProcessingManager/DataProcessingManager.h"

#define TCP_SERVER_DEFAULT_PORT (5300)

#ifndef MAC_ADDRESS_LENGTH
#define MAC_ADDRESS_LENGTH (6)
#endif // MAC_ADDRESS_LENGTH

class TCPServer;
struct binaryPacketWithTcpServer_t
{
    std::vector<uint8_t> *bin;
    TCPServer *server;
};

typedef void (*PacketHandlerFunc)(void *inputData);

class TCPServer : public QObject
{
    Q_OBJECT

public:
    TCPServer();
    ~TCPServer();

    // Client MAC functions
    void addClientMAC(const std::vector<uint8_t> &client);
    void addClientMAC(std::vector<uint8_t> &&client);
    void addClientMAC(const std::array<uint8_t, MAC_ADDRESS_LENGTH> &client);
    void addClientMAC(std::array<uint8_t, MAC_ADDRESS_LENGTH> &&client);

    void removeClientMAC(const std::vector<uint8_t> &client);
    void removeClientMAC(const std::array<uint8_t, MAC_ADDRESS_LENGTH> &client);

    std::set<std::array<uint8_t, MAC_ADDRESS_LENGTH>>& getClientMACs();

    static std::string convertMACtoString(std::array<uint8_t, MAC_ADDRESS_LENGTH> mac);

private:
    static void bootstrapHandler(void *);

    QTcpServer *m_tcpServer = nullptr;
    QMap<int, QTcpSocket*> m_clientSockets;

    std::set<std::array<uint8_t, MAC_ADDRESS_LENGTH>> m_clientAddress;

    // TODO: change this
    DataProcessingManager<std::string, PacketHandlerFunc> m_handlers;

public slots:
    int startServer();
    int stopServer();

    int processNewConnection();
    int comunicateWithRoot();
};

#endif // TCP_SERVER_H
