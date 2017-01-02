#include "amessage.h"

// Command to compile me:
//	gcc amessage_serialize.c ./proto-files/amessage.pb-c.c -I/usr/local/include -L/usr/local/lib -lprotobuf-c -o test


int main (int argc, const char * argv[]){

	AMessage msg = AMESSAGE__INIT; // AMessage
	void *buf;                     // Buffer to store serialized data
	unsigned len;                  // Length of serialized data

	if (argc != 2 && argc != 3) {
		fprintf(stderr, "usage: amessage a [b]\n");
		return 1;
	}

	msg.a = atoi(argv[1]);
	if (argc == 3) { msg.has_b = 1; msg.b = atoi(argv[2]); }
	len = amessage__get_packed_size(&msg);

	buf = malloc(len);
	amessage__pack(&msg, buf);

	fprintf(stderr, "Writing %d serialized bytes\n", len);
	fwrite(buf, len, 1, stdout);

	free(buf);
	return 0;
}