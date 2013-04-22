//==============================================================================
// Send.h
//==============================================================================
/*
    <description, licence, etc.>

    Date        Author          Notes
    dd/mm/yyyy  Seb Madgwick    Initial release
*/
//==============================================================================
#ifndef Send_h
#define Send_h

//------------------------------------------------------------------------------
// Class declaration

class Send {
    public:
        static void flexSensorData();
        static void sensorData();
        static void quaternionData();
        static void miscData(const char* const charArray);
    private:
        static char calcChecksum(const char* const packet, const int packetLength);
};

#endif
//==============================================================================
// End of file
//==============================================================================