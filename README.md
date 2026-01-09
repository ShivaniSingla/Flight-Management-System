# Flight Management System (C)

## Overview

This is my **first C programming project**, built to practice core C concepts such as **structures, file handling, control flow, and basic input/output**. The application is a **console-based Flight Management System** that allows staff to add flight details and customers to search flight schedules using a CSV file as storage.

This project is intentionally simple and educational. It is **not production-ready** and does **not use a database**.

---

## Features

* Role-based access (Customer / Staff)
* Staff can:

  * Add flight details
  * Store flight data in a CSV file
* Customers can:

  * Search flight schedules by flight number
* Uses C structures to model:

  * Date
  * Time
  * City
  * Airline (flight)

---

## Technologies Used

* **Language:** C
* **Concepts:**

  * Structures (struct)
  * File handling (fopen, fgets, fprintf)
  * String handling
  * Conditional logic and loops
* **Storage:** CSV file (no database)

---

## Project Structure


Flight-Management-System/
├── src/
│   └── flight.c
├── data/
│   └── flight_data.csv
├── README.md


---

## How to Compile and Run

### Compile

From the project root directory:

```bash
gcc src/flight.c -o flight
```

### Run

```bash
./flight
```

(On Windows)

```powershell
flight.exe
```

---

## Usage

1. Start the program
2. Choose role:
   * Customer (1)
   * Staff (0)
3. Staff must enter a security code (hardcoded for demonstration)
4. Staff can add flight data
5. Customers can search flights using flight number

---

## Limitations

* No input validation for incorrect formats
* Security code is hardcoded (for learning only)
* CSV file is used instead of a database
* No deletion or update of existing flights

---

## Learning Outcome

Through this project, I learned:

* How to design programs using structures
* How to store and retrieve structured data using files
* How to organize a small C project
* How to handle basic user interaction in C

---

## Future Improvements

* Add search by city and date
* Improve input validation
* Replace CSV storage with a database
* Add seat booking functionality

---
