#include <stdint.h> 
class FndDisplay
{
public:
	FndDisplay(uint8_t clk, uint8_t dio);
	void start();
	void stop();
	bool writeByte(uint8_t b);
  void init();
	int writeNumber(int number,bool colon=false);
  int writeNumber_f(int number);
private:
	uint8_t m_clk;
	uint8_t m_dio;
};
