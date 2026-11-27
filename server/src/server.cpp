#include "server.hpp"
#include <QDebug>

Server::Server() {}

Server::~Server() {
    for (auto socket : mActiveClients) {
        socket->close();
    }
    mActiveClients.clear();
}

bool Server::open(const QString& port) {
    if (!listen(QHostAddress::Any, port.toInt())) {
        qDebug() << "Unable to start server";
        return false;
    }
    
    connect(this, &QTcpServer::newConnection, this, &Server::newClientConnected);
    qDebug() << "Server successfully started on port" << port;
    return true;
}

void Server::newClientConnected() {
    auto client = nextPendingConnection();
    
    if (client->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "New connection! Socket descriptor:" << client->socketDescriptor();
        
        mActiveClients.insert(client->socketDescriptor(), client);
        
        connect(client, &QTcpSocket::readyRead, this, &Server::receiveMessage);
        connect(client, &QTcpSocket::disconnected, this, &Server::clientStateChanged);
    } else {
        qDebug() << "Failed connection";
    }
}

void Server::clientStateChanged() {
    auto client = static_cast<QTcpSocket*>(sender());
    
    if (client) {
        int descriptor = client->socketDescriptor();
        mActiveClients.remove(descriptor);
        qDebug() << "Client connection closed. Socket descriptor:" << descriptor;
        client->deleteLater();
    }
}

void Server::receiveMessage() {
    auto client = static_cast<QTcpSocket*>(sender());
    
    if (client) {
        QByteArray data = client->readAll();
        
        QString message = QString::fromLocal8Bit(data);
        qDebug() << "Received message from client:" << message;
        
        client->flush();
    }
}
