# <div align="center">Hey 👋, I'm The-R4V3N!</div>  

----

## <div align="center"> Connect with me  

<div align="center">
 <a href="https://github.com/The-R4V3N" target="_blank">
<img src=https://img.shields.io/badge/github-%2324292e.svg?&style=for-the-badge&logo=github&logoColor=white alt=github style="margin-bottom: 5px;" />
<a href="https://dev.to/ther4v3n" target="_blank">
<img src=https://img.shields.io/badge/dev.to-%2308090A.svg?&style=for-the-badge&logo=dev.to&logoColor=white alt=devto style="margin-bottom: 5px;" />
</a>
<a href="https://linkedin.com/in/oliver-joisten" target="_blank">
<img src=https://img.shields.io/badge/linkedin-%231E77B5.svg?&style=for-the-badge&logo=linkedin&logoColor=white alt=linkedin style="margin-bottom: 5px;" />
</a>
<a href="https://www.facebook.com/oliver.joisten" target="_blank">
<img src=https://img.shields.io/badge/facebook-%232E87FB.svg?&style=for-the-badge&logo=facebook&logoColor=white alt=facebook style="margin-bottom: 5px;" />
</a>

</a>  
</div>

## Welcome! Glad to see you here  
# Vehicle Manufacturer-Dealers Program

![License](https://img.shields.io/badge/license-MIT-blue.svg)

This program implements a thread-safe and synchronized vehicle manufacturer-dealers program in C++. The program simulates the interaction between multiple manufacturers and dealerships in a controlled environment. It ensures that all operations are properly synchronized to prevent race conditions and maintain data integrity.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- Simulates the interaction between vehicle manufacturers and dealerships.
- Provides thread-safe and synchronized operations.
- Prevents race conditions and ensures data integrity.
- Supports manufacturers and dealerships operating at different rates.
- Implements classes for Vehicle, Car, and Truck with property printing functions.
- Utilizes a circular buffer to store vehicles.
- Customizable capacity of the circular buffer.
- Multiple dealers operating as threads.
- Supports a variable number of dealers.

## Getting Started

These instructions will help you compile and run the program on your local machine for development and testing purposes.

### Prerequisites

To compile and run this program, you need to have a C++ compiler supporting C++11 or higher installed on your system.

### Compiling

You can compile the program by executing the following command in the terminal:
```
 g++ -std=c++11 -o vehicle_manufacturer_dealers main.cpp
```
### Running
Once the program is compiled, you can run it using the following command:

```
./vehicle_manufacturer_dealers <capacity> <num_dealers>
 ```
Note: Replace <capacity> with the desired capacity of the circular buffer (must be at least 8) and <num_dealers> with the desired number of dealers (must be at least 2).

### Usage
This program provides a simulation of a vehicle manufacturer-dealers system. The main components of the system are the Manufacturer and Dealer classes. The manufacturers produce vehicles, and the dealerships receive and sell those vehicles.

The program implements a circular buffer as the warehouse to store vehicles. The circular buffer has a specified capacity, which is provided as a command-line argument when running the program.

The manufacturers randomly produce cars and trucks and store them in the warehouse. If the warehouse is full, the manufacturing thread will sleep until space becomes available.

The dealers retrieve vehicles from the warehouse one at a time and print all the properties of the vehicle to the terminal. If the warehouse is empty, the dealer threads will sleep until a vehicle is manufactured by the manufacturer thread.

The program supports manufacturers and dealers operating at different rates, ensuring correct functionality in scenarios where either the manufacturer is faster than the dealers or the dealers are faster than the manufacturer.

The program also includes the following classes:

- Vehicle: Represents a generic vehicle with common properties and functions.
- Car: Represents a car and extends the Vehicle class.
- Truck: Represents a truck and extends the Vehicle class.

 Both the Car and Truck classes have functions to print their properties.

### Contributing
Contributions to this project are welcome and encouraged. If you find any issues or have suggestions for improvement, please open a new issue or submit a pull request. Any feedback you have is highly appreciated.

License
This project is licensed under the MIT License. Feel free to use, modify, or distribute this code for personal or commercial purposes.

- 👨‍💻 All about me is at [My Website](https://www.oliver-joisten.se/)

<div align="center">
<img src="https://komarev.com/ghpvc/?username=the-r4v3n&&style=flat-square" align="center" />
&emsp;
<a href="https://paypal.me/paypal.me/TheR4V3N" target="_blank" style="display: inline-block;">
<img src="https://img.shields.io/badge/Donate-PayPal-blue.svg?style=flat-square&logo=paypal" align="center"/>


