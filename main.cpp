#include<string>
#include<vector>
#include<iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/if.h>
#include <fstream>
#include "isoExiWrapper.h"
#include "json/json.h"
#include <regex>

using namespace std;


/** \brief Parse from stream, collect comments and capture error info.
 * Example Usage:
 * $g++ readFromStream.cpp -ljsoncpp -std=c++11 -o readFromStream
 * $./readFromStream
 * // comment head
 * {
 *    // comment before
 *    "key" : "value"
 * }
 * // comment after
 * // comment tail
 */
int runJson(std::string strJson) {
  // std::string strJson = "{\"mykey\" : \"myvalue\"}"; // need escape the quotes
   //strJson = R"({"Age": 20,\n  "Name": "colin"})";
  std::regex e ("\\\\n"); 
   strJson = std::regex_replace(strJson,e,"");
   Json::Value root;
   Json::Reader reader;
   bool parsingSuccessful = reader.parse(strJson.c_str(), root); // parse process
   if (!parsingSuccessful)
   {
       std::cout << "Failed to parse"
                 << reader.getFormattedErrorMessages();
       return 0;
    }
    std::vector<std::string> members = root.getMemberNames();
    for (auto &member : members)
    {
       Json::Value memObj = root.get(member, "");
    //   std::cout <<"member: "<< member<<" with "<< memObj.type();
  //  std::cout << root.get(member, "A Default Value if not exists" ).asString() << std::endl;
//std::cout<<endl;
    }

  //  std::cout << root.get("v2gci_t_Value", "A Default Value if not exists" ).asString() << std::endl;
    IsoExiWrapper wrapper;
    IsoExiWrapper::ErrorList ret = wrapper.init(root);
    for (auto &error : ret.elements) {
        if (error.status == IsoExiWrapper::ErrorFlag::isOk)
            std::cout << "ExiWrapper: " << error.message;
        else if (error.status == IsoExiWrapper::ErrorFlag::isWarning)
            std::cout << "ExiWrapper - Warning: " << error.message;
        else if (error.status == IsoExiWrapper::ErrorFlag::isError)
            std::cout << "ExiWrapper - Error : " << error.message;
    }
    std::cout<<wrapper.toJsonString()<<std::endl;
    return 0;
}


#define PRINT_NAME(x) std::cout << #x << " - " << typeid(x).name() << '\n'


int main(int argc, char* argv[]){
    try{

        // read json text
        string line;
        string jsonInput = "";
        string fileName = "tests/schedule01.txt";
        if (argc > 1) fileName = argv[1];
        ifstream scheduleFile(fileName);
        if (scheduleFile.is_open())
        {
            while (getline(scheduleFile, line))
            {
                jsonInput += line;
            }
            scheduleFile.close();
          //  cout << jsonInput << endl;
        }
        else
            cout << "Unable to open file";
        cout << "end\n";
        runJson(jsonInput);
    }
    catch (string e)
    {
       cerr << e << endl;
    }
}


















