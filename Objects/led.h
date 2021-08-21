#ifndef LED_HFILE
#define LED_HFILE

class LED {
public:
	LED(int i);
	void setXYZ(float x, float y, float z);
	int index;
	float x, y, z;

};

#endif
