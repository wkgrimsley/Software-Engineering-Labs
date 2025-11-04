#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
//github copilot used to help with algorithms to perform the addition 
bool isDigit(char c) {
    return c>= '0' && c<= '9';
}
//check if the values are actually doubles or not - checks if there is a decimal, + or -, return false if it is not valid
bool isDouble(const std::string& str){
    bool decimal=false;

    if (str.empty()) return false;

    if (str[0]!='-' && !isDigit(str[0]) && str[0]!='+') return false;

    if (str.length()==1 && str[0]=='-') return false;

    for (size_t i = 1; i<str.length(); i++){
        if (str[i]=='.'){
            if (decimal) return false;
            decimal = true;
        }else if (!isDigit(str[i])){
            return false;
        }
    }
    return true;
}
//equalize the decimal places by padding zeros to make it easier to add
void equalDecimal(std::string& num1, std::string& num2){
    size_t dec1 = num1.find('.');
    size_t dec2 = num2.find('.');

    if (dec1==std::string::npos){
        num1+= ".0";
        dec1 = num1.length()-2;
    }
    if (dec2==std::string::npos){
        num2+=".0";
        dec2 = num2.length()-2;
    }
    while (num1.length() - dec1 < num2.length() - dec2){
        num1+="0";
    }
    while (num2.length() - dec2 < num1.length() - dec1){
        num2+="0";
    }
}

// Compare magnitudes of two non-signed decimal strings. Returns 1 if a>b, 0 if equal, -1 if a<b
//idea from github copilot - i added code with help from it
int compareMagnitude(std::string a, std::string b) {
    if (a.size() == 0) a = "0";
    if (b.size() == 0) b = "0";
    if (a.find('.') == std::string::npos) a += ".0";
    if (b.find('.') == std::string::npos) b += ".0";
    size_t da = a.find('.');
    size_t db = b.find('.');
    std::string ia = a.substr(0, da);
    std::string ib = b.substr(0, db);
    std::string da_part = a.substr(da + 1);
    std::string db_part = b.substr(db + 1);
    // strip leading zeros from integer parts
    while (ia.size() > 1 && ia[0] == '0') ia.erase(0, 1);
    while (ib.size() > 1 && ib[0] == '0') ib.erase(0, 1);
    // pad decimal parts
    while (da_part.size() < db_part.size()) da_part.push_back('0');
    while (db_part.size() < da_part.size()) db_part.push_back('0');
    if (ia.size() != ib.size()) return (ia.size() > ib.size()) ? 1 : -1;
    if (ia != ib) return (ia > ib) ? 1 : -1;
    if (da_part != db_part) return (da_part > db_part) ? 1 : -1;
    return 0;
}

//Subtract magnitudes a - b (both non-signed decimal strings) assuming a >= b. Returns positive result string.
//code simplified by github copilot
std::string subtractMagnitudes(std::string a, std::string b) {
    if (a.find('.') == std::string::npos) a += ".0";
    if (b.find('.') == std::string::npos) b += ".0";
    size_t da = a.find('.');
    size_t db = b.find('.');
    std::string ia = a.substr(0, da);
    std::string ib = b.substr(0, db);
    std::string da_part = a.substr(da + 1);
    std::string db_part = b.substr(db + 1);
    // pad decimal parts
    while (da_part.size() < db_part.size()) da_part.push_back('0');
    while (db_part.size() < da_part.size()) db_part.push_back('0');
    // combine into whole-digit strings
    std::string as = ia + da_part;
    std::string bs = ib + db_part;
    // pad leading zeros on shorter
    while (bs.size() < as.size()) bs = "0" + bs;

    int borrow = 0;
    std::string res;
    for (int i = (int)as.size() - 1; i >= 0; --i) {
        int daig = (as[i] - '0') - borrow;
        int dbig = (bs[i] - '0');
        if (daig < dbig) {
            daig += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        int digit = daig - dbig;
        res.insert(res.begin(), char('0' + digit));
    }

    // insert decimal point
    size_t decPlaces = da_part.size();
    if (decPlaces > 0) {
        if (res.size() <= decPlaces) {
            // need leading zeros
            res = std::string(decPlaces - res.size() + 1, '0') + res;
        }
        res.insert(res.size() - decPlaces, ".");
    }

    // trim leading zeros in integer part
    size_t dotPos = res.find('.');
    std::string intPart = (dotPos == std::string::npos) ? res : res.substr(0, dotPos);
    std::string decPart = (dotPos == std::string::npos) ? std::string() : res.substr(dotPos + 1);
    while (intPart.size() > 1 && intPart[0] == '0') intPart.erase(0, 1);
    // trim trailing zeros in decimal part
    while (!decPart.empty() && decPart.back() == '0') decPart.pop_back();
    std::string finalRes = intPart;
    if (!decPart.empty()) finalRes += "." + decPart;
    if (finalRes.empty()) return "0";
    return finalRes;
}
//add the doubles (strings)
std::string addDoubles(std::string num1, std::string num2) {
    // remove leading plus signs
    if (!num1.empty() && num1[0] == '+') num1 = num1.substr(1);
    if (!num2.empty() && num2[0] == '+') num2 = num2.substr(1);

    bool neg1 = (!num1.empty() && num1[0] == '-');
    bool neg2 = (!num2.empty() && num2[0] == '-');
    if (neg1) num1 = num1.substr(1);
    if (neg2) num2 = num2.substr(1);

    // both positive: add
    if (!neg1 && !neg2) {
        // ensure decimal
        if (num1.find('.') == std::string::npos) num1 += ".0";
        if (num2.find('.') == std::string::npos) num2 += ".0";
        size_t d1 = num1.find('.');
        size_t d2 = num2.find('.');
        std::string int1 = num1.substr(0, d1);
        std::string int2 = num2.substr(0, d2);
        std::string dec1_part = num1.substr(d1 + 1);
        std::string dec2_part = num2.substr(d2 + 1);
        while (dec1_part.size() < dec2_part.size()) dec1_part.push_back('0');
        while (dec2_part.size() < dec1_part.size()) dec2_part.push_back('0');
        // add decimal parts
        std::string dec_result;
        int carry = 0;
        for (int i = (int)dec1_part.size() - 1; i >= 0; --i) {
            int sum = (dec1_part[i] - '0') + (dec2_part[i] - '0') + carry;
            carry = sum / 10;
            dec_result.insert(dec_result.begin(), char('0' + (sum % 10)));
        }
        // pad integer parts
        while (int1.size() < int2.size()) int1 = "0" + int1;
        while (int2.size() < int1.size()) int2 = "0" + int2;
        std::string int_result;
        for (int i = (int)int1.size() - 1; i >= 0; --i) {
            int sum = (int1[i] - '0') + (int2[i] - '0') + carry;
            carry = sum / 10;
            int_result.insert(int_result.begin(), char('0' + (sum % 10)));
        }
        if (carry > 0) int_result.insert(int_result.begin(), '0' + carry);
        // combine and trim
        std::string result = int_result;
        if (!dec_result.empty()) result += "." + dec_result;
        // trim trailing zeros in decimal
        while (result.size() > 0 && result.back() == '0' && result.find('.') != std::string::npos) result.pop_back();
        if (!result.empty() && result.back() == '.') result.pop_back();
        if (result.empty()) return "0";
        return result;
    }

    // both negative: result is negative of sum of magnitudes
    if (neg1 && neg2) {
        std::string sum = addDoubles(num1, num2); // recursive call for positive add
        if (sum == "0") return "0";
        return std::string("-") + sum;
    }

    // signs differ: subtract smaller magnitude from larger magnitude
    // determine which magnitude is larger
    int cmp = compareMagnitude(num1, num2);
    if (cmp == 0) return "0";
    if (neg1 && !neg2) {
        // (-num1) + num2  => num2 - num1
        if (cmp >= 0) {
            // |num1| >= |num2| => result negative
            std::string res = subtractMagnitudes(num1, num2);
            if (res == "0") return "0";
            return std::string("-") + res;
        } else {
            // |num2| > |num1| => positive
            return subtractMagnitudes(num2, num1);
        }
    } else { // !neg1 && neg2  => num1 + (-num2) => num1 - num2
        if (cmp >= 0) {
            return subtractMagnitudes(num1, num2);
        } else {
            std::string res = subtractMagnitudes(num2, num1);
            if (res == "0") return "0";
            return std::string("-") + res;
        }
    }
    }
//remove whitespace - trim the doubles
std::string trim(const std::string& str){
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}
//process the numberpair to be used
void processNumberPair(const std::string& line, int pairNumber) {
    size_t spacePos = line.find_first_of(" \t");
    if (spacePos != std::string::npos) {
        std::string num1 = trim(line.substr(0, spacePos));
        std::string num2 = trim(line.substr(spacePos + 1));
        //check if they're doubles and then say what the numbers are
        if (isDouble(num1) && isDouble(num2)) {
            std::cout << "\nPair " << pairNumber << ":" << std::endl;
            std::cout << "First number: " << num1 << std::endl;
            std::cout << "Second number: " << num2 << std::endl;
            std::string result = addDoubles(num1, num2);
            std::cout << "Sum: " << result << std::endl;
        } else { //case for invalid number pair
            std::cout << "\nPair " << pairNumber << ": Invalid number format" << std::endl;
        }
    } else { //case for invalid format
        std::cout << "\nPair " << pairNumber << ": Invalid line format" << std::endl;
    }
}
//open the file and get the pairs - then process them and perform the addition
bool readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cout << "Error: File not found " << filename << std::endl;
        return false;
    }

    std::string line;
    int pairCount = 0;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            pairCount++;
            processNumberPair(line, pairCount);
        }
    }
    
    if (pairCount == 0) {
        std::cout << "No number pairs found in the file." << std::endl;
    } else {
        std::cout << "\nProcessed " << pairCount << " pairs of numbers." << std::endl;
    }
    
    file.close();
    return true;
}
//pass the file to readFromFile() function
int main() {
    std::string filename;
    
    std::cout << "Enter the filename to read numbers from: ";
    std::cin >> filename;
    
    readFromFile(filename);
    
    return 0;

}
