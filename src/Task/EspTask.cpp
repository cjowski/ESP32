#include "EspTask.h"

EspTask::EspTask(int id)
{
  ID = id;
}

bool EspTask::IsReadyForLoop(int currentTime)
{
  return currentTime - PreviousStepTime > LOOP_STEP_DELAY_TIME();
}

bool EspTask::IsOvertime(int currentTime)
{
  return currentTime - StartTime > LIFE_TIME();
}