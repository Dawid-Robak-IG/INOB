#include "ProgramInterpreter.hh"


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
   

   delete pParser;
   delete pHandler;
   return true;
}

bool ProgramInterpreter::ExecProgram(const char* fileName_Prog){
     return _LibManager.execFileCmds(fileName_Prog);
}




//===============================================================
/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 */
bool ProgramInterpreter::OpenConnection(int &rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}

void ProgramInterpreter::klient(){
     cout << "Port: " << PORT << endl;
     int Socket4Sending;   

     if (!OpenConnection(Socket4Sending)) return;

     Sender ClientSender(Socket4Sending,&_aControl,make_shared<Scene>(_Scene) );

     thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);
     const char *sConfigCmds =
     "Clear\n"
     "AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
     "AddObj Name=Podstawa1.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
     "AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"       
     "AddObj Name=Podstawa2 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
     "AddObj Name=Podstawa2.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
     "AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";


     cout << "Konfiguracja:" << endl;
     cout << sConfigCmds << endl;

     Send(Socket4Sending,sConfigCmds);


     cout << "Akcja:" << endl;    
     usleep(20000);
     ChangeState(_aControl, _Scene);
     _aControl.MarkChange();
     usleep(100000);
     usleep(100000);

     cout << "Close\n" << endl;
     Send(Socket4Sending,"Close\n");
     ClientSender.CancelCountinueLooping();
     Thread4Sending.join();
     close(Socket4Sending);
}