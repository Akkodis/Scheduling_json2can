/*
 Class to collect all iso2 exi data types in one object and transform it into a json string.
*/

#ifndef ISO_EXI_WRAPPER_H
#define ISO_EXI_WRAPPER_H


#include <iostream>
#include <list>
#include <string.h>
#include  <typeinfo> 
#include "iso1EXIDatatypes.h"
#include "json/json.h"

class IsoExiWrapper
{
  public:
  enum ErrorFlag {
    isOk,
    isWarning,
    isError
  };
  struct Error {
    ErrorFlag status = isOk;
    std::string message = "";
    Error(ErrorFlag s, std::string m) {
      status = s;
      message = m;
    }
  };
  struct ErrorList {
    std::list<Error> elements;
    void append2List(ErrorList& elements2Add) {
      for (auto &elem : elements2Add.elements)
        elements.push_back(elem);
    }
    void push_back(Error err) {
      elements.push_back(err);
    }
    void addErrorMsg(std::string msg) {elements.push_back(Error(isError, msg));}
    void addWarningMsg(std::string msg) {elements.push_back(Error(isWarning, msg));}
    void addOKMsg(std::string msg) {elements.push_back(Error(isOk, msg));}
    void addErrorSetValMsg(std::string key, std::string val)
    {
      std::string msg = "'"+key+"' ca'nt be set to: "+val+".\n";
      elements.push_back(Error(isError, msg));
    }
    template <typename T>
    void addOKSetValMsg(std::string key, T &obj)
    {
      throw std::invalid_argument("addOKSetValMsg dos not support type: " + std::string(typeid(T).name()));
    }
    void addOkFill(std::string structName) {
      elements.push_back(Error(isOk,"'"+structName+"' will be filled\n"));
    }
    void addOKSetValMsg(std::string key, uint val)
    {
      std::string msg = "'"+key+"' is set to: " + std::to_string(val) + "\n";
      elements.push_back(Error(isOk, msg));
    }
    void addOKSetValMsg(std::string key, unsigned char val)
    {
      std::string msg = "'"+key+"' is set to: " + std::to_string(val) + "\n";
      elements.push_back(Error(isOk, msg));
    }
    void addOKSetValMsg(std::string key, signed char val)
    {
      std::string msg = "'"+key+"' is set to: " + std::to_string(val) + "\n";
      elements.push_back(Error(isOk, msg));
    }
    void addOKSetValMsg(std::string key, short val)
    {
      std::string msg = "'"+key+"' is set to: " + std::to_string(val) + "\n";
      elements.push_back(Error(isOk, msg));
    }
    void addOKSetValMsg(std::string key, std::string val)
    {
      std::string msg = "'"+key+"' is set to: " +val + "\n";
      elements.push_back(Error(isOk, msg));
    }
    void addErrorNotInMsg(std::string key, std::string structName) {
      elements.push_back(Error(isError,"'"+key+"' is not included in '"+structName+"'!\n"));
    }
    void addWarningNum(std::string key, uint num, uint maxNum) {
      elements.push_back(Error(isWarning,"'"+key+"' has "+std::to_string(num)+"members, but the maximum is: " + std::to_string(maxNum) +"!\n"));
    }
  };
private:

  bool isComplete;
  std::string bufferStr;
  iso1SAScheduleListType scheduleList;

public:
    IsoExiWrapper(/* args */);
    ~IsoExiWrapper();

    ErrorList init(Json::Value jsonObj);
    ErrorList evaluate();
    std::string toJsonString();
    uint32_t numBytes;
    uint32_t iByte;
    void add2Buffer(std::string text, uint32_t index);
    void clear();
    void setNumBytes(uint32_t _num) {numBytes = _num;}
    bool isStringComplete(){return isComplete;}
};



#endif /* ISO_EXI_WRAPPER_H */