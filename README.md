# 🩺 Electronic Patient Record – C++ Project

## 🧠 Project Goal

This project simulates a simplified **electronic patient record** (EPR) system using C++. It was created to practice object-oriented programming, file handling, and structured data management. The software allows storing, editing, and displaying patient data, including appointments, diagnoses, medications, invoices, and more.

---

## 🛠️ Concepts Used

- Classes & Inheritance
- Access specifiers (`private`, `protected`, `public`)
- STL containers: `std::vector`, `std::string`
- Dynamic memory management
- Friend functions and operator overloading (`operator<<`)
- File input/output (`fstream`)
- Text-based user menu
- Optional: simple role system (e.g. Doctor, Admin, Staff)

---

## 📋 Features Overview

### 🔹 Patient Record Management
- **Public Info**: name, gender, birth date, patient ID, room number
- **Private Info**:
  - Diagnoses (medical findings)
  - Medications (including dosage)
  - Appointments (past & upcoming)
  - Assigned doctor
  - Invoices (amount, purpose, status)

### 🔹 Core Functionalities
- Create new patient
- View patient details (public/private based on role)
- Add diagnoses, medications, and appointments
- Assign/change doctor
- Create and update invoice status
- Search patients by name or ID
- Save/load patient records to/from file

### 🔹 Optional Extensions
- Simple login simulation with roles
- Export a patient record to a readable `.txt` file
- Statistics (e.g. most common diseases, total revenue)
- Sorting by room, last name, or next appointment

---

## 📦 Project Structure
```
/ElectronicPatientRecord/
│
├── src/
│ ├── main.cpp
│ ├── Patient.h / Patient.cpp
│ ├── Appointment.h / Appointment.cpp
│ ├── Medication.h / Doctor.h / Invoice.h ...
│
├── data/
│ ├── patient_001.txt
│ ├── patient_002.txt
│
├── README.md
└── Makefile (optional)
```

## 💡 Future Ideas
- Save records in XML or JSON
- Build a Qt or web-based GUI
- ICD-10 integration via external API
- Encrypt private patient data for security

## 👤 Author
This project was created by *Kilian* as part of independent study in Medical Informatics.
The software was fully developed in C++ using modern programming techniques.

