#include "Adapter.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

namespace AdapterPattern
{
	void Entry()
	{
		ITarget* pTarget = new Adaptor;
		pTarget->f1();
		pTarget->f2();
		pTarget->fc();

		(pTarget);
	}

	void STLAdapt()
	{
		// 统计容器中小于60的元素
		vector<int> scores = { 10,20,60,80,65,83,92,96,71,45 };
		auto result = std::count_if(scores.begin(), scores.end(), [](int val) { return (val < 60); });
		cout << result << endl;
	}

} // namespace AdapterPattern
