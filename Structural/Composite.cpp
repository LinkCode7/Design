#include "Composite.h"

using namespace std;

namespace CompositePattern
{
	void Entry()
	{
		Leaf* pLeaf = new Leaf();
		pLeaf->Operation();

		Composite* pComposite = new Composite();
		pComposite->Add(pLeaf);
		pComposite->Operation();

		Component* pComponentTemp = pComposite->GetChild(0);
		pComponentTemp->Operation();

		delete pComposite;
	}

} // namespace CompositePattern
