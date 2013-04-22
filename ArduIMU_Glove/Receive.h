//==============================================================================
// Receive.h
//==============================================================================
/*
    <description, licence, etc.>

    Date        Author          Notes
    dd/mm/yyyy  Seb Madgwick    Initial release
*/
//==============================================================================
#ifndef Receive_h
#define Receive_h

//------------------------------------------------------------------------------
// Class declaration

class Receive {
    public:
        static void doTasks();
    private:
        static char rxBuf[256];
        static unsigned char rxBufIndex;
        static char calcChecksum(const int packetLength);
};

#endif
//==============================================================================
// End of file
//==============================================================================