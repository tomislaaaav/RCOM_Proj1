/*Non-Canonical Input Processing*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "alarm.h"
#include "link_layer.h"
#include "utils.h"
#include "app_layer.h"

int main(int argc, char** argv) {
    
	
  	LinkLayer *link_layer = malloc(sizeof(LinkLayer));

  struct sigaction sa;
  sa.sa_flags = 0;
  sa.sa_handler = atende;
  if (sigaction(SIGALRM, &sa, NULL) == -1) {
    perror("Error: cannot handle SIGALRM");
    return 0;
  }

  if ( (argc < 2) || 
	      (strcmp("/dev/ttyS0", argv[1])!=0 && 
	      (strcmp("/dev/ttyS4", argv[1])!=0))) {
    printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
    exit(1);
  }

  ll_init(link_layer, argv[1], BAUDRATE, 1, 5, 1000, RECEIVER); 

  app_layer(link_layer, 0);

  fprintf(stderr, "Saiu da app_layer. Encerrar a link_layer\n");

  ll_end(link_layer);

	return 0;
}
