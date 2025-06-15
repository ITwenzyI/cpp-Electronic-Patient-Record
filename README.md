# 🩺 Electronic Patient Record – C++ Project

## 🧠 Project Goal

This project simulates a simplified **electronic patient record** (EPR) system using C++. It was created to practice object-oriented programming, file handling, and structured data management. The software allows storing, editing, and displaying patient data, including appointments, medications, records, and more.

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

### 🔹 Core Functionalities
- System Inizialistaton on first Startup with Admin-Setup
- System needs to have 1 Assistant and 1 Doctor
- Admin Menu which can be opened in the Main Menu with #admin
- Simple Login System which checks if the FirstName and LastName are correct for the ID (Checks in info.txt from the ID)
- Simple Booting Up Scenario with Threads (For realismus)
- User is the over Class for Patient, Assistant, Doctors (Stores all the infos and the generally functions)
- Every Role has their own unique ID (Patient == P00000001, Assistant == A0001, Doctor == D0001)
- IDs start with '1' and get updated for every new User. Stored in data/role_id.txt (patient_id.txt, ...)
- Utils functions in seperate file.
- IDs functions in seperate file and class for each role)
- A lot of comments to understand each process
- Threads to add realismus

---

### 🔹 IDs functions
Class Patient_ID:
- get_patient_id returns the ID which is stored in patient_id.txt
- update_patient_id Updates the ID in patient_id.txt with +1
Class Assistant_ID:
- get_assistant_id returns the ID which is stored in assistant_id.txt
- update_assistant_id Updates the ID in assistant_id.txt with +1
Class Doctor_ID:
- get_docotr_id returns the ID which is stored in doctor_id.txt
- update_doctor_id Updates the ID in doctor_id.txt with +1

### 🔹 Utils Functions
- getDate in the Format YYYY-MM-DD
- getTime in the Format HH:MM:SS
- random_number, return a random int Number between min and max
- cleaned, cleans a string from \r and all white spaces
- get_file_path_from_id, gets the correct Path from the ID so for D0001 it's Doctors...

### 🔹 Admin Functions
- Create Patients
- Create Doctors
- Create Assistants
- View Patients
- View Doctors
- View Assistants
- Update Field in all the info.txt

### 🔹 Patient Functions
- Request Appointments, which need to be confirmed by Assistants
- See all your Medications, Appointments, Records

### 🔹 Assistant Functions
- Create New Patient
- Update a Field in the info.txt from a Patient with his ID
- Review Appointments and confirm or reject them
- Add Medications to a Patient
- Add Records to a Patient
- View Patient Info (All his Details like `name`, `address` ...)
- View Patient Appointments
- View Patient Medications
- View Patient Records
- Add Extra Info to a info.txt from a Patient

### 🔹 Doctor Functions
- Add Medications to a Patient
- Add Records to a Patient
- View Patient Info
- View Patient Appointments
- View Patient Medications
- View Patient Records
- Update a Field in the info.txt from a Patient with his ID
- Add Extra Info to a info.txt from a Patient

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
│   ├── Assistantss/
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

## 💡 Purpose
This project was created for learning purposes in the field of medical informatics and to improve practical C++ development and architecture skills.
It aims to simulate a real-world clinical information workflow on a simple and accessible level.

## 📬 Contact
If you have questions, suggestions, or want to contribute, feel free to open an issue or contact me via GitHub.

## 👤 Author
This project was created by **Kilian** as part of independent study in Medical Informatics.
The software was fully developed in C++ using modern programming techniques.

