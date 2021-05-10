#include "../Includes/Kernel/Log.hpp"
#include "../Includes/Kernel/Entstr.hpp"

#include "../Includes/Generator.hpp"
#include "../Includes/Transducer.hpp"
#include "../Includes/Coordinator.hpp"
#include "../Includes/Process.hpp"

int main()
{
	EntStr *efp = new EntStr("ef-p");
	efp->AddItem(new Digraph("pip"));
	efp->AddItem(new Digraph("ef"));

	efp->AddCouple("pip", "ef", "out", "in");
	efp->AddCouple("ef","pip", "out", "in");

	efp->SetCurrentItem("pip");
	efp->AddItem(new Coordinator("pip-co"));
	efp->AddItem(new Process("p0"));
	efp->AddItem(new Process("p1"));
	efp->AddItem(new Process("p2"));
	efp->AddCouple("pip-co", "pip", "out", "out");
	efp->AddCouple("pip", "pip-co", "in", "in");
	efp->AddCouple("pip-co", "p0", "y0", "in");
	efp->AddCouple("p0", "pip-co", "out", "x0");
	efp->AddCouple("pip-co", "p1", "y1", "in");
	efp->AddCouple("p1", "pip-co", "out", "x1");
	efp->AddCouple("pip-co", "p2", "y2", "in");
	efp->AddCouple("p2", "pip-co", "out", "x2");

	efp->SetCurrentItem("ef");
	efp->AddItem(new Generator("genr"));
	efp->AddItem(new Transducer("transd"));
	efp->AddCouple("ef", "transd", "in", "solved");
	efp->AddCouple("transd", "genr", "out", "stop");
	efp->AddCouple("genr", "ef", "out", "out");
	efp->AddCouple("genr", "transd", "out", "arriv");

	efp->Restart();

	return 0;
}