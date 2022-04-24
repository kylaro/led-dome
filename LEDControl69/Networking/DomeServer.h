// DomeServer.h : Include file for standard system include files,
// or project specific include files.
#ifndef DOMESERVER_H
#define DOMESERVER_H
// TODO: Reference additional headers your program requires here.
namespace server {

	int start();
	

	typedef struct {
		float x;
		float y;
		float z;
		float percussion;
	} joint_t;

	typedef struct {

		joint_t left_hand;
		joint_t right_hand;
		joint_t left_foot;
		joint_t right_foot;

		
		
	} posepack_t;

	
};


#endif