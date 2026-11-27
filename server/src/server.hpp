#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server();
    ~Server();
    bool open(const QString& port);

public slots:
    void newClientConnected();
    void clientStateChanged();
    void receiveMessage();

private:
    QMap<int, QTcpSocket*> mActiveClients;
};
