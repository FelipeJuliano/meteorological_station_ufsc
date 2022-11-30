 */
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <thread>

#include "CRaspberryPi.hpp"
#include "modules/CDht11.hpp"

class dados
{
private:
 int temp;
 float umid, vel;

public:

   virtual void captadados();

};

class analisadados : public dados
{

public:

void comparadados();
void defineeventos();

};

void dados::captadados(){

 try
    {
        CRaspberryPi Raspi;
        CDht11 Dht11(Raspi, 4);
        for (int i = 0; i < 10; ++i)
        {
            try
            {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                auto Data = Dht11.Measure();
                temp = Data.Temperature;
                umid = Data.Humidity;
                std::cout << "Temperature: " << Data.Temperature << " °C" << std::endl;
                std::cout << "Humidity: " << Data.Humidity << "%" << std::endl;
                std::cout << std::endl;
            }
            catch (const std::exception& E)
            {
                std::cout << "ERROR: " << E.what() << std::endl;
            }
        }
    }
    catch (const std::exception& E)
    {
        std::cout << "ERROR: " << E.what() << std::endl;
        return 1; 
}






;}

int main()
{
  














    return 0;
}