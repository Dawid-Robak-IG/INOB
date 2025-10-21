#include "ExecPreprocesor.hh"

bool execPreprocesor(const char *FileName, std::istringstream &ISTRM4Cmds){
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream OTmpStrm;

    Cmd4Preproc += FileName;
    FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

    if(!pProc) return false;

    while(std::fgets(Line,LINE_SIZE,pProc)){
        OTmpStrm << Line;
    }

    ISTRM4Cmds.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}
