//
// Created by User on 07.06.2025.
//

#ifndef UTILS_HPP
#define UTILS_HPP

/* Todo
 * Patient ID function
*/

#include <string>

std::string getDate();
std::string getTime();
int random_number(int min, int max);

int get_patient_id();
void update_patient_id(int old_id);



#endif //UTILS_HPP
