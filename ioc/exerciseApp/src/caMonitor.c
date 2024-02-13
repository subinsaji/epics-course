#include <stdio.h>
#include <stdlib.h>
#include <cadef.h>

void connectFunc( struct connection_handler_args args );
void monitorFunc( struct event_handler_args args );

int main( int argc, char *argv[] )
{
   int status;
   chid channelId;
 
   if(argc < 2)
   {
     printf("Useage: %s <PV name> <value>\n", argv[0]);
     return(0);
   }

   status = ca_context_create( ca_disable_preemptive_callback );
   SEVCHK(status, " ");

   status = ca_create_channel( argv[1], (void (*)())connectFunc, 0, 0, &channelId );
   SEVCHK(status, " ");

   status = ca_pend_io(0.0);
   SEVCHK(status, " ");

   status = ca_create_subscription( DBR_DOUBLE, 0, channelId,
   DBE_VALUE|DBE_LOG|DBE_ALARM, (void (*)())monitorFunc, NULL, NULL );
   SEVCHK(status, " ");

   status = ca_pend_event(0.0); /* Wait forever */
   SEVCHK(status, " ");
   return(0);
}


void connectFunc( struct connection_handler_args args )
{
  if( ca_state(args.chid) != cs_conn )
    printf("%s has just Disconnected\n", ca_name(args.chid));
  else
    printf("%s has just Connected\n", ca_name(args.chid));
}

void monitorFunc( struct event_handler_args args )
{
   printf("Monitor on %s, new value = %f\n",
   ca_name(args.chid), *(double *)args.dbr);
}
