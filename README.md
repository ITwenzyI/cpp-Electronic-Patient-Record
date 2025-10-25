# 🩺 Electronic Patient Record (EPR) System – C++ Implementation

## 🧠 Project Goal

This C++ project simulates a simple yet structured **Electronic Patient Record (EPR) System**, designed for hands-on practice in object-oriented programming, file handling, and user role management. It supports patients, doctors, assistants, and an admin role, each with role-specific functionality. The project features realistic ID systems, folder-based data storage and a modular architecture, making it ideal for learning practical C++ in a healthcare related context.

---

## 💡 Purpose
This project was created for learning purposes in the field of medical informatics and to improve practical C++ development and architecture skills.
It aims to simulate a real-world clinical information workflow on a simple and accessible level.

---

## 📍 Status
🔧 Currently under development

---

## 🛠️ Concepts Used

- Classes & Inheritance
- Access specifiers (`private`, `protected`, `public`)
- File input/output (`fstream`)
- Text-based user menu
- Simple role system (Patient, Doctor, Assistant, Admin)
- Header/Source file separation

---

## 🚀 Features (Work in Progress)

- Role-based access:
  - **Patients** can view personal records and request appointments
  - **Doctors** can review appointments and add medical records
  - **Assistants** can manage and confirm appointment requests
- Individual folder structure for each patient (`/data/Patients/`)
- Text-based data files (`info.txt`, `appointments.txt`, `records.txt`)
- Clear class separation with inheritance (User → Patient/Doctor/Assistant)
- File-based storage using `std::filesystem`

## 🔹 Core Functionalities
- System Initialization on first Startup with Admin-Setup
- System requires at least one Assistant and one Doctor to operate
- Admin Menu which can be opened in the Main Menu with #admin
- Simple Login System which checks if the FirstName and LastName are correct for the ID (Checks in info.txt from the ID)
- Simple Booting Up Scenario with Threads (For realism)
- User is the base class for Patient, Assistant, Doctors (Stores all the infos and the generally functions)
- Every Role has their own unique ID (Patient == P00000001, Assistant == A0001, Doctor == D0001)
- IDs start with '1' and get updated for every new User. Stored in data/role_id.txt (patient_id.txt, ...)
- Utils functions in separate file.
- IDs functions in separate file and class for each role
- Extensive code comments for learning
- Threads to add realism

---

## 🔹 IDs functions
| Role      | Prefix | Example ID  |
|-----------|--------|-------------|
| Patient   | `P`    | `P00000001` |
| Doctor    | `D`    | `D0001`     |
| Assistant | `A`    | `A0001`     |

#### Class Patient_ID:
- get_patient_id returns the ID which is stored in ``patient_id.txt``
- update_patient_id Updates the ID in ``patient_id.txt`` with +1
#### Class Assistant_ID:
- get_assistant_id returns the ID which is stored in ``assistant_id.txt``
- update_assistant_id Updates the ID in ``assistant_id.txt`` with +1
#### Class Doctor_ID:
- get_doctor_id returns the ID which is stored in ``doctor_id.txt``
- update_doctor_id Updates the ID in ``doctor_id.txt`` with +1

## 🔹 Utils Functions
- getDate in the Format ``YYYY-MM-DD``
- getTime in the Format ``HH:MM:SS``
- random_number, return a random **int Number** between min and max
- cleaned, removes ``\r`` and all ``whitespace`` characters to clear input before storage or comparison
- get_file_path_from_id, gets the correct Path from the ID (Example: D0001 == Doctor)

## 🔹 Admin Functions
- Create New Patient | Creates a new Folder <Patient-ID> with ``info.txt``, ``medications.txt``, ``records.txt``, ``appointments.txt``
- Create Doctors | Creates a new Folder <Doctor-ID> with ``info.txt``
- Create Assistants | Creates a new Folder <Assistant-ID> with ``info.txt``
- View Patient Info | Reads and displays `info.txt`
- View Doctors Info | Reads and displays `info.txt`
- View Assistants Info | Reads and displays `info.txt`
- Update Info Field | Updates a field in `info.txt` by ID

## 🔹 Patient Functions
- Request Appointments | Request in ``request.txt``. Needs Conformation to land in ``appointments.txt``
- View Patient Appointments | Reads and displays `appointments.txt`
- View Patient Medications | Reads and displays `medications.txt`
- View Patient Records | Reads and displays `records.txt`

## 🔹 Assistant Functions
- Create New Patient | Creates a new Folder <Patient-ID> with ``info.txt``, ``medications.txt``, ``records.txt``, ``appointments.txt``
- Update Info Field | Updates a field in `info.txt` by ID
- Review Appointments |  Reads and displays `request.txt`. Assistant can confirm, reject or skip
- Add Medications | Adds a line to `medications.txt`
- Add Records | Adds a line to `records.txt`
- View Patient Info | Reads and displays `info.txt`
- View Patient Appointments | Reads and displays `appointments.txt`
- View Patient Medications | Reads and displays `medications.txt`
- View Patient Records | Reads and displays `records.txt`
- Add Extra Info | Reads and Updates `info.txt` with an Extra Info

## 🔹 Doctor Functions
- Add Medications | Adds a line to `medications.txt`
- Add Records | Adds a line to `records.txt`
- View Patient Info | Reads and displays `info.txt`
- View Patient Appointments | Reads and displays `appointments.txt`
- View Patient Medications | Reads and displays `medications.txt`
- View Patient Records | Reads and displays `records.txt`
- Update Info Field | Updates a field in `info.txt` by ID
- Add Extra Info | Reads and Updates `info.txt` with an Extra Info

---


## 📦 Project Structure
```
│   ├── main.cpp              
📁 /src/
│   ├── Admin/
│   │   └── Admin.cpp/hpp        
│   ├── User/
│   │   └── User.cpp/hpp        
│   ├── Patient/
│   │   └── Patient.cpp/hpp     
│   ├── Doctor/
│   │   └── Doctor.cpp/hpp      
│   ├── Assistant/
│       └── Assistant.cpp/hpp 
│   ├── Utils/
│       └── utils.cpp/hpp  
📁 /data/
│   ├── Patients/
│     └── /<patient_id>/
│           ├── info.txt       
│           ├── records.txt       
│           └── appointments.txt    
│   ├── Assistants/
│     └── /<assistant_id>/
│           └── info.txt         
│   ├── Doctors/
│     └── /<doctor_id>/
│           └── info.txt        
│   ├── Appointments/
│       └── requests.txt        
│   ├── admin_logging.txt
│   ├── assistant_id.txt
│   ├── doctor_id.txt
│   ├── patient_id.txt
│
```

## 🧩 To-Do
 - Save Users in Database
 - Password for Login
 - Debug-Mode
 - Log-System
 - Backup whole User
 - Demo-System
 - Tutorial
 - Wards System with bed occupancy
 - Medical visits Information
 - Graph for Medication
 - Complete Front-End 

## 📬 Contact
If you have questions, suggestions, or want to contribute, feel free to open an issue or contact me via GitHub.

## 👤 Author
This project was created by **Kilian** as part of independent study in Medical Informatics.
The software was fully developed in C++ using modern programming techniques.

