

#ifndef IDS_HPP
#define IDS_HPP

#include <string>
#include <vector>

class Patient_ID {
public:
    static int get_patient_id();
    static void update_patient_id(int old_id);
};

class Assistant_ID {
    public:
    int get_assistant_id();
    void update_assistant_id(int old_id);
};

class Doctor_ID {
    public:
    int get_doctor_id();
    void update_doctor_id(int old_id);
};

#endif //IDS_HPP
