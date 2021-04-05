#include "EspServerStorage.h"

EspServerStorage::EspServerStorage()
{
  FmChannelValuesContainer = new JsonContainer("FmChannelValues", 50, 10000);
  GyroValuesContainer = new JsonContainer("GyroValues", 50, 10000);
  SayHeyStmResponse = new SayHiStmResponse();
}

void EspServerStorage::AddFmChannelValues(FmChannelValues *fmChannelValues)
{
  FmChannelValuesContainer->AddToContainer(
    fmChannelValues
  );
}

void EspServerStorage::AddGyroValues(GyroValues *gyroValues)
{
  GyroValuesContainer->AddToContainer(
    gyroValues
  );
}