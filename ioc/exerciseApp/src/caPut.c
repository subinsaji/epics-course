#include <stdio.h>
#include <stdlib.h>
#include <cadef.h>      /* Structures and data types used by CA */

int main( int argc, char *argv[] )
{
  int status;
  chid channelId;
  double val;

  if(argc < 3)
  {
    printf("Useage: %s <PV name> <value>\n", argv[0]);
    return(0);
  }

  val = atof( argv[2] );

  status = ca_context_create( ca_disable_preemptive_callback );
  SEVCHK(status, " ");

  status = ca_create_channel( argv[1], 0, 0, 0, &channelId );
  SEVCHK(status, " ");

  status = ca_pend_io(0.0);
  SEVCHK(status, " ");

  status = ca_put( DBR_DOUBLE, channelId, &val );
  SEVCHK(status, " ");

  status = ca_pend_io(0.0);
  SEVCHK(status, " ");

  return(0);
}
