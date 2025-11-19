/*
Name of Program: EECS348 Assignment 7
Brief Description: Connect to SQL database and create the tables given from lab12
Then perform the SQL commands given in the assignment in C++
Inputs: Tables from Lab12
Outputs: Results of SQL commands printed to console
All Collaborators: None
Other Sources: ChatGPT, Stack Exchange
Author's Full Name: William Grimsley
Creation Date: November 19 2025
*/

//include headers
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>
using namespace std;
int main(){

	//connect to mysql  database
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res = nullptr;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://mysql.eecs.ku.edu:3306", "348f25_w679g525", "caexa3Ee");
	con->setSchema("348f25_w679g525");
	stmt = con->createStatement();
	//use my database
	stmt->execute("USE 348f25_w679g525");
	//drop the tables to ensure new output each time
	//this helps with testing
	stmt->execute("DROP TABLE IF EXISTS Course7");
	stmt->execute("DROP TABLE IF EXISTS Enrollment7");
	stmt->execute("DROP TABLE IF EXISTS Faculty7");
	stmt->execute("DROP TABLE IF EXISTS Offering7");
	stmt->execute("DROP TABLE IF EXISTS Student7");
	//create course7 table - ChatGPT helped with the insert statements by allowing me to feed it the info and it would format it for me
	stmt->execute("CREATE TABLE Course7 ("
				  "courseNo CHAR(6), "
				  "CrsDesc VARCHAR(50), "
				  "CrsUnits INTEGER, "
				  "PRIMARY KEY (courseNo))");
		//insert into course7 table
	stmt->execute("INSERT INTO Course7 VALUES "
				  "('FIN300', 'FUNDAMENTALS OF FINANCE', 4), "
				  "('FIN450','PRINCIPLES OF INVESTMENTS',4), "
				  "('FIN480','CORPORATE FINANCE',4), "
				  "('IS320','FUNDAMENTALS OF BUSINESS PROGRAMMING',4 ),"
				  "( 'IS460','SYSTEMS ANALYSIS',4),"
				  "( 'IS470','BUSINESS DATA COMMUNICATIONS',4),"
				  "( 'IS480','FUNDAMENTALS OF DATABASE MANAGEMENT',4)");
	//create enrollment7 table
	stmt->execute("CREATE TABLE Enrollment7("
              "OfferNo INTEGER, "
              "StdNo CHAR(11), "
              "EnrGrade DECIMAL(3,2), "
              "PRIMARY KEY (OfferNo, StdNo))");
		//insert into enrollment7 table
	stmt->execute("INSERT INTO Enrollment7 VALUES"
				"(1234, '123-45-6789', 3.30), "
				"(1234, '234-56-7890', 3.50), "
				"(1234, '345-67-8901', 3.20), "
				"(1234, '456-78-9012', 3.10), "
				"(1234, '567-89-0123', 3.80), "
				"(1234, '678-90-1234', 3.40), "
				"(4321, '123-45-6789', 3.50), "
				"(4321, '124-56-7890', 3.20), "
				"(4321, '789-01-2345', 3.50), "
				"(4321, '876-54-3210', 3.10), "
				"(4321, '890-12-3456', 3.40), "
				"(4321, '901-23-4567', 3.10), "
				"(5555, '123-45-6789', 3.20), "
				"(5555, '124-56-7890', 2.70), "
				"(5678, '123-45-6789', 3.20), "
				"(5678, '234-56-7890', 2.80), "
				"(5678, '345-67-8901', 3.30), "
				"(5678, '456-78-9012', 3.40), "
				"(5678, '567-89-0123', 2.60), "
				"(5679, '123-45-6789', 2.00), "
				"(5679, '124-56-7890', 3.70), "
				"(5679, '678-90-1234', 3.30), "
				"(5679, '789-01-2345', 3.80), "
				"(5679, '890-12-3456', 2.90), "
				"(5679, '901-23-4567', 3.10), "
				"(6666, '234-56-7890', 3.10), "
				"(6666, '567-89-0123', 3.60), "
				"(7777, '876-54-3210', 3.40), "
				"(7777, '890-12-3456', 3.70), "
				"(7777, '901-23-4567', 3.40), "
				"(9876, '124-56-7890', 3.50), "
				"(9876, '234-56-7890', 3.20), "
				"(9876, '345-67-8901', 3.20), "
				"(9876, '456-78-9012', 3.40), "
				"(9876, '567-89-0123', 2.60), "
				"(9876, '678-90-1234', 3.30), "
				"(9876, '901-23-4567', 4.00), "
				"(1111, '901-23-4567', 0.00)");
	//create faculty7 table
	stmt->execute("CREATE TABLE Faculty7("
				"FacNo CHAR(11), "
				"FacFirstName VARCHAR(30), "
				"FacLastName VARCHAR(30), "
				"FacCity VARCHAR(30), "
				"FacState CHAR(2), "
				"FacDept CHAR(10), "
				"FacRank CHAR(4), "
				"FacSalary DECIMAL(10,2), "
				"FacSupervisor CHAR(11), "
				"FacHireDate DATE, "
				"FacZipCode CHAR(10), "
				"PRIMARY KEY (FacNo))");
		//insert into faculty7 table
	stmt->execute("INSERT INTO Faculty7 VALUES"
				"('543-21-0987','VICTORIA','EMMANUEL','BOTHELL','WA','MS','PROF',120000.00,NULL,'2008-04-15','98011-2242'), "
				"('765-43-2109','NICKI','MACON','BELLEVUE','WA','FIN','PROF',65000.00,NULL,'2009-04-11','98015-9945'), "
				"('654-32-1098','LEONARD','FIBON','SEATTLE','WA','MS','ASSC',70000.00,'543-21-0987','2006-05-01','98121-0094'), "
				"('098-76-5432','LEONARD','VINCE','SEATTLE','WA','MS','ASST',35000.00,'654-32-1098','2007-04-10','98111-9921'), "
				"('876-54-3210','CRISTOPHER','COLAN','SEATTLE','WA','MS','ASST',40000.00,'654-32-1098','2011-03-01','98114-1332'), "
				"('987-65-4321','JULIA','MILLS','SEATTLE','WA','FIN','ASSC',75000.00,'765-43-2109','2012-03-15','98114-9954')");
	//create offering7 table
	stmt->execute("CREATE TABLE Offering7("
				"OfferNo INTEGER, "
				"CourseNo CHAR(6), "
				"OffTerm CHAR(6), "
				"OffYear INTEGER, "
				"OffLocation VARCHAR(30), "
				"OffTime VARCHAR(10), "
				"FacNo CHAR(11), "
				"OffDays CHAR(6) DEFAULT 'MW', "
				"PRIMARY KEY (OfferNo))");
		//insert into offering7 table
	stmt->execute("INSERT INTO Offering7 VALUES"
				"(1111,'IS320','SUMMER',2020,'BLM302','10:30:00',NULL,'MW'), "
				"(1234,'IS320','FALL',2019,'BLM302','10:30:00','098-76-5432','MW'), "
				"(2222,'IS460','SUMMER',2019,'BLM412','13:30:00',NULL,'TTH'), "
				"(3333,'IS320','SPRING',2020,'BLM214','08:30:00','098-76-5432','MW'), "
				"(4321,'IS320','FALL',2019,'BLM214','15:30:00','098-76-5432','TTH'), "
				"(4444,'IS320','WINTER',2020,'BLM302','15:30:00','543-21-0987','TTH'), "
				"(5555,'FIN300','WINTER',2020,'BLM207','08:30:00','765-43-2109','MW'), "
				"(5678,'IS480','WINTER',2020,'BLM302','10:30:00','987-65-4321','MW'), "
				"(5679,'IS480','SPRING',2020,'BLM412','15:30:00','876-54-3210','TTH'), "
				"(6666,'FIN450','WINTER',2020,'BLM212','10:30:00','987-65-4321','TTH'), "
				"(7777,'FIN480','SPRING',2020,'BLM305','13:30:00','765-43-2109','MW'), "
				"(8888,'IS320','SUMMER',2020,'BLM405','13:30:00','654-32-1098','MW'), "
				"(9876,'IS460','SPRING',2020,'BLM307','13:30:00','654-32-1098','TTH')");
	//create student7 table
	stmt->execute("CREATE TABLE Student7("
              "StdNo CHAR(11), "
              "StdFirstName VARCHAR(50), "
              "StdLastName VARCHAR(50), "
              "StdCity VARCHAR(50), "
              "StdState CHAR(2), "
              "StdZip CHAR(10), "
              "StdMajor CHAR(6), "
              "StdClass CHAR(6), "
              "StdGPA DECIMAL(3,2) DEFAULT 0, "
              "PRIMARY KEY (StdNo))");
	//insert into student7 table
	stmt->execute("INSERT INTO Student7 VALUES"
              "('123-45-6789','HOMER','WELLS','SEATTLE','WA','98121-1111','IS','FR',3.00), "
              "('124-56-7890','BOB','NORBERT','BOTHELL','WA','98011-2121','FIN','JR',2.70), "
              "('234-56-7890','CANDY','KENDALL','TACOMA','WA','99042-3321','ACCT','JR',3.50), "
              "('345-67-8901','WALLY','KENDALL','SEATTLE','WA','98123-1141','IS','SR',2.80), "
              "('456-78-9012','JOE','ESTRADA','SEATTLE','WA','98121-2333','FIN','SR',3.20), "
              "('567-89-0123','MARIAH','DODGE','SEATTLE','WA','98114-0021','IS','JR',3.60), "
              "('678-90-1234','TESS','DODGE','REDMOND','WA','98116-2344','ACCT','SO',3.30), "
              "('789-01-2345','ROBERTO','MORALES','SEATTLE','WA','98121-2212','FIN','JR',2.50), "
              "('876-54-3210','CRISTOPHER','COLAN','SEATTLE','WA','98114-1332','IS','SR',4.00), "
              "('890-12-3456','LUKE','BRAZZI','SEATTLE','WA','98116-0021','IS','SR',2.20), "
              "('901-23-4567','WILLIAM','PILGRIM','BOTHELL','WA','98113-1885','IS','SO',3.80)");

	//perform queries from assignment - each cout represents a different query
	//all res = stmt->executeQuery(...) lines execute the queries
	//all while(res->next()) loops go through the result set and print the results
	
	cout << "Students majoring in IS:\n";
	res = stmt->executeQuery("SELECT * FROM Student7 WHERE StdMajor = 'IS';");
	while (res->next()) {
		std::cout << "StdNo: " << res->getString("StdNo") << ", ";
		std::cout << "StdFirstName: " << res->getString("StdFirstName") << ", ";
		std::cout << "StdLastName: " << res->getString("StdLastName") << ", ";
		std::cout << "StdCity: " << res->getString("StdCity") << ", ";
		std::cout << "StdState: " << res->getString("StdState") << ", ";
		std::cout << "StdZip: " << res->getString("StdZip") << ", ";
		std::cout << "StdMajor: " << res->getString("StdMajor") << ", ";
		std::cout << "StdClass: " << res->getString("StdClass") << ", ";
		std::cout << "StdGPA: " << res->getDouble("StdGPA") << std::endl;
	}
	delete res;

	cout << "\nStudents who have enrolled in more than two courses:\n";

    res = stmt->executeQuery(
		"SELECT StdNo "
		"FROM Enrollment7 "
		"GROUP BY StdNo "
		"HAVING COUNT(OfferNo) > 2"
	);

	while (res->next()) {
		cout << "Student Number: " << res->getString("StdNo") << endl;
	}

	delete res;

	cout << "\nProfessors employed more than 15 years (hired in 2010 or earlier):\n";

    res = stmt->executeQuery(
		"SELECT FacFirstName, FacLastName "
		"FROM Faculty7 "
		"WHERE FacHireDate <= '2010-12-31'"
	);

	while (res->next()) {
		cout << "First Name: " << res->getString("FacFirstName") << endl
			<< "Last Name: "  << res->getString("FacLastName")  << endl
			<< "----------------------------------------" << endl;
	}

	delete res;

	cout << "\nCourses offered in Summer 2020:\n";

    res = stmt->executeQuery(
		"SELECT CourseNo "
		"FROM Offering7 "
		"WHERE OffTerm = 'SUMMER' AND OffYear = 2020"
	);

	while (res->next()) {
		cout << "Course Number: " << res->getString("CourseNo") << endl;
	}

	delete res;

	cout << "\nProfessors living in ZIP code 98114:\n";

    res = stmt->executeQuery(
		"SELECT FacFirstName, FacLastName "
		"FROM Faculty7 "
		"WHERE FacZipCode LIKE '98114%'"
	);

	while (res->next()) {
		cout << "First Name: " << res->getString("FacFirstName") << endl
			<< "Last Name: "  << res->getString("FacLastName")  << endl
			<< "----------------------------------------" << endl;
	}

	delete res;

	cout << "\nSecond-highest GPA:\n";

    res = stmt->executeQuery(
		"SELECT MAX(StdGPA) AS SecondHighestGPA "
		"FROM Student7 "
		"WHERE StdGPA < (SELECT MAX(StdGPA) FROM Student7)"
	);

	if (res->next()) {
		cout << "Second-highest GPA: " << res->getDouble("SecondHighestGPA") << endl;
	}

	delete res;

	cout << "\nIndividuals in both Student and Faculty tables:\n";

	res = stmt->executeQuery(
	"SELECT s.StdFirstName, s.StdLastName "
	"FROM Student7 s "
	"JOIN Faculty7 f ON s.StdFirstName = f.FacFirstName AND s.StdLastName = f.FacLastName"
	);

	while (res->next()) {
		cout << "First Name: " << res->getString("StdFirstName") << endl
			<< "Last Name: "  << res->getString("StdLastName")  << endl
			<< "----------------------------------------" << endl;
	}

	delete res;

	cout << "\nStudent course counts:\n";

	res = stmt->executeQuery(
		"SELECT s.StdNo, s.StdFirstName, s.StdLastName, COUNT(e.OfferNo) AS NumCourses "
		"FROM Student7 s "
		"LEFT JOIN Enrollment7 e ON s.StdNo = e.StdNo "
		"GROUP BY s.StdNo, s.StdFirstName, s.StdLastName "
	);

	while (res->next()) {
		cout << "StdNo: "       << res->getString("StdNo") << endl
			<< "First Name: "  << res->getString("StdFirstName") << endl
			<< "Last Name: "   << res->getString("StdLastName") << endl
			<< "Number of Courses: " << res->getInt("NumCourses") << endl
			<< "----------------------------------------" << endl;
	}

	delete res;

	cout << "\nTop three highest-paid professors:\n";

	res = stmt->executeQuery(
		"SELECT FacFirstName, FacLastName, FacSalary "
		"FROM Faculty7 "
		"ORDER BY FacSalary DESC "
		"LIMIT 3"
	);

	while (res->next()) {
		cout << "First Name: " << res->getString("FacFirstName") << endl
			<< "Last Name: "  << res->getString("FacLastName")  << endl
			<< "Salary: "     << res->getDouble("FacSalary")    << endl
			<< "----------------------------------------" << endl;
	}

	delete res;

	cout << "\nStudents with no enrollments:\n";

	res = stmt->executeQuery(
		"SELECT * "
		"FROM Student7 s "
		"LEFT JOIN Enrollment7 e ON s.StdNo = e.StdNo "
		"WHERE e.StdNo IS NULL"
	);

	while (res->next()) {
		cout << "StdNo: "       << res->getString("StdNo") << endl
			<< "First Name: "  << res->getString("StdFirstName") << endl
			<< "Last Name: "   << res->getString("StdLastName") << endl
			<< "City: "        << res->getString("StdCity") << endl
			<< "State: "       << res->getString("StdState") << endl
			<< "Zip: "         << res->getString("StdZip") << endl
			<< "Major: "       << res->getString("StdMajor") << endl
			<< "Class: "       << res->getString("StdClass") << endl
			<< "GPA: "         << res->getDouble("StdGPA") << endl
			<< "----------------------------------------" << endl;
	}

	delete res;

	// Insert new student
	stmt->execute(
		"INSERT INTO Student7(StdNo, StdFirstName, StdLastName, StdCity, StdState, StdZip, StdMajor, StdClass, StdGPA) "
		"VALUES ('888-88-8888','Alice','Smith','Topeka','KS','66610','CS','JR',3.85)"
	);

	// Display updated table
	cout << "\nUpdated Student table:\n";

	res = stmt->executeQuery("SELECT * FROM Student7;");

	while (res->next()) {
		cout << "StdNo: "       << res->getString("StdNo") << endl
			<< "First Name: "  << res->getString("StdFirstName") << endl
			<< "Last Name: "   << res->getString("StdLastName") << endl
			<< "City: "        << res->getString("StdCity") << endl
			<< "State: "       << res->getString("StdState") << endl
			<< "Zip: "         << res->getString("StdZip") << endl
			<< "Major: "       << res->getString("StdMajor") << endl
			<< "Class: "       << res->getString("StdClass") << endl
			<< "GPA: "         << res->getDouble("StdGPA") << endl
			<< "----------------------------------------" << endl;
	}

	delete res;

	// Update Bob Norbert
	stmt->execute(
		"UPDATE Student7 "
		"SET StdCity = 'Overland Park', StdZip = '66204' "
		"WHERE StdFirstName = 'Bob' AND StdLastName = 'Norbert'"
	);

	// Display updated table
	cout << "\nStudent table after updating Bob Norbert:\n";

	res = stmt->executeQuery("SELECT * FROM Student7");

	while (res->next()) {
		cout << "StdNo: "       << res->getString("StdNo") << endl
			<< "First Name: "  << res->getString("StdFirstName") << endl
			<< "Last Name: "   << res->getString("StdLastName") << endl
			<< "City: "        << res->getString("StdCity") << endl
			<< "State: "       << res->getString("StdState") << endl
			<< "Zip: "         << res->getString("StdZip") << endl
			<< "Major: "       << res->getString("StdMajor") << endl
			<< "Class: "       << res->getString("StdClass") << endl
			<< "GPA: "         << res->getDouble("StdGPA") << endl
			<< "----------------------------------------" << endl;
	}
	//res is deleted each time after it is used for the command
	delete res;
	//clear memory
	delete stmt;
	delete con;
}
