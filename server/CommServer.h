// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000 Alistair Riddoch

#ifndef COMM_SERVER_H
#define COMM_SERVER_H

#include <common/const.h>

extern "C" {
    #include <netinet/in.h>
    #include "protocol_instructions.h"
}

class CommClient;

typedef std::map<int, CommClient *> client_map_t;

class CommServer {
    int server_fd;
    int server_port;
    client_map_t clients;

    int accept();
    void idle();

    static bool use_metaserver;
    static const int metaserver_port = 8453;
    struct sockaddr_in meta_sa;
    int meta_fd;
  public:
    ServerRouting * server;
    const string identity;

    CommServer(const string & ident) : identity(ident) { }

    int setup(int port);
    void loop();
    void remove_client(CommClient * client, char * msg);
    void remove_client(CommClient * client);
    void metaserver_keepalive();
    void metaserver_reply();
    void metaserver_terminate();
    int numClients() {
        return clients.size();
    }
};

#endif /* COMM_SERVER_H */
