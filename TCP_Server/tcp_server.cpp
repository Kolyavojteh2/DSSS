#include "tcp_server.h"
#include "../DSS_Protocol/DSS_Protocol.h"
#include "../DSS_Protocol/packets/BootstrapPacket.h"

#include <sstream>
#include <iomanip>

#include <QObject>
#include <QDateTime>

TCPServer::TCPServer() : QObject()
{
    m_handlers.add(typeid(BootstrapPacket_t).name(), bootstrapHandler);
}

TCPServer::~TCPServer()
{
    if (m_tcpServer)
        delete m_tcpServer;

    for (auto &it : m_clientSockets)
        it->close();
}

int TCPServer::startServer()
{
    if (m_tcpServer)
        return -1;

    m_tcpServer = new QTcpServer;
    QObject::connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(processNewConnection()));

    // Listen new connections
    int ret = m_tcpServer->listen(QHostAddress::AnyIPv4, TCP_SERVER_DEFAULT_PORT);
    if (ret == false)
    {
        // TODO: add error handling
        return -1;
    }

    return 0;
}

int TCPServer::stopServer()
{
    if (m_tcpServer == nullptr)
        return -1;

    // Close connections
    for (auto &it : m_clientSockets)
        it->close();
    m_clientSockets.clear();

    // Close server
    m_tcpServer->close();

    // Delete and clear pointer
    delete m_tcpServer;
    m_tcpServer = nullptr;

    return 0;
}

int TCPServer::processNewConnection()
{
    if (m_tcpServer == nullptr)
    {
        std::cerr << "The Server has been stoped. A connection doesn't established with client." << std::endl;
        return -1;
    }

    QTcpSocket* clientSocket = m_tcpServer->nextPendingConnection();
    int id = clientSocket->socketDescriptor();
    m_clientSockets[id] = clientSocket;

    QObject::connect(m_clientSockets[id], SIGNAL(readyRead()), this, SLOT(comunicateWithRoot()));

    QHostAddress clientAddress = clientSocket->peerAddress();
    quint16 clientPort = clientSocket->peerPort();

    std::cout << "The connection with " << clientAddress.toString().toStdString() << ":" << clientPort
              << " has been established." << std::endl;

    return -1;
}

void TCPServer::bootstrapHandler(void *inputData)
{
    binaryPacketWithTcpServer_t *input = (binaryPacketWithTcpServer_t*)inputData;
    std::vector<uint8_t> &bin = *input->bin;
    TCPServer &tcpServer = *input->server;


    DSS_Protocol_t bootstrap(bin);
    if (bootstrap.type != PacketType_t::BootstrapPacket)
        return;

    // get MAC
    std::array<uint8_t, MAC_ADDRESS_LENGTH> nodeMAC;
    for (unsigned int i = 0; i < bootstrap.sourceMAC.size(); ++i)
    {
        nodeMAC[i] = ((uint8_t)bootstrap.sourceMAC[i]);
    }

    // Print DateTime and bootstrap tag
    std::cout << QDateTime::currentDateTime().toString(Qt::DateFormat::ISODate).toStdString() << "[bootstrap]: ";

    // Print MAC
    std::cout << "MAC=" << convertMACtoString(nodeMAC);
    // Add MAC into the set
    tcpServer.addClientMAC(std::move(nodeMAC));

    // Print Root MAC
    BootstrapPacket_t *packet = dynamic_cast<BootstrapPacket_t*>(bootstrap.packet);
    std::array<uint8_t, MAC_ADDRESS_LENGTH> rootMAC;
    std::copy(packet->rootMAC.begin(), packet->rootMAC.end(), rootMAC.begin());

    std::cout << "rootMAC=" << convertMACtoString(rootMAC) << std::endl;
}

std::string TCPServer::convertMACtoString(std::array<uint8_t, MAC_ADDRESS_LENGTH> mac)
{
    std::stringstream ss;

    for (unsigned int i = 0; i < mac.size(); ++i)
    {
        if (i)
            ss << ":";
        ss << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)mac[i];
    }

    return ss.str();
}

void TCPServer::addClientMAC(const std::vector<uint8_t> &client)
{
    std::array<uint8_t, MAC_ADDRESS_LENGTH> clientMAC;
    std::copy(client.begin(), client.end(), clientMAC.begin());

    m_clientAddress.insert(std::move(clientMAC));
}

void TCPServer::addClientMAC(std::vector<uint8_t> &&client)
{
    std::array<uint8_t, MAC_ADDRESS_LENGTH> clientMAC;
    std::move(client.begin(), client.end(), clientMAC.begin());

    m_clientAddress.insert(std::move(clientMAC));
}

void TCPServer::addClientMAC(const std::array<uint8_t, MAC_ADDRESS_LENGTH> &client)
{
    m_clientAddress.insert(client);
}

void TCPServer::addClientMAC(std::array<uint8_t, MAC_ADDRESS_LENGTH> &&client)
{
    m_clientAddress.insert(std::move(client));
}

void TCPServer::removeClientMAC(const std::vector<uint8_t> &client)
{
    std::array<uint8_t, MAC_ADDRESS_LENGTH> clientMAC;
    std::copy(client.begin(), client.end(), clientMAC.begin());

    auto iter = m_clientAddress.find(clientMAC);
    if (iter != m_clientAddress.end())
        m_clientAddress.erase(iter);
}

void TCPServer::removeClientMAC(const std::array<uint8_t, MAC_ADDRESS_LENGTH> &client)
{
    auto iter = m_clientAddress.find(client);
    if (iter != m_clientAddress.end())
        m_clientAddress.erase(iter);
}

int TCPServer::comunicateWithRoot()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    QByteArray byteArray = clientSocket->readAll();
    std::vector<uint8_t> bin;
    for (unsigned int i = 0; i < byteArray.size(); ++i)
    {
        bin.push_back((uint8_t)byteArray[i]);
    }

    binaryPacketWithTcpServer_t data;
    data.server = this;
    data.bin = &bin;

    m_handlers.runAll(&data);

    return -1;
}

std::set<std::array<uint8_t, MAC_ADDRESS_LENGTH>>& TCPServer::getClientMACs()
{
    return m_clientAddress;
}
