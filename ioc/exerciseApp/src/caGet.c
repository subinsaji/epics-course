#include <stdio.h>
#include <stdlib.h>
#include <cadef.h>

typedef struct info
{
  char   *project;
  int    numIoc;
  double current;
} info_t;

void usrFunc( struct event_handler_args args );

int main( int argc, char *argv[] )
{
  int    status;
  chid   channelId;
  info_t info;

  if(argc < 2)
  {
    printf("Useage: %s <PV name>\n", argv[0]);
    return(0);
  }

  info.project = "Diamond";
  info.numIoc  = 167;
  info.current = 3.45;

  status = ca_context_create( ca_disable_preemptive_callback );
  SEVCHK(status, " ");

  status = ca_create_channel( argv[1], 0, 0, 0, &channelId );
  SEVCHK(status, " ");

  status = ca_pend_io(0.0);

  status = ca_get_callback( DBR_DOUBLE, channelId, (void (*)())usrFunc, &info );
  SEVCHK(status, " ");

  status = ca_pend_event(0.1); /* This is different! */

  return(0);
}

void usrFunc( struct event_handler_args args ) /* cadef.h */
{
  info_t *t = (info_t *)args.usr;

  if( args.status == ECA_NORMAL )
  {
    printf("UsrFunc called: Value = %f\n",  *(double *)args.dbr);
    printf("User Argument Name    = %s\n",  t->project);
    printf("User Argument NumIoc  = %d\n",  t->numIoc);
    printf("User Argument Current = %f\n",  t->current);
    printf("Channel Name          = %s\n",  ca_name(args.chid) );
    printf("Number of Elements    = %ld\n", ca_element_count(args.chid) );
    printf("Host Name             = %s\n",  ca_host_name(args.chid) );
  }
}
