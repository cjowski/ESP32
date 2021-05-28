#include "EspServerStorage.h"

EspServerStorage::EspServerStorage()
{
  FmChannelValuesContainer = new JsonContainer("FmChannelValues", 10, 2000);
  GyroValuesContainer = new JsonContainer("GyroValues", 10, 2000);
  MotorsContainer = new JsonContainer("Motors", 10, 2000);
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

void EspServerStorage::AddMotors(Motors *motors)
{
  MotorsContainer->AddToContainer(
    motors
  );
}