#pragma once

#include "../EventLimiter.h"

#include "../SinricProNamespace.h"
namespace SINRICPRO_NAMESPACE {

template <typename T>
class MotionSensor {
  public:
    MotionSensor();
    bool sendMotionEvent(bool detected, String cause = "PHYSICAL_INTERACTION");
  private:
    EventLimiter event_limiter;
};

template <typename T>
MotionSensor<T>::MotionSensor()
: event_limiter(EVENT_LIMIT_SENSOR_STATE) {}

template <typename T>
bool MotionSensor<T>::sendMotionEvent(bool detected, String cause) {
  if (event_limiter) return false;
  T* device = static_cast<T*>(this);

  DynamicJsonDocument eventMessage = device->prepareEvent("motion", cause.c_str());
  JsonObject event_value = eventMessage["payload"]["value"];
  event_value["state"] = detected ? "detected" : "notDetected";
  return device->sendEvent(eventMessage);
}

} // SINRICPRO_NAMESPACE