#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <iostream>
#include <list>

#include "AbstractScene.hh"
#include "Set4LibInterfaces.hh"

class ProgramInterpreter{
    Set4LibInterfaces _LibManager;

public:
    bool Read_XML_Config(const char* fileName);
    bool ExecProgram(const char* fileName_Prog);
};