/**
 * @file main.cpp
 * @author Oliver Joisten (https://oliver-joisten.se/)
 * @brief Assignment-1
 * @details Implement a thread safe and synchronized vehicle manufacturer-dealersprogram.
                    1.The manufacturer manufactures cars and trucks randomly and stores them in to the warehouse.
                    When the warehouse is full the manufacturing thread shall sleep.
                    2.A dealer gets a vehicle at a time from the warehouse and prints all the properties of the vehicle to the terminal.
                    When the warehouse is empty the dealer threads shall sleep until a vehicle is manufactured by the manufacturer thread.
                    3.The manufacturer and the dealers operateat different rates.
                    It means that the program shall work correctly in both of the following cases.
                        a.The manufacturer is faster than the dealers
                        b.The dealers are faster than the manufacturer
                    4.Vehicle, Car and Truck are classes to model the properties and they shall have functions to print the properties.
                    5.The circularbuffer is an uncopyable, unassignable and unmovable template class which is implemented
                    using an array whose capacity is specified by a macro in the commandline when you compile the program.
                    The capacity shall be at least 8.
                    Every dealer is a thread and when a dealer gets a vehicle, it shall print all the properties of the vehicle to the terminal.
                    Number of dealers shall be at least 2 and it is specified as an argument when the program is run
 * @version 0.1
 * @date 2023-04-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <random>

// Get buffer capacity and number of dealers from command-line arguments
#ifndef BUFFER_CAPACITY
#error Please specify the buffer capacity using -DBUFFER_CAPACITY=N, where N is an integer between 8 and 100.
#elif BUFFER_CAPACITY < 8 || BUFFER_CAPACITY > 100
#error The buffer capacity must be between 8 and 100.
#endif

#ifndef NUM_DEALERS
#error Please specify the number of dealers using -DNUM_DEALERS=N, where N is an integer greater than 1.
#elif NUM_DEALERS < 2
#error The number of dealers must be at least 2.
#endif

// Vehicle class to model the properties of the vehicle
class Vehicle
{
public:
    // Constructor to generate a unique id number starting from 1000
    Vehicle(std::string model, std::string type) : model_(model), type_(type)
    {
        id_ = getNextId();
    }

    // Function to print the id number of the vehicle
    void printId()
    {
        std::cout << "ID number: " << id_ << std::endl;
    }

    // Function to print the properties of the vehicle
    virtual void printProperties()
    {
        std::cout << "Model: " << model_ << std::endl;
        std::cout << "Type: " << type_ << std::endl;
        printId();
    }

private:
    // Function to generate a unique id number for each vehicle
    static int getNextId()
    {
        static std::mutex mutex_;
        static int lastId_ = 1000;
        std::lock_guard<std::mutex> lock(mutex_);
        return ++lastId_;
    }

protected:
    int id_;
    std::string model_;
    std::string type_;
};

// Car class derived from Vehicle
class Car : public Vehicle
{
public:
    Car() : Vehicle("SUV", "Car") {}

    void printProperties() override
    {
        std::cout << "This is a " << model_ << " " << type_ << "." << std::endl;
        Vehicle::printProperties();
    }
};

// Truck class derived from Vehicle
class Truck : public Vehicle
{
public:
    Truck() : Vehicle("Pickup", "Truck") {}

    void printProperties() override
    {
        std::cout << "This is a " << model_ << " " << type_ << "." << std::endl;
        Vehicle::printProperties();
    }
};

template <typename T>
class WareHouse
{
public:
    explicit WareHouse(size_t capacity) : buffer_(new T[capacity]), capacity_(capacity),
                                          head_(0), tail_(0), size_(0) {}

    ~WareHouse()
    {
        delete[] buffer_;
    }

    void put(T item)
    {
        std::unique_lock<std::mutex> lock(mutex_);

        // Wait until buffer has space
        while (size_ == capacity_)
        {
            bufferNotFull_.wait(lock);
        }

        buffer_[tail_] = std::move(item);
        tail_ = (tail_ + 1) % capacity_;
        ++size_;

        // Signal that buffer is not empty
        bufferNotEmpty_.notify_one();
    }

    T get()
    {
        std::unique_lock<std::mutex> lock(mutex_);

        // Wait until buffer is not empty
        while (size_ == 0)
        {
            bufferNotEmpty_.wait(lock);
        }

        T item = std::move(buffer_[head_]);
        head_ = (head_ + 1) % capacity_;
        --size_;

        // Signal that buffer is not full
        bufferNotFull_.notify_one();

        return item;
    };

private:
    T *buffer_;
    const size_t capacity_;
    size_t head_;
    size_t tail_;
    size_t size_;
    std::mutex mutex_;
    std::condition_variable bufferNotEmpty_;
    std::condition_variable bufferNotFull_;
};

// Create the circular buffer with the specified capacity
WareHouse<std::unique_ptr<Vehicle>> buffer(BUFFER_CAPACITY);

// Manufacturer thread function
void manufacturer(WareHouse<std::unique_ptr<Vehicle>> &buffer)
{
    std::cout << "Manufacturer started." << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    while (true)
    {
        // Manufacture a vehicle randomly
        std::unique_ptr<Vehicle> vehicle;
        if (dis(gen) == 0)
        {
            vehicle = std::make_unique<Car>();
        }
        else
        {
            vehicle = std::make_unique<Truck>();
        }
        // Put the vehicle into the buffer
        buffer.put(std::move(vehicle));
        std::cout << "Manufacturer produced a vehicle." << std::endl;

        // Sleep for a random time
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen) * 1000));
    }
}

// Dealer thread function
void dealer(WareHouse<std::unique_ptr<Vehicle>> &buffer)
{
    std::cout << "Dealer started." << std::endl;
    while (true)
    {
        // Get a vehicle from the buffer
        std::unique_ptr<Vehicle> vehicle = buffer.get();
        std::cout << "Dealer got a vehicle." << std::endl;
        // Print the properties of the vehicle
        vehicle->printProperties();

        // Sleep for a random time
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen) * 1000));
    }
}

int main()
{
    // Create the manufacturer thread
    std::thread manufacturerThread(manufacturer, std::ref(buffer));
    // Create the dealer threads
    std::array<std::thread, NUM_DEALERS> dealerThreads;
    for (int i = 0; i < NUM_DEALERS; ++i)
    {
        dealerThreads[i] = std::thread(dealer, std::ref(buffer));
    }

    // Join the threads
    manufacturerThread.join();
    for (auto &thread : dealerThreads)
    {
        thread.join();
    }

    return 0;
}
