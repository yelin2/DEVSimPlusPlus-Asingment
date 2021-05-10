#include "../Includes/Generator.hpp"

#include <iostream>

Generator::Generator() : Atomic() {
	SetName("Generator");
}

Generator::Generator(std::string EName) : Atomic(EName) {
	SetName(EName);
}

void Generator::ExtTransitionFN(double E, DevsMessage X) {
	// Logln(Name + "(EXT) --> :" + X.ContentPort() + ": " + "When: " + std::to_string(AddTime(GetLastEventTime(), E)));
	
	if (X.ContentPort() == "stop") Passivate();
}

void Generator::IntTransitionFN(void) {
	// Logln(Name + "(INT) --> Sigma: " + std::to_string(Sigma) + " / When: " + std::to_string(AddTime(GetLastEventTime(), Sigma)));
	if (Phase == "busy") { HoldIn("busy", InterArrivalTime); }
	else { Passivate(); }
}

void Generator::OutputFN(void){
	Logln(Name + "(OUT) --> Phase: " + Phase + " / Sigma: " + std::to_string(Sigma) + " / When: " + std::to_string(GetNextEventTime()));

	if (Phase == "busy") {
		MakeContent("out", "Job-" + std::to_string(Count++));
	}
	else MakeContent();
}

void Generator::InitializeFN(void){
	InterArrivalTime = 10;
	Count = 0;

	// 시작을 busy로 하고 시작하자마자 job-0을 out으로 내보내고 하겠다
	HoldIn("busy", 0.0);
}
