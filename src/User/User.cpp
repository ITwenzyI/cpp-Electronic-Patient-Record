#include "User.hpp"

User::User(std::string user_id,
           std::string role,
           std::string firstName,
           std::string lastName,
           std::string dateOfBirth,
           std::string gender,
           std::string nationality,
           std::string address,
           std::string phoneNumber,
           std::string email,
           std::string insuranceID,
           std::string insuranceType)
    : user_id(std::move(user_id)),
      role(std::move(role)),
      firstName(std::move(firstName)),
      lastName(std::move(lastName)),
      dateOfBirth(std::move(dateOfBirth)),
      gender(std::move(gender)),
      nationality(std::move(nationality)),
      address(std::move(address)),
      phoneNumber(std::move(phoneNumber)),
      email(std::move(email)),
      insuranceID(std::move(insuranceID)),
      insuranceType(std::move(insuranceType)) {}




User::~User() = default;





// Getters

std::string User::getFirstName() const {
    return firstName;
}

std::string User::getLastName() const {
    return lastName;
}

std::string User::getRole() const {
    return role;
}

std::string User::getID() const {
    return user_id;
}


// Setters

void User::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void User::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}


// Updates a specific field in info.txt of the id
void User::update_field_in_file(const std::string& id, const std::string& field, const std::string& newInput) {

    // Determine the correct file path based on the ID (Example: P0001 = Patients/P0001/info.txt)
    std::string path = get_file_path_from_id(id);

    if (path.empty()) {
        std::cerr << "Invalid ID: " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        std::cerr << "Could not open file: " << path << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool updated = false;

    // Read each line and replace the target field with the new Input
    while (std::getline(inFile, line)) {
        // Check if the line starts with the field name (Example: "Address: ")
        if (line.substr(0, field.length() + 2) == field + ": ") { // +2, because of the ": "
            line = field + ": " + newInput; // Update the line with the new Input
            updated = true;
        }
        lines.push_back(line); // Store the lines in the vector (modified or not)
    }

    inFile.close();

    // If the field was not found, inform the user and stop
    if (!updated) {
        std::cerr << "Field \"" << field << "\" not found in file.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    // Overwrite new File
    std::ofstream outFile(path);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << path << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    // Write all lines back to the file, including the updated one
    for (const auto& newline : lines) {
        outFile << newline << '\n';
    }

    outFile.close();
    std::cout << field << " successfully updated.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}



// Adds an Extra Info in info.txt for the ID
void User::add_extra_info(const std::string &id) {

    // Determine the correct file path based on the ID (Example: P0001 = Patients/P0001/info.txt)
    std::string path = get_file_path_from_id(id);

    if (path.empty()) {
        std::cerr << "Invalid ID: " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::string extra_info;

    std::cout << "ID: " << id << std::endl;
    std::cout << "Enter the Extra Info: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, extra_info);
    std::cout << std::endl;

    // Final format: [2025-06-15] Extra Info.
    std::string newLine = "[" + getDate() + "] " + extra_info + "\n";

    std::ofstream out(path, std::ios::app);  // append mode

    if (!out.is_open()) {
        std::cerr << "Could not open file for writing.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    out << newLine << '\n';
    out.close();

    std::cout << "Extra Info added:\n" << newLine << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(2));
}







