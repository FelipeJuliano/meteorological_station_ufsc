#include <iostream>
#include <CppLinuxSerial/SerialPort.hpp>

using namespace mn::CppLinuxSerial;

class Menu 
{
    int escolha;
public:
    Menu();
    ~Menu();
    void selecao();
  

};

Menu::Menu()
{
    std::cout <<"========================================\n";
    std::cout <<"         Estacao Meteorologica\n";
    std::cout <<"========================================\n";
  }

Menu::~Menu()
{
    std::cout << "\nEncerrando programa\n";
}
  void Menu::selecao()
{

  
  std::cout <<" Selecione 1 para captar dados\n 0 para sair";
  std::cin >> escolha;

        if ((escolha = 1))
        {
          
            std::cout << "Captando dados";
            SerialPort serialPort("/dev/ttyUSB0", BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE);
	// Use SerialPort serialPort("/dev/ttyACM0", 13000); instead if you want to provide a custom baud rate
	serialPort.SetTimeout(-1); // Block when reading until any data is received
	serialPort.Open();

	// Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
	std::string readvel;
	serialPort.Read(readvel);

  std::string readtemp;
	serialPort.Read(readtemp);

  std::string readData;
	serialPort.Read(readData);

  
 std::cout << readvel;
 std::cout << readtemp;
 std::cout << readData;

	// Close the serial port
	serialPort.Close();
          
}
   if((escolha = 0)){
      std::cout << "\nReiniciando sistema\n";
      main();


    }
    else ( escolha != 1 & escolha != 0){

      std::cout << "\nDigite uma entrada válida\n";
      main();

    
  }
  }
     
int main() {


Menu *p, *p2;
  
p = new Menu();

p -> selecao();  
  
}
  
    
  
