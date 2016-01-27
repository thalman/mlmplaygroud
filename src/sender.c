#include <malamute.h>

int main (int argc, char **argv) {

    if (argc < 3) {
        printf("usage: ./sender tcp://192.168.1.223:9999 myname\n");
        return 1;
    }

    mlm_client_t *client = mlm_client_new ();
    assert(client);

    int rv;
    rv = mlm_client_connect(client, argv[1], 5000, argv[2]);
    if (rv != 0) {
        zsys_error("connection failed.");
        mlm_client_destroy (&client);
        return -1;
    }

    rv = mlm_client_set_producer (client, "hello-stream");
    if (rv != 0) {
        zsys_error("set_producer failed.");
        mlm_client_destroy (&client);
        return -2;
    }

    while (!zsys_interrupted) {
        zclock_sleep(1000);
        zmsg_t *msg = zmsg_new();
        assert (msg);
        zmsg_pushstr (msg, "hello");
        zmsg_print(msg);
        mlm_client_send (client, "testing message", &msg);
        zmsg_destroy (&msg);
    }
    mlm_client_destroy(&client);
    zsys_info ("finished.");
    return 0;
}

