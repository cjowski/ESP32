#ifndef SAY_HI_STM_RESPONSE
#define SAY_HI_STM_RESPONSE

  #include "Json/Json.h"
  #include "EspServer/Utils/EspServerEnums.h"

  class SayHiStmResponse : public Json
  {
    private:
    String Greeting;
    bool Done;

    public:
    int JSON_BUFFER_SIZE() const { return 50; };
    SayHiStmResponse(String greeting, bool done);
    DynamicJsonDocument GetJson();
    bool Equals(Json *otherJson) { return false; }
  };

#endif