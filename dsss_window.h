#ifndef DSSS_WINDOW_H
#define DSSS_WINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "TCP_Server/tcp_server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DSSS_Window; }
QT_END_NAMESPACE

class DSSS_Window : public QMainWindow
{
    Q_OBJECT

public:
    enum LogLevel_t
    {
        Info,
        Warning,
        Error,
    };

    DSSS_Window(QWidget *parent = nullptr);
    ~DSSS_Window();

private:
    void log(const QString& msg, const LogLevel_t level = Info);

    Ui::DSSS_Window *ui;
    TCPServer m_server;
    QTimer m_updateActiveNodesTimer;

private slots:
    void slot_startServer();
    void slot_stopServer();

    void slot_updateActiveNodes();
};
#endif // DSSS_WINDOW_H
