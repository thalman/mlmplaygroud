#include <malamute.h>

#define MLM_ENDPOINT "tcp://127.0.0.1:9999"
//#define MLM_ENDPOINT "ipc://@/malamute"
#define AGENT_NAME "tom"

int main (int argc, char **argv) {

    mlm_client_t *client = mlm_client_new ();
    assert(client);

    int rv;
    rv = mlm_client_connect(client, MLM_ENDPOINT, 5000, "receiver");
    if (rv == -1) {
        zsys_error("connection failed.");
        mlm_client_destroy (&client);
        return -1;
    }

    /* I don't produce any messages
    rv = mlm_client_set_producer (client, "hello-stream");
    if (rv != 0) {
        zsys_error("set_producer failed.");
        mlm_client_destroy (&client);
        return -2;
    }
    */

    rv = mlm_client_set_consumer (client, "hello-stream", ".*");
    if (rv == -1) {
        zsys_error ("set_consumer failed.");
    }
    // We don't really need a poller. We just have one client (actor/socket)
    while (!zsys_interrupted) {
        zsys_debug ("WAITING");
        zmsg_t *msg = mlm_client_recv (client);
        if (msg) {
            zsys_info ("sender: %s", mlm_client_sender(client));
            zmsg_print (msg);
            zmsg_destroy (&msg);
        }
    }
    mlm_client_destroy(&client);
    zsys_info ("finished.");
    return 0;
}

