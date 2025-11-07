#include "ProgramInterpreter.hh"

ProgramInterpreter::ProgramInterpreter(){
     _aControl = std::make_shared<AccessControl>();
}
bool ProgramInterpreter::Read_XML_Config(const char* fileName){
    Configuration rConfig;

    try {
            xercesc::XMLPlatformUtils::Initialize();
   }
   catch (const xercesc::XMLException& toCatch) {
            char* message = xercesc::XMLString::transcode(toCatch.getMessage());
            std::cerr << "Error during initialization! :\n";
            std::cerr << "Exception message is: \n"
                 << message << "\n";
            xercesc::XMLString::release(&message);
            return 1;
   }

   xercesc::SAX2XMLReader* pParser = xercesc::XMLReaderFactory::createXMLReader();

   pParser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(xercesc::XMLUni::fgXercesDynamic, false);
   pParser->setFeature(xercesc::XMLUni::fgXercesSchema, true);
   pParser->setFeature(xercesc::XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(xercesc::XMLUni::fgXercesValidationErrorAsFatal, true);

   xercesc::DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       std::cerr << "!!! Plik grammar/actions.xsd, '" << std::endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << std::endl;
       return false;
     }
     pParser->setFeature(xercesc::XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(fileName);
   }
   catch (const xercesc::XMLException& Exception) {
            char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
            std::cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            xercesc::XMLString::release(&sMessage);
            return false;
   }
   catch (const xercesc::SAXParseException& Exception) {
            char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            std::cerr << "Blad! " << std::endl
                 << "    Plik:  " << sSystemId << std::endl
                 << "   Linia: " << Exception.getLineNumber() << std::endl
                 << " Kolumna: " << Exception.getColumnNumber() << std::endl
                 << " Informacja: " << sMessage 
                 << std::endl;

            xercesc::XMLString::release(&sMessage);
            xercesc::XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            std::cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   std::cout<<"Putting " << rConfig.getLibs().size() << " libs to lib interps...\n";
   _LibManager.addLibs(rConfig.getLibs());
   _config_cmds = "Clear\n" + rConfig.GetObjCmds();

   std::cout<<"Putting " << rConfig.GetCubes().size() << " objs to scene...\n";
   _Scene.AddMobileObjs(rConfig.GetCubes());
   
   _aControl->OpenConnection();
   std::cout << "Sending config cmds: " << _config_cmds;
   _aControl->LockAccess();
   Send(_aControl->GetSocket(),_config_cmds.c_str());
   close(_aControl->GetSocket());
   _aControl->UnlockAccess();

   delete pParser;
   delete pHandler;
   return true;
}

bool ProgramInterpreter::ExecProgram(const char* fileName_Prog){
     std::istringstream Stream;
     execPreprocesor(fileName_Prog,Stream);
     std::cout << "\033[44m" << "Preprocesor streamout: " << std::endl << Stream.str() << std::endl;
     std::cout << "======" << "\033[0m" << std::endl;
     std::string cmd_name;
     _aControl->OpenConnection();
     while(Stream >> cmd_name){
          std::cout << "\33[32m" << "Read cmd: " << cmd_name << "\33[0m" << std::endl;
          std::shared_ptr<AbstractInterp4Command> cmd;
          cmd = _LibManager.find_cmd(cmd_name);
          if(cmd == nullptr){
               close(_aControl->GetSocket());
               return false;
          }
          cmd->ReadParams(Stream);
          cmd->PrintCmd();
          cmd->ExecCmd(_Scene,_aControl);
          std::cout << std::endl;
     }
     close(_aControl->GetSocket());
     return true;
}


// void ProgramInterpreter::klient(){
//      cout << "Port: " << PORT << endl;
//      int Socket4Sending;   

//      if (!OpenConnection(Socket4Sending)) return;

//      Sender ClientSender(Socket4Sending,&_aControl,make_shared<Scene>(_Scene) );

//      thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);
//      std::string sConfigCmds = std::string("Clear\n") + _config_cmds;


//      cout << "Konfiguracja:" << endl;
//      cout << sConfigCmds << endl;

//      Send(Socket4Sending,sConfigCmds.c_str());


//      cout << "Akcja:" << endl;    
//      ChangeState(_aControl, _Scene);
//      _aControl.MarkChange();
//      usleep(100000);
//      usleep(100000);

//      cout << "Close\n" << endl;
//      Send(Socket4Sending,"Close\n");
//      ClientSender.CancelCountinueLooping();
//      Thread4Sending.join();
//      close(Socket4Sending);
// }