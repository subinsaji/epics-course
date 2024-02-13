#include <stdio.h>
#include <stdlib.h>
#include <cadef.h>

void printResults(struct dbr_ctrl_double data, char *timeString);


int main(int argc,char **argv)
{
  int                    status;
  chid                   channelId;
  struct dbr_ctrl_double data;
  struct dbr_time_double tdata;
  char                   timeString[64];

  if(argc < 2)
  {
    printf("Useage: %s <PV name>\n", argv[0]);
    return(0);
  }

  status = ca_context_create(ca_disable_preemptive_callback);
  SEVCHK(status,"");

  status = ca_create_channel(argv[1],0,0,0,&channelId);
  SEVCHK(status,"");

  status = ca_pend_io(0.0);
  SEVCHK(status,"");

  status = ca_get(DBR_CTRL_DOUBLE,channelId,&data);
  SEVCHK(status,"");

  status = ca_get(DBR_TIME_DOUBLE,channelId,&tdata);
  SEVCHK(status,"");

  status = ca_pend_io(0.0);
  SEVCHK(status,"");

  epicsTimeToStrftime(timeString, sizeof(timeString), "%a %b %d %Y %H:%M:%S.%f", &tdata.stamp);
  printResults(data,timeString);
  return(0);
}


void printResults(struct dbr_ctrl_double data, char *timeString)
{
  printf("Channel Value       = %f\n", data.value);
  printf("Alarm Status        = %d\n", data.status);
  printf("Alarm Severity      = %d\n", data.severity);
  printf("Precision           = %d\n", data.precision);
  printf("Engineering units   = %s\n", data.units);
  printf("Upper Display Limit = %f\n", data.upper_disp_limit);
  printf("Lower Display Limit = %f\n", data.lower_disp_limit);
  printf("Upper Alarm Limit   = %f\n", (float)data.upper_alarm_limit);
  printf("Upper Warning Limit = %f\n", (float)data.upper_warning_limit);
  printf("Lower Warning Limit = %f\n", (float)data.lower_warning_limit);
  printf("Lower Alarm Limit   = %f\n", (float)data.lower_alarm_limit);
  printf("Last Processed on:    %s\n", timeString);
}
