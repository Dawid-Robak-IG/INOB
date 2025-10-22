#include "ExecPreprocesor.hh"

bool execPreprocesor(const char *FileName, std::istringstream &inStream){
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream outStream;

    Cmd4Preproc += FileName;
    FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

    if(!pProc) return false;

    while(std::fgets(Line,LINE_SIZE,pProc)){
        outStream << Line;
    }

    inStream.str(outStream.str());
    return pclose(pProc) == 0;
}
