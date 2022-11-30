 
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <thread>
#include "CRaspberryPi.hpp"
#include "CDht11.hpp"
#include <CppLinuxSerial/SerialPort.hpp>

using namespace mn::CppLinuxSerial;

class dados
{
private:
 int temp;
 float umid;
 const float pi = 3.14159265;     //Número de pi
 int period = 5000;               //Tempo de medida(miliseconds)
 int delaytime = 2000;            //Invervalo entre as amostras (miliseconds)
 int radius = 147;                //Raio do anemometro(mm)
 unsigned int Sample  = 0;        //Armazena o número de amostras
 unsigned int counter = 0;        //Contador para o sensor  
 unsigned int RPM = 0;            //Rotações por minuto
 float speedwind = 0;             //Velocidade do vento (m/s)
 float windspeed = 0;  
public:

   virtual void anemometrof();
   virtual void dht11();
   friend void enviadados();

};

class analisadados : public dados
{

public:

void comparadados();
void defineeventos();

};

void dados::dht11(){

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

void dados::anemometrof()
{
try
{
  speedwind = 0;
  windspeed = 0;
  
  counter = 0;  
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();       
  long startTime = millis();
  while(millis() < startTime + period) {}

  RPM =((counter)*60)/(period/1000);  // Calculate revolutions per minute (RPM)

  windspeed = ((4 * pi * radius * RPM)/60) / 1000;  //Calcula a velocidade do vento em m/s

  speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6;  //Calcula velocidade do vento em km/h

  counter++;
}
 catch (const std::exception& E)
    {
        std::cout << "ERROR: " << E.what() << std::endl;
        return 1; 
}

};

class enviadados
{

            SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	// Use SerialPort serialPort("/dev/ttyACM0", 13000); instead if you want to provide a custom baud rate
	serialPort.SetTimeout(-1); // Block when reading until any data is received
	serialPort.Open();

	// Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
	std::string sendspeedwind;
	serialPort.Send(speedwind);

  std::string sendtemp;
	serialPort.Send(readtemp);

  std::string sendData;
	serialPort.Send(readData);


	serialPort.Close();
};



int main()
{

dados *captandodados, *captandodadosa, *enviadados;
int i;
i = 1;

    while (i=1)

            {

                
                captandodados -> dht11();

                captandodadosa -> anemometrof();

                enviadados -> enviadados();

            }
    return 0;
}