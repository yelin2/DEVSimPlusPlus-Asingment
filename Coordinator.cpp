#include "../Includes/Coordinator.hpp"

#include <string>

Coordinator::Coordinator(std::string entity_name) : Atomic(entity_name) { 
    SetName(entity_name); 
}

void Coordinator::ExtTransitionFN(double Time, DevsMessage MSG) {
	std::string oldP = Phase;
	
	if (MSG.ContentPort() == "in") {
		JobID = MSG.ContentValue();
		if (Phase == "passive"){
			HoldIn("send_0", PTime);
		}
	} else if (MSG.ContentPort() == "x0") {
		if (Phase == "passive"){
			HoldIn("send_1", PTime);
		}
	} else if (MSG.ContentPort() == "x1") {
		if (Phase == "passive"){
			HoldIn("send_2", PTime);
		}
	} else if (MSG.ContentPort() == "x2") {
		if (Phase == "passive"){
			HoldIn("send_fin", PTime);
		}
	}
	else Continue();
	Log(Name + "(EXT) input port= " + MSG.ContentPort() + "  Transition: " + oldP + " --> " + Phase);
	Logln();
}

void Coordinator::IntTransitionFN(void) {
	std::string oldIP = Phase;
	if (Phase == "send_0"){
		Log(" process : " + JobID);
		Logln();
		HoldIn("send_0", PTime);
		Passivate();
	} else if (Phase == "send_1"){
		Log(" process : " + JobID);
		HoldIn("send_1", PTime);
		Logln();
		Passivate();
	} else if (Phase == "send_2"){
		Log(" process : " + JobID);
		HoldIn("send_2", PTime);
		Logln();
		Passivate();
	} else if (Phase == "send_fin"){
		Log(" process : " + JobID);
		HoldIn("send_fin", PTime);
		Logln();
		Passivate();
	}
	else Continue();
	Log(Name + "(INT): " + oldIP + " --> " + Phase);
	Logln();
}

void Coordinator::OutputFN(void) {
	// Log(Name + "(OUT) --> ");
	
	if (Phase == "send_0"){
		MakeContent("y0", JobID);
	}else if (Phase == "send_1"){
		MakeContent("y1", JobID);
	}else if (Phase == "send_2"){
		MakeContent("y2", JobID);
	} else if (Phase == "send_fin"){
		MakeContent("out", JobID);
	}
	else MakeContent();
	Logln();
}

void Coordinator::InitializeFN(void){
	PTime = (double) 1.0;
	Passivate();
}