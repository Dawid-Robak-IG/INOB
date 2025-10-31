#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include <list>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>

#include "AccessControl.hh"
#include "Port.hh"
#include "Scene.hh"
#include "Set4LibInterfaces.hh"
#include "xmlinterp.hh"
#include "Sender.hh"

class ProgramInterpreter{
    Set4LibInterfaces _LibManager;
    std::string _config_cmds;
    Scene _Scene;
    AccessControl _aControl;

public:
    bool Read_XML_Config(const char* fileName);
    bool ExecProgram(const char* fileName_Prog);
    void klient();
private:
//================================================================================
    bool OpenConnection(int &rSocket);
};