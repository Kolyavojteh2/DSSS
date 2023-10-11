#include "dsss_window.h"
#include "./ui_dsss_window.h"

#include <QString>

DSSS_Window::DSSS_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DSSS_Window)
{
    ui->setupUi(this);

    connect(ui->p_startServer, SIGNAL(clicked()), this, SLOT(slot_startServer()));
    connect(ui->p_stopServer, SIGNAL(clicked()), this, SLOT(slot_stopServer()));

    connect(&m_updateActiveNodesTimer, SIGNAL(timeout()), this, SLOT(slot_updateActiveNodes()));
    m_updateActiveNodesTimer.setInterval(5000);
    m_updateActiveNodesTimer.start();

}

void DSSS_Window::log(const QString& msg, const LogLevel_t level)
{
    static const char* tagColorArr[] = {
        "<div style=\"color: black;\">",
        "<div style=\"color: orange;\">",
        "<div style=\"color: red;\">",
    };

    static const char* levelArr[] = {
        "[INFO]",
        "[WARNING]",
        "[ERROR]",
    };

    QString colorTagOpen = tagColorArr[level];
    static QString colorTagClose = "</div>";

    QString levelStr = levelArr[level];

    ui->p_Log->append(QString("%1 %2 %3: %4")
                          .arg(colorTagOpen)
                          .arg(levelStr)
                          .arg(colorTagClose)
                          .arg(msg));
}

void DSSS_Window::slot_startServer()
{
    m_server.startServer();
    log("server started");
}

void DSSS_Window::slot_stopServer()
{
    m_server.stopServer();
    log("server stopped");
}

void DSSS_Window::slot_updateActiveNodes()
{
    ui->p_activeNodes->clear();

    std::set<std::array<uint8_t, MAC_ADDRESS_LENGTH>> nodes = m_server.getClientMACs();
    for (auto &it : nodes)
    {
        std::string mac = TCPServer::convertMACtoString(it);
        ui->p_activeNodes->addItem(QString::fromStdString(mac));
    }
}

DSSS_Window::~DSSS_Window()
{
    delete ui;
}

