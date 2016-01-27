#include <malamute.h>

int main (int argc, char **argv) {

    if (argc < 3) {
        printf("usage: %s tcp://192.168.1.34:9999 myname\n", argv[0]);
        return 1;
    }

    mlm_client_t *client = mlm_client_new ();
    assert(client);

    int rv;
    rv = mlm_client_connect(client, argv[1], 5000, argv[2]);
    if (rv == -1) {
        zsys_error("connection failed.");
        mlm_client_destroy (&client);
        return -1;
    }
    zsys_info ("client is connected");

    rv = mlm_client_set_consumer (client, "hello-stream", ".*");
    if (rv == -1) {
        zsys_error ("set_consumer failed.");
    }
    // We don't really need a poller. We just have one client (actor/socket)
    int count = 0;
    zsys_info ("client is configured");
    while (!zsys_interrupted) {
        zmsg_t *msg = mlm_client_recv (client);
        if (msg) {
            zmsg_destroy (&msg);
            count ++;
            if ( count % 100 == 0 ) {
                zsys_info ("received %d", count);
            }
        }
    }
    mlm_client_destroy(&client);
    zsys_info ("finished.");
    return 0;
}

