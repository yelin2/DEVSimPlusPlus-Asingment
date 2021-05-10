#include "../Includes/Process.hpp"

#include <string>

Process::Process(std::string entity_name) : Atomic(entity_name) { 
    SetName(entity_name); 
}

void Process::ExtTransitionFN(double Time, DevsMessage MSG) {
	// Log(Name + "(EXT) --> ");
	JobID = MSG.ContentValue();
	if (MSG.ContentPort() == "in") {
		if (Phase == "passive"){
			HoldIn("busy", PTime);
		}
	}
	else Continue();
	Logln();
}

void Process::IntTransitionFN(void) {
	Log(Name + "(INT) --> ");
	if (Phase == "busy"){
		// Get job from the Queue
		// processing
		Log(" process : " + JobID);
		HoldIn("busy", PTime);
		Passivate();
	}
	else Continue();
	Logln();
}

void Process::OutputFN(void) {
	Log(Name + "(OUT) --> ");
	
	if (Phase == "busy"){
		MakeContent("out", JobID);
	}
	else MakeContent();
	Logln();
}

void Process::InitializeFN(void){
	PTime = (double) 7.0;
	Passivate();
}