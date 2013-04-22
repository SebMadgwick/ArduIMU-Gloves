//==============================================================================
// VibrationMotor.h
//==============================================================================
/*
    <description, licence, etc.>

    Date        Author          Notes
    dd/mm/yyyy  Seb Madgwick    Initial release
*/
//==============================================================================
#ifndef VibrationMotor_h
#define VibrationMotor_h

//------------------------------------------------------------------------------
// Class declaration

class VibrationMotor {
    public:
        static void init();
        static void doTasks();
        static void pulse(const char num);
};

#endif
//==============================================================================
// End of file
//==============================================================================