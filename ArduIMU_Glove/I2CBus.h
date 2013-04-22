//==============================================================================
// I2CBus.h
//==============================================================================
/*
    <description, licence, etc.>

    Date        Author          Notes
    dd/mm/yyyy  Seb Madgwick    Initial release
*/
//==============================================================================
#ifndef I2CBus_h
#define I2CBus_h

//------------------------------------------------------------------------------
// Definitions

typedef union {
    struct {
        int x;
        int y;
        int z;
    };
    struct {
        char xByteL;
        char xByteH;
        char yByteL;
        char yByteH;
        char zByteL;
        char zByteH;
    };
} Magnetometer;

//------------------------------------------------------------------------------
// Class declaration

class I2CBus {
    public:
        static Magnetometer magnetometer;
        static void init();
        static void readMagnetometer();
        static void setRGB(const unsigned char red, const unsigned char green, const unsigned char blue);
};

#endif
//==============================================================================
// End of file
//==============================================================================